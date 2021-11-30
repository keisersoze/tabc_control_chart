//
// Created by filip on 28/11/2021.
//

#ifndef RACE_FAST_PERMTEST_H
#define RACE_FAST_PERMTEST_H

#include <vector>


#include "monitoring_statistic_wrappers.h"
#include "test_interface.h"

std::vector<double> generate_permutation_distribution(unsigned m,
                                                      unsigned n,
                                                      unsigned n_perm,
                                                      const simple_statistic &s,
                                                      dqrng::xoshiro256plus &rng);

class fast_permtest{
private:
    std::vector<double> permutation_distribution;
    simple_statistic s;
    std::function<bool (const double&, const double&)> comparator;
public:
    fast_permtest(const simple_statistic &s,
                  const std::vector<double> &permutation_distribution,
                  const std::string &tail_key);

    double operator () (const std::vector<double> &x1,
                        const std::vector<double> &x2,
                        dqrng::xoshiro256plus &rng);
};

class npc_df_chart{
private:
    std::vector<fast_permtest> perm_tests;
public:
    npc_df_chart(const std::vector<fast_permtest> &perm_tests);

    double operator () (const std::vector<double> &x1,
                        const std::vector<double> &x2,
                        dqrng::xoshiro256plus &rng);
};


#endif //RACE_FAST_PERMTEST_H
