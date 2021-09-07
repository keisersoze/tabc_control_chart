//
// Created by filip on 27/08/2021.
//

#include "calibration.h"
#include "test_dispatching.h"
#include "utils.h"

#include <xoshiro.h>

calibration_result::calibration_result(double LCL) : LCL(LCL) {}


Rcpp::List find_ucl_conditional(const std::vector<double> &reference_sample,
                                unsigned n,
                                double target_ARL,
                                unsigned nsim,
                                unsigned nperm,
                                const std::string &test,
                                unsigned seed) {
    test_fun_ptr test_f = dispatch_from_string(test);
    // double type_1_error_prob = 1.0 / (double) target_ARL;
    unsigned n_iterations = target_ARL * nsim;
    std::vector<unsigned> counts(nperm + 1, 0);
    dqrng::xoroshiro128plus rng(seed);
    for (unsigned i = 0; i < n_iterations; ++i) {
        std::vector<double> test_sample_boot = sample_with_replacement(reference_sample, n, rng);
        perm_test_result res = test_f(reference_sample, test_sample_boot, nperm, rng);
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