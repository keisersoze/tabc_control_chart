//
// Created by filip on 27/09/2021.
//

#ifndef RACE_MONITORING_STATISTIC_H
#define RACE_MONITORING_STATISTIC_H

#include <vector>
#include <xoshiro.h>

typedef std::function<double (const std::vector<double> &,
                              const std::vector<double> &,
                              dqrng::xoroshiro128plus &)> monitoring_statistic;

#endif //RACE_MONITORING_STATISTIC_H


