//
// Created by filip on 20/08/2021.
//

#ifndef RACE_RUNLENGTH_H
#define RACE_RUNLENGTH_H

#include "../../stat/distribution.h"
#include "../monitoring_statistic.h"

#include <vector>
#include <optional>

std::vector<std::vector<unsigned>> conditional_unidirectional_evaluation(const std::vector<double> &reference_sample,
                                                                         unsigned n,
                                                                         double limit,
                                                                         bool upper_limit,
                                                                         const std::vector<double> &shifts,
                                                                         const monitoring_statistic &ms,
                                                                         unsigned nsim,
                                                                         unsigned run_length_cap);


struct uncoditional_evaluation_result {
    std::vector<unsigned> run_lengths;
    std::vector<double> reference_sample_means;
    std::vector<double> reference_sample_sds;

    uncoditional_evaluation_result(std::vector<unsigned int> &&run_lengths,
                                   std::vector<double> &&reference_sample_means,
                                   std::vector<double> &&reference_sample_sds);
};


uncoditional_evaluation_result unconditional_evaluation(unsigned m,
                                                        unsigned n,
                                                        const std::optional<double> &lcl,
                                                        const std::optional<double> &ucl,
                                                        double location_shift,
                                                        double scale_multiplier,
                                                        const distribution &ic_distribution,
                                                        const monitoring_statistic &ms,
                                                        unsigned nsim,
                                                        unsigned run_length_cap);


#endif //RACE_RUNLENGTH_H
