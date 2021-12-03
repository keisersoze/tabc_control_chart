//
// Created by filip on 25/08/2021.
//

#include "evaluation.h"

#include "../../rng/global_rng.h"

#include "../../stat/utils.h" //sample_with_replacement

#include <xoshiro.h>

#include <omp.h>

//double testCExact(Rcpp::NumericVector x1, Rcpp::NumericVector x2) {
//    const unsigned m = x1.size();
//    const unsigned n = x2.size();
//    Rcpp::NumericVector pooled_sample(x1.size() + x2.size());
//    for (unsigned i = 0; i < m; ++i) {
//        pooled_sample[i] = x1[i];
//    }
//    for (unsigned i = 0; i < n ; ++i) {
//        pooled_sample[x1.size() + i] = x2[i];
//    }
//    // Rcpp::print(pooled_sample);
//    Rcpp::NumericVector ranks = avg_rank(pooled_sample);
//    // Rcpp::print(ranks);
//    unsigned sum_of_x2_ranks = std::accumulate(ranks.begin(), ranks.begin() + m, 0.0);
//    double obs_stat = sum_of_x2_ranks - m * (m + 1)/2;
//    // Rcpp::Rcout << obs_stat << std::endl;
//    return R::pwilcox( obs_stat, m, n, true, false);
//
//}

//std::vector<double> parallel_random_sum(int n, int m, int ncores) {
//    std::normal_distribution<double> dist(0.0, 1.0);
//    dqrng::xoshiro256plus rng(42);              // properly seeded rng
//    std::vector<double> res(m);
//    // ok to use rng here
//
//    #pragma omp parallel num_threads(ncores)
//    {
//        dqrng::xoshiro256plus lrng(rng);      // make thread local copy of rng
//        lrng.long_jump(omp_get_thread_num() + 1);  // advance rng by 1 ... ncores jumps
//
//        #pragma omp for
//        for (int i = 0; i < m; ++i) {
//            double lres(0);
//            for (int j = 0; j < n; ++j) {
//                lres += dist(lrng);
//            }
//            res[i] = lres / n;
//        }
//    }
//    // ok to use rng here
//    return res;
//}

//Rcpp::DataFrame conditional_run_length_distribution_bootstrap(const std::vector<double> &reference_sample,
//                                                              unsigned n,
//                                                              unsigned nsim,
//                                                              unsigned nperm,
//                                                              const std::vector<double> &shifts,
//                                                              double LCL,
//                                                              const std::string &test,
//                                                              unsigned run_length_cap) {
//    Rcpp::NumericVector arls(shifts.size());
//    // Rcpp::NumericVector sds(shifts.size());
//    test_fun_ptr test_f = dispatch_from_string(test);
//    for (unsigned shift_index = 0; shift_index < shifts.size(); ++shift_index) {
//        double shift = shifts[shift_index];
//        std::vector<unsigned> run_lengths(nsim);
//        std::vector<double> shifted_reference_sample(reference_sample.size());
//        // TODO shift test sample and not reference sample
//        std::transform(reference_sample.begin(),
//                       reference_sample.end(),
//                       shifted_reference_sample.begin(),
//                       [shift](double x) -> double { return x + shift; });
//        #pragma omp parallel
//        {
//            dqrng::xoroshiro128plus lrng(global_rng::instance);      // make thread local copy of rng
//            lrng.long_jump(omp_get_thread_num() + 1);  // advance rng by 1 ... ncores jumps
//            #pragma omp for
//            for (unsigned i = 0; i < nsim; ++i) {
//                unsigned run_length = 0;
//                double stat;
//                do {
//                    run_length++;
//                    std::vector<double> test_sample_boot = sample_with_replacement(shifted_reference_sample, n, lrng);
//                    perm_test_result res = test_f(reference_sample, test_sample_boot, nperm, lrng);
//                    stat = res.p_value;
//                } while (stat > LCL and run_length <= run_length_cap);
//                run_lengths[i] = run_length;
//            }
//        }
//        global_rng::instance.long_jump(omp_get_max_threads() + 1);
//        arls[shift_index] = std::accumulate(run_lengths.begin(), run_lengths.end(), 0.0) / run_lengths.size();
//        // sds[shift_index] = Rcpp::sd(run_lengths);
//    }
//    Rcpp::DataFrame result = Rcpp::DataFrame::create(Rcpp::Named("ARLs") = arls);
//    return result;
//}

std::vector<std::vector<unsigned>> conditional_unidirectional_evaluation(const std::vector<double> &reference_sample,
                                                                         unsigned n,
                                                                         double limit,
                                                                         bool upper_limit,
                                                                         const std::vector<double> &shifts,
                                                                         const monitoring_statistic &ms,
                                                                         unsigned nsim,
                                                                         unsigned run_length_cap) {
    std::function<bool (double&, double&)> comparator;
    if (upper_limit){
        comparator = std::less<double>();
    } else{
        comparator = std::greater<double>();
    }
    std::vector<std::vector<unsigned>> rl_matrix(
            shifts.size(),
            std::vector<unsigned>(nsim));
    for (unsigned shift_index = 0; shift_index < shifts.size(); ++shift_index) {
        double shift = shifts[shift_index];
        #pragma omp parallel firstprivate(ms)
        {
            // make thread local copy of rng
            dqrng::xoshiro256plus lrng(global_rng::instance);
            // advance rng by 1 ... ncores jumps
            lrng.long_jump(omp_get_thread_num() + 1);
            #pragma omp for
            for (unsigned i = 0; i < nsim; ++i) {
                unsigned run_length = 0;
                double stat;
                do {
                    run_length++;
                    // generate test sample as if the process was IC
                    std::vector<double> test_sample_boot = sample_with_replacement(reference_sample, n, lrng);
                    // apply shift
                    std::transform(test_sample_boot.begin(),
                                   test_sample_boot.end(),
                                   test_sample_boot.begin(),
                                   [shift](double x) -> double { return x + shift; });
                    // compute monitoring statistic
                    stat = ms(reference_sample, test_sample_boot, lrng);
                } while (comparator(stat, limit) and run_length <= run_length_cap);
                rl_matrix[shift_index][i] = run_length;
            }
        }
        global_rng::instance.long_jump(omp_get_max_threads() + 1);
    }
    return rl_matrix;
}


std::vector<std::vector<unsigned>> unconditional_unidirectional_evaluation(unsigned m,
                                                                           unsigned n,
                                                                           double limit,
                                                                           bool upper_limit,
                                                                           const std::vector<double> &shifts,
                                                                           const distribution &ic_distribution,
                                                                           const monitoring_statistic &ms,
                                                                           unsigned nsim,
                                                                           unsigned run_length_cap) {
    std::function<bool (double&, double&)> comparator;
    if (upper_limit){
        comparator = std::less<double>();
    } else{
        comparator = std::greater<double>();
    }
    std::vector<std::vector<unsigned>> rl_matrix(
            shifts.size(),
            std::vector<unsigned>(nsim));
    for (unsigned shift_index = 0; shift_index < shifts.size(); ++shift_index) {
        double shift = shifts[shift_index];
        #pragma omp parallel firstprivate(ic_distribution) firstprivate(ms)
        {
            std::vector<double> reference_sample(m);
            std::vector<double> test_sample(n);

            // make thread local copy of rng
            dqrng::xoshiro256plus lrng(global_rng::instance);
            // advance rng by 1 ... ncores jumps
            lrng.long_jump(omp_get_thread_num() + 1);

            #pragma omp for
            for (unsigned i = 0; i < nsim; ++i) {
                // generate reference sample
                std::generate(reference_sample.begin(), reference_sample.end(),
                              [&ic_distribution, &lrng]() { return ic_distribution(lrng);});
                // ic_variate_generator(lrng, reference_sample);
                unsigned run_length = 0;
                double stat;
                do {
                    run_length++;
                    // generate test sample as if the process was IC
                    std::generate(test_sample.begin(), test_sample.end(),
                                  [&ic_distribution, &lrng]() { return ic_distribution(lrng);});
                    // ic_variate_generator(lrng, test_sample);
                    // apply shift
                    std::transform(test_sample.begin(),
                                   test_sample.end(),
                                   test_sample.begin(),
                                   [shift](double x) -> double { return x + shift; });
                    // compute monitoring statistic
                    stat = ms(reference_sample, test_sample, lrng);
                } while (comparator(stat, limit) and run_length <= run_length_cap);
                rl_matrix[shift_index][i] = run_length;
            }
        }
        global_rng::instance.long_jump(omp_get_max_threads() + 1);
    }
    return rl_matrix;
}

std::vector<std::vector<unsigned>> unconditional_unidirectional_evaluation_scale(unsigned m,
                                                                                 unsigned n,
                                                                                 double limit,
                                                                                 bool upper_limit,
                                                                                 const std::vector<double> &scale_multipliers,
                                                                                 const distribution &ic_distribution,
                                                                                 const monitoring_statistic &ms,
                                                                                 unsigned nsim,
                                                                                 unsigned run_length_cap){
    std::function<bool (double&, double&)> comparator;
    if (upper_limit){
        comparator = std::less<double>();
    } else{
        comparator = std::greater<double>();
    }
    std::vector<std::vector<unsigned>> rl_matrix(
            scale_multipliers.size(),
            std::vector<unsigned>(nsim));
    for (unsigned multiplier_index = 0; multiplier_index < scale_multipliers.size(); ++multiplier_index) {
        double scale_multiplier = scale_multipliers[multiplier_index];
        #pragma omp parallel firstprivate(ic_distribution) firstprivate(ms)
        {
            std::vector<double> reference_sample(m);
            std::vector<double> test_sample(n);

            // make thread local copy of rng
            dqrng::xoshiro256plus lrng(global_rng::instance);
            // advance rng by 1 ... ncores jumps
            lrng.long_jump(omp_get_thread_num() + 1);

            #pragma omp for
            for (unsigned i = 0; i < nsim; ++i) {
                // generate reference sample
                std::generate(reference_sample.begin(), reference_sample.end(),
                              [&ic_distribution, &lrng]() { return ic_distribution(lrng);});
                // ic_variate_generator(lrng, reference_sample);
                unsigned run_length = 0;
                double stat;
                do {
                    run_length++;
                    // generate test sample as if the process was IC
                    std::generate(test_sample.begin(), test_sample.end(),
                                  [&ic_distribution, &lrng]() { return ic_distribution(lrng);});
                    // ic_variate_generator(lrng, test_sample);
                    // apply shift
                    std::transform(test_sample.begin(),
                                   test_sample.end(),
                                   test_sample.begin(),
                                   [scale_multiplier](double x) -> double { return x * scale_multiplier; });
                    // compute monitoring statistic
                    stat = ms(reference_sample, test_sample, lrng);
                } while (comparator(stat, limit) and run_length <= run_length_cap);
                rl_matrix[multiplier_index][i] = run_length;
            }
        }
        global_rng::instance.long_jump(omp_get_max_threads() + 1);
    }
    return rl_matrix;
}

std::vector<std::vector<unsigned>> unconditional_unidirectional_evaluation_location_scale(unsigned m,
                                                                                          unsigned n,
                                                                                          double limit,
                                                                                          bool upper_limit,
                                                                                          const std::vector<std::pair<double,double>> &location_scale_changes,
                                                                                          const distribution &ic_distribution,
                                                                                          const monitoring_statistic &ms,
                                                                                          unsigned nsim,
                                                                                          unsigned run_length_cap){
    std::function<bool (double&, double&)> comparator;
    if (upper_limit){
        comparator = std::less<double>();
    } else{
        comparator = std::greater<double>();
    }
    std::vector<std::vector<unsigned>> rl_matrix(
            location_scale_changes.size(),
            std::vector<unsigned>(nsim));
    for (unsigned location_scale_index = 0; location_scale_index < location_scale_changes.size(); ++location_scale_index) {
        double location_shift = location_scale_changes[location_scale_index].first;
        double scale_multiplier = location_scale_changes[location_scale_index].second;
        #pragma omp parallel firstprivate(ic_distribution) firstprivate(ms)
        {
            std::vector<double> reference_sample(m);
            std::vector<double> test_sample(n);

            // make thread local copy of rng
            dqrng::xoshiro256plus lrng(global_rng::instance);
            // advance rng by 1 ... ncores jumps
            lrng.long_jump(omp_get_thread_num() + 1);

            #pragma omp for
            for (unsigned i = 0; i < nsim; ++i) {
                // generate reference sample
                std::generate(reference_sample.begin(), reference_sample.end(),
                              [&ic_distribution, &lrng]() { return ic_distribution(lrng);});
                // ic_variate_generator(lrng, reference_sample);
                unsigned run_length = 0;
                double stat;
                do {
                    run_length++;
                    // generate test sample as if the process was IC
                    std::generate(test_sample.begin(), test_sample.end(),
                                  [&ic_distribution, &lrng]() { return ic_distribution(lrng);});
                    // ic_variate_generator(lrng, test_sample);
                    // apply shift
                    std::transform(test_sample.begin(),
                                   test_sample.end(),
                                   test_sample.begin(),
                                   [location_shift, scale_multiplier](double x) -> double { return (x * scale_multiplier) + location_shift; });
                    // compute monitoring statistic
                    stat = ms(reference_sample, test_sample, lrng);
                } while (comparator(stat, limit) and run_length <= run_length_cap);
                rl_matrix[location_scale_index][i] = run_length;
            }
        }
        global_rng::instance.long_jump(omp_get_max_threads() + 1);
    }
    return rl_matrix;
}




