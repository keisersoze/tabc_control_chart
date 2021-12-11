//
// Created by filip on 11/12/2021.
//

#ifndef RACE_STATISTIC_INTERFACE_H
#define RACE_STATISTIC_INTERFACE_H

#include <vector>
#include <functional>

typedef std::function<double (const std::vector<double> &,
                              const std::vector<double> &)> simple_statistic;

#endif //RACE_STATISTIC_INTERFACE_H
