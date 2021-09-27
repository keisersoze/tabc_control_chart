//
// Created by filip on 27/08/2021.
//

#include "calibration.h"

#include "utils.h"
#include "global_rng.h"

#include <xoshiro.h>

#include <omp.h>

//Rcpp::List find_ucl_conditional(const std::vector<double> &reference_sample,
//                                unsigned n,
//                                double target_ARL,
//                                unsigned nsim,
//                                unsigned nperm,
//                                const std::string &test) {
//    test_fun_ptr test_f = dispatch_from_string(test);
//    // double type_1_error_prob = 1.0 / (double) target_ARL;
//    unsigned n_iterations = target_ARL * nsim;
//    std::vector<unsigned> counts(nperm + 1, 0);
//    for (unsigned i = 0; i < n_iterations; ++i) {
//        std::vector<double> test_sample_boot = sample_with_replacement(reference_sample, n, global_rng::instance);
//        perm_test_result res = test_f(reference_sample, test_sample_boot, nperm, global_rng::instance);
//        counts[res.pos]++;
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
//                              Rcpp::Named("distribution") = counts);
//}

std::vector<std::vector<int>> unconditional_unidirectional_calibration(unsigned m,
                                                                       unsigned n,
                                                                       const distribution &ic_distribution,
                                                                       const monitoring_statistic &ms,
                                                                       const std::vector<double> &lcl_seq,
                                                                       unsigned nsim,
                                                                       unsigned run_length_cap) {
    std::vector<double> lcl_seq_sorted(lcl_seq);
    std::sort(lcl_seq_sorted.begin(), lcl_seq_sorted.end(), std::greater<>());

    std::vector<std::vector<int>> res_matrix(
            nsim,
            std::vector<int>(lcl_seq_sorted.size()));
    #pragma omp parallel firstprivate(ic_distribution) firstprivate(ms)
    {
        std::vector<double> reference_sample(m);
        std::vector<double> test_sample(n);

        dqrng::xoroshiro128plus lrng(global_rng::instance);  // make thread local copy of rng
        lrng.long_jump(omp_get_thread_num() + 1);  // advance rng by 1 ... ncores jumps

        #pragma omp for
        for (unsigned i = 0; i < nsim; ++i) {
            std::generate(reference_sample.begin(), reference_sample.end(),
                          [&ic_distribution, &lrng]() { return ic_distribution(lrng);});
            // ic_variate_generator(lrng, reference_sample);
            unsigned run_length = 0;
            unsigned lcl_idx = 0;
            double stat;
            for (;;) {
                run_length++;
                std::generate(test_sample.begin(), test_sample.end(),
                              [&ic_distribution, &lrng]() { return ic_distribution(lrng);});
                // ic_variate_generator(lrng, test_sample);
                stat = ms(reference_sample, test_sample, lrng);
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
    return res_matrix;
}
