//
// Created by filip on 20/08/2021.
//

#ifndef RACE_RUNLENGTH_H
#define RACE_RUNLENGTH_H

#include "distribution.h"
#include "monitoring_statistic.h"

#include <vector>

//Rcpp::DataFrame conditional_run_length_distribution_bootstrap(const std::vector<double> &reference_sample,
//                                                              unsigned n,
//                                                              unsigned nsim,
//                                                              unsigned nperm,
//                                                              const std::vector<double> &shifts,
//                                                              double LCL,
//                                                              const std::string &test,
//                                                              unsigned run_length_cap);

std::vector<std::vector<unsigned>> conditional_unidirectional_evaluation(const std::vector<double> &reference_sample,
                                                                         unsigned n,
                                                                         double limit,
                                                                         bool upper_limit,
                                                                         const std::vector<double> &shifts,
                                                                         const monitoring_statistic &ms,
                                                                         unsigned nsim,
                                                                         unsigned run_length_cap);

std::vector<std::vector<unsigned>> unconditional_unidirectional_evaluation(unsigned m,
                                                                           unsigned n,
                                                                           double limit,
                                                                           bool upper_limit,
                                                                           const std::vector<double> &shifts,
                                                                           const distribution &ic_distribution,
                                                                           const monitoring_statistic &ms,
                                                                           unsigned nsim,
                                                                           unsigned run_length_cap);

std::vector<std::vector<unsigned>> unconditional_unidirectional_evaluation_scale(unsigned m,
                                                                                 unsigned n,
                                                                                 double limit,
                                                                                 bool upper_limit,
                                                                                 const std::vector<double> &scale_multipliers,
                                                                                 const distribution &ic_distribution,
                                                                                 const monitoring_statistic &ms,
                                                                                 unsigned nsim,
                                                                                 unsigned run_length_cap);

std::vector<std::vector<unsigned>> unconditional_unidirectional_evaluation_location_scale(unsigned m,
                                                                                          unsigned n,
                                                                                          double limit,
                                                                                          bool upper_limit,
                                                                                          const std::vector<std::pair<double,double>> &location_scale_changes,
                                                                                          const distribution &ic_distribution,
                                                                                          const monitoring_statistic &ms,
                                                                                          unsigned nsim,
                                                                                          unsigned run_length_cap);


#endif //RACE_RUNLENGTH_H
