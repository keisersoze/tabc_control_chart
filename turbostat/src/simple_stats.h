//
// Created by filip on 09/10/2021.
//

#ifndef RACE_SIMPLE_STATS_H
#define RACE_SIMPLE_STATS_H

#include <vector>

double wilcoxon_rank_sum (const std::vector<double> &x1,
                          const std::vector<double> &x2);

double difference_of_rank_means (const std::vector<double> &x1,
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

double x2_mean (const std::vector<double> &x1,
                const std::vector<double> &x2);

double precedence (const std::vector<double> &x1,
                   const std::vector<double> &x2);

double sum_of_signs_v2 (const std::vector<double> &x1,
                        const std::vector<double> &x2);

double conover_statistic (const std::vector<double> &x1,
                          const std::vector<double> &x2);

double mood_statistic (const std::vector<double> &x1,
                       const std::vector<double> &x2);

double ab_statistic (const std::vector<double> &x1,
                     const std::vector<double> &x2);

double difference_of_means_ab_statistic (const std::vector<double> &x1,
                                         const std::vector<double> &x2);

double klotz_statistic (const std::vector<double> &x1,
                        const std::vector<double> &x2);

double difference_of_means_klotz (const std::vector<double> &x1,
                                  const std::vector<double> &x2);

double fab_statistic (const std::vector<double> &x1,
                      const std::vector<double> &x2);

double lepage (const std::vector<double> &x1,
               const std::vector<double> &x2);

#endif //RACE_SIMPLE_STATS_H
