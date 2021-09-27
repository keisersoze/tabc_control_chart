//
// Created by filip on 27/08/2021.
//

#ifndef RACE_TEST_DISPATCHING_H
#define RACE_TEST_DISPATCHING_H

#include <vector>

#include "monitoring_statistic.h"
#include "test_interface.h"

typedef std::function<perm_test_result (const std::vector<double> &,
                                        const std::vector<double> &,
                                        unsigned B,
                                        dqrng::xoroshiro128plus &)> permutation_test;


class permutation_pvalue_monitoring_statistic{
private:
    permutation_test pt;
    unsigned B;
public:
    permutation_pvalue_monitoring_statistic(const permutation_test &pt, unsigned B);

    double operator () (const std::vector<double> &x1,
                        const std::vector<double> &x2,
                        dqrng::xoroshiro128plus &rng);
};


#endif //RACE_TEST_DISPATCHING_H
