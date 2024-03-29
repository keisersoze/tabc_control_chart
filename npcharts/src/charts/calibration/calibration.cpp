//
// Created by filip on 27/08/2021.
//

#include "calibration.h"

#include "../../stat/utils.h"
#include "../../rng/global_rng.h"

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

double conditional_unidirectional_calibration(const std::vector<double> &reference_sample,
                                              unsigned n,
                                              const monitoring_statistic &ms,
                                              bool upper_limit,
                                              double target_ARL,
                                              unsigned nsim) {
    unsigned n_iterations = target_ARL * nsim;
    std::vector<double> stats(n_iterations, 0);
    double type_1_error_prob = 1/target_ARL;
    for (unsigned i = 0; i < n_iterations; ++i) {
        std::vector<double> test_sample_boot = sample_with_replacement(reference_sample, n, global_rng::instance);
        double stat = ms(reference_sample, test_sample_boot, global_rng::instance);
        stats[i]=stat;
    }
    std::function<bool (double&, double&)> comparator;
    if (!upper_limit){
        comparator = std::greater_equal<double>();
        std::sort(stats.begin(), stats.end(), std::less<>());
    } else{
        comparator = std::less_equal<double>();
        std::sort(stats.begin(), stats.end(), std::greater<>());
    }
    double limit = stats[(int)round(stats.size() * type_1_error_prob)];
    return limit;
}

std::vector<std::vector<int>> unconditional_unidirectional_calibration(unsigned m,
                                                                       unsigned n,
                                                                       const distribution &ic_distribution,
                                                                       const monitoring_statistic &ms,
                                                                       const std::vector<double> &limits_seq,
                                                                       bool upper_limit,
                                                                       unsigned nsim,
                                                                       unsigned run_length_cap) {
    std::vector<double> limits_seq_sorted(limits_seq);

    std::function<bool (double&, double&)> comparator;
    if (upper_limit){
        comparator = std::greater_equal<double>();
        std::sort(limits_seq_sorted.begin(), limits_seq_sorted.end(), std::less<>());
    } else{
        comparator = std::less_equal<double>();
        std::sort(limits_seq_sorted.begin(), limits_seq_sorted.end(), std::greater<>());
    }

    std::vector<std::vector<int>> res_matrix(
            nsim,
            std::vector<int>(limits_seq_sorted.size()));
    #pragma omp parallel firstprivate(ic_distribution) firstprivate(ms)
    {
        std::vector<double> reference_sample(m);
        std::vector<double> test_sample(n);

        dqrng::xoshiro256plus lrng(global_rng::instance);  // make thread local copy of rng
        lrng.long_jump(omp_get_thread_num() + 1);  // advance rng by 1 ... ncores jumps

        #pragma omp for
        for (unsigned i = 0; i < nsim; ++i) {
            std::generate(reference_sample.begin(), reference_sample.end(),
                          [&ic_distribution, &lrng]() { return ic_distribution(lrng);});
            unsigned run_length = 0;
            unsigned lcl_idx = 0;
            double stat;
            for (;;) {
                run_length++;
                std::generate(test_sample.begin(), test_sample.end(),
                              [&ic_distribution, &lrng]() { return ic_distribution(lrng);});
                stat = ms(reference_sample, test_sample, lrng);
                // Update rl for limits that have been surpassed
                while (lcl_idx < limits_seq_sorted.size() and comparator(stat, limits_seq_sorted[lcl_idx])) {
                    res_matrix[i][lcl_idx] = run_length;
                    lcl_idx++;
                }
                // All limits have been surpassed
                if (lcl_idx == limits_seq_sorted.size()){
                    break;
                }
                // If rl threshold is hit before all limits are surpassed then truncate rl
                // for all remaining limits (this can introduce bias)
                if (run_length == run_length_cap) {
                    while (lcl_idx < limits_seq_sorted.size()) {
                        res_matrix[i][lcl_idx] = run_length_cap;
                        lcl_idx++;
                    }
                    break;
                }

            }
        }
    }
    global_rng::instance.long_jump(omp_get_max_threads() + 1);
    return res_matrix;
}
