//
// Created by filip on 25/08/2021.
//

#include "evaluation.h"

#include "../../rng/global_rng.h"

#include "../../stat/utils.h" //sample_with_replacement

#include <xoshiro.h>

#include <omp.h>

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


uncoditional_evaluation_result::uncoditional_evaluation_result(std::vector<unsigned int> &&run_lengths,
                                                               std::vector<double> &&reference_sample_means,
                                                               std::vector<double> &&reference_sample_sds) :
        run_lengths(std::move(run_lengths)),
        reference_sample_means(std::move(reference_sample_means)),
        reference_sample_sds(std::move(reference_sample_sds)) {}



uncoditional_evaluation_result unconditional_evaluation(unsigned m,
                                                        unsigned n,
                                                        const std::optional<double> &lcl,
                                                        const std::optional<double> &ucl,
                                                        double location_shift,
                                                        double scale_multiplier,
                                                        const distribution &ic_distribution,
                                                        const monitoring_statistic &ms,
                                                        unsigned nsim,
                                                        unsigned run_length_cap) {
    std::vector<unsigned> run_lengths(nsim);
    std::vector<double> reference_sample_means(nsim);
    std::vector<double> reference_sample_sds(nsim);
    #pragma omp parallel firstprivate(ic_distribution) firstprivate(ms)
    {
        std::vector<double> reference_sample(m);
        std::vector<double> test_sample(n);

        // make thread local copy of rng
        dqrng::xoshiro256plus lrng(global_rng::instance);
        // advance rng by 0,1, ... ncores - 1 jumps
        lrng.long_jump(omp_get_thread_num());

        #pragma omp for
        for (unsigned i = 0; i < nsim; ++i) {
            // generate reference sample
            std::generate(reference_sample.begin(), reference_sample.end(),
                          [&ic_distribution, &lrng]() { return ic_distribution(lrng);});
            reference_sample_means[i] = mean(reference_sample);
            reference_sample_sds[i] = standard_deviation(reference_sample);
            // ic_variate_generator(lrng, reference_sample);
            unsigned run_length = 0;
            double stat;
            bool lcl_signal = false;
            bool ucl_signal = false;
            do {
                run_length++;
                // generate test sample as if the process was IC
                std::generate(test_sample.begin(), test_sample.end(),
                              [&ic_distribution, &lrng]() { return ic_distribution(lrng);});
                // ic_variate_generator(lrng, test_sample);
                // apply location shift and scale multiplier
                std::transform(test_sample.begin(),
                               test_sample.end(),
                               test_sample.begin(),
                               [location_shift, scale_multiplier](double x) -> double { return (x * scale_multiplier) + location_shift; });
                // compute monitoring statistic
                stat = ms(reference_sample, test_sample, lrng);
                if (lcl) {
                    lcl_signal = (stat <= lcl.value());
                }
                if (ucl) {
                    ucl_signal = (stat >= ucl.value());
                }
            } while (!lcl_signal and !ucl_signal and run_length < run_length_cap);
            run_lengths[i] = run_length;
        }
    }
    // advance by ncores jumps
    global_rng::instance.long_jump(omp_get_max_threads());
    return uncoditional_evaluation_result(
            std::move(run_lengths),
            std::move(reference_sample_means),
            std::move(reference_sample_sds)
    );
}


