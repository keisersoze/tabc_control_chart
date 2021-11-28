//
// Created by filip on 28/11/2021.
//

#ifndef RACE_FAST_PERMTEST_H
#define RACE_FAST_PERMTEST_H

#include <vector>


#include "monitoring_statistic_wrappers.h"
#include "test_interface.h"

class fast_permtest{
private:
    std::vector<double> perm_stats;
    simple_statistic s;
public:
    fast_permtest(unsigned m,
                  unsigned n,
                  unsigned n_perm,
                  const simple_statistic &s,
                  dqrng::xoshiro256plus &rng);

    double operator () (const std::vector<double> &x1,
                        const std::vector<double> &x2,
                        dqrng::xoshiro256plus &rng);
};

#endif //RACE_FAST_PERMTEST_H
