//
// Created by filip on 27/08/2021.
//

#ifndef RACE_CALIBRATION_H
#define RACE_CALIBRATION_H

#include "distribution.h"
#include "monitoring_statistic.h"

#include <vector>

//Rcpp::List find_ucl_conditional(const std::vector<double> &reference_sample,
//                                unsigned n,
//                                double target_ARL,
//                                unsigned nsim,
//                                unsigned nperm,
//                                const std::string &test);

double conditional_unidirectional_calibration(const std::vector<double> &reference_sample,
                                              unsigned n,
                                              const monitoring_statistic &ms,
                                              bool upper_limit,
                                              double target_ARL,
                                              unsigned nsim);

std::vector<std::vector<int>> unconditional_unidirectional_calibration(unsigned m,
                                                                       unsigned n,
                                                                       const distribution &ic_distribution,
                                                                       const monitoring_statistic &ms,
                                                                       const std::vector<double> &limits_seq,
                                                                       bool upper_limit,
                                                                       unsigned nsim,
                                                                       unsigned run_length_cap);

#endif //RACE_CALIBRATION_H
