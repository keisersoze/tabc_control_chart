//
// Created by filip on 09/10/2021.
//

#ifndef RACE_SIMPLE_STATS_H
#define RACE_SIMPLE_STATS_H

#include <vector>

double wilcoxon_rank_sum (const std::vector<double> &x1,
                          const std::vector<double> &x2);

double mann_whitney (const std::vector<double> &x1,
                     const std::vector<double> &x2);

double sum_of_signs (const std::vector<double> &x1,
                     const std::vector<double> &x2);

double difference_of_sums (const std::vector<double> &x1,
                           const std::vector<double> &x2);

double difference_of_means (const std::vector<double> &x1,
                            const std::vector<double> &x2);

double x2_sum (const std::vector<double> &x1,
               const std::vector<double> &x2);


#endif //RACE_SIMPLE_STATS_H
