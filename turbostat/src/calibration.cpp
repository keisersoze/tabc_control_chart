//
// Created by filip on 27/08/2021.
//

#include "calibration.h"
#include "test_dispatching.h"
#include "utils.h"
#include "global_rng.h"
#include "distribution_dispatching.h"

#include <xoshiro.h>
#include <boost/random/normal_distribution.hpp>

#include <omp.h>

calibration_result::calibration_result(double LCL) : LCL(LCL) {}


Rcpp::List find_ucl_conditional(const std::vector<double> &reference_sample,
                                unsigned n,
                                double target_ARL,
                                unsigned nsim,
                                unsigned nperm,
                                const std::string &test) {
    test_fun_ptr test_f = dispatch_from_string(test);
    // double type_1_error_prob = 1.0 / (double) target_ARL;
    unsigned n_iterations = target_ARL * nsim;
    std::vector<unsigned> counts(nperm + 1, 0);
    for (unsigned i = 0; i < n_iterations; ++i) {
        std::vector<double> test_sample_boot = sample_with_replacement(reference_sample, n, global_rng::instance);
        perm_test_result res = test_f(reference_sample, test_sample_boot, nperm, global_rng::instance);
        counts[res.pos]++;
    }
    unsigned tot_count = 0;
    unsigned i = 0;
    unsigned max_type_1_error_counts = nsim; // (double) target_ARL * nsim * type_1_error_prob; (equal to nsim)
    while (tot_count <= max_type_1_error_counts) {
        tot_count += counts[i];
        i++;
    }
    double LCL = (double) (i - 1) / (double) nperm;
    return Rcpp::List::create(Rcpp::Named("LCL") = LCL,
                              Rcpp::Named("distribution") = counts);
}

Rcpp::NumericMatrix find_lcl_uncoditional(unsigned m,
                                          unsigned n,
                                          const std::string &dist,
                                          const std::vector<double> &params,
                                          unsigned nsim,
                                          unsigned nperm,
                                          const std::vector<double> &lcl_seq,
                                          const std::string &test,
                                          unsigned run_length_cap) {
    test_fun_ptr test_f = dispatch_from_string(test);

    std::vector<double> lcl_seq_sorted(lcl_seq);
    std::sort(lcl_seq_sorted.begin(), lcl_seq_sorted.end(), std::greater<>());

    std::vector<std::vector<int> > res_matrix(
            nsim,
            std::vector<int>(lcl_seq_sorted.size()));
    #pragma omp parallel
    {
        // TODO distribution should be a parameter
        std::function<double (dqrng::xoroshiro128plus&)> sampling_func =
                dispatch_sampling_function<dqrng::xoroshiro128plus>(dist, params, 0.0);

        std::vector<double> reference_sample(m);
        std::vector<double> test_sample(n);

        dqrng::xoroshiro128plus lrng(global_rng::instance);      // make thread local copy of rng
        lrng.long_jump(omp_get_thread_num() + 1);  // advance rng by 1 ... ncores jumps

        #pragma omp for
        for (unsigned i = 0; i < nsim; ++i) {
            std::generate(reference_sample.begin(), reference_sample.end(),
                          [&sampling_func, &lrng]() { return sampling_func(lrng); });
            unsigned run_length = 0;
            unsigned lcl_idx = 0;
            double stat;
            for (;;) {
                run_length++;
                std::generate(test_sample.begin(), test_sample.end(),
                              [&sampling_func, &lrng]() { return sampling_func(lrng); });
                perm_test_result res = test_f(reference_sample, test_sample, nperm, lrng);
                stat = res.p_value;
                while (lcl_idx < lcl_seq_sorted.size() and stat <= lcl_seq_sorted[lcl_idx]) {
                    res_matrix[i][lcl_idx] = run_length;
                    lcl_idx++;
                }
                if (run_length == run_length_cap or lcl_idx == lcl_seq_sorted.size()) {
                    break;
                }
            }
        }
    }
    global_rng::instance.long_jump(omp_get_max_threads() + 1);

    Rcpp::NumericMatrix res_rcpp(nsim, lcl_seq_sorted.size());

    for (unsigned i = 0; i < nsim; ++i) {
        for (unsigned j = 0; j < lcl_seq_sorted.size(); ++j) {
            res_rcpp(i, j) = res_matrix[i][j];
        }
    }

    return res_rcpp;
}




//Rcpp::List find_UCL(Rcpp::NumericVector reference_sample,
//                    unsigned n,
//                    double target_ARL,
//                    unsigned nsim,
//                    unsigned nperm,
//                    const std::string &test,
//                    unsigned seed){
//    test_fun_ptr test_f = dispatch_from_string(test);
//    // double type_1_error_prob = 1.0 / (double) target_ARL;
//    unsigned n_iterations = target_ARL * nsim;
//    Rcpp::NumericVector counts(nperm + 1);
//    dqrng::xoroshiro128plus rng(seed);
//
//#pragma omp parallel num_threads(ncores)
//    {
//        dqrng::xoshiro256plus lrng(rng);      // make thread local copy of rng
//        lrng.long_jump(omp_get_thread_num() + 1);  // advance rng by 1 ... ncores jumps
//        for (unsigned i = 0; i < n_iterations; ++i) {
//            Rcpp::NumericVector test_sample_boot = sample_with_replacement(reference_sample, n, lrng);
//            unsigned position = test_f(reference_sample, test_sample_boot, nperm, lrng)[2];
//            counts[position]++;
//        }
//    }
//    unsigned tot_count = 0;
//    unsigned i = 0;
//    unsigned max_type_1_error_counts = nsim; // (double) target_ARL * nsim * type_1_error_prob; (equal to nsim)
//    while (tot_count <= max_type_1_error_counts) {
//        tot_count += counts[i];
//        i++;
//    }
//    double LCL = (double) (i - 1) / (double) nperm;
//    return Rcpp::List::create(Rcpp::Named("LCL") = LCL,
//                              Rcpp::Named("distribution") = counts );
//}