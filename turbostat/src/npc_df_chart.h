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
    bool is_two_sided;
public:
    fast_permtest(const simple_statistic &s,
                  const std::vector<double> &permutation_distribution,
                  const std::string &tail_key);

    double operator () (const std::vector<double> &x1,
                        const std::vector<double> &x2,
                        dqrng::xoshiro256plus &rng);
};

typedef std::function<double (const std::vector<double> &)> combining_function;

double tippet(const std::vector<double> &p_values);
double fisher(const std::vector<double> &p_values);
double liptak(const std::vector<double> &p_values);

class npc_df_chart{
private:
    std::vector<fast_permtest> perm_tests;
    combining_function cf;
public:
    npc_df_chart(const std::vector<fast_permtest> &perm_tests, const combining_function &cf);

    double operator () (const std::vector<double> &x1,
                        const std::vector<double> &x2,
                        dqrng::xoshiro256plus &rng);
};


#endif //RACE_FAST_PERMTEST_H
