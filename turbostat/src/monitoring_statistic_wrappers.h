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

typedef std::function<multiaspect_phase_1_result (const std::vector<double> &,
                                                  const std::vector<double> &,
                                                  unsigned B,
                                                  dqrng::xoroshiro128plus &)> multiaspect_test_phase_1;

class multiaspect_obs_value_monitoring_statistic{
private:
    multiaspect_test_phase_1 mtp1;
    unsigned B;
public:
    multiaspect_obs_value_monitoring_statistic(const multiaspect_test_phase_1 &pt, unsigned B);

    double operator () (const std::vector<double> &x1,
                        const std::vector<double> &x2,
                        dqrng::xoroshiro128plus &rng);
};


typedef std::function<double (const std::vector<double> &,
                              const std::vector<double> &)> simple_statistic;

class simple_monitoring_statistic{
private:
    simple_statistic s;
public:
    simple_monitoring_statistic(const simple_statistic &s);

    double operator () (const std::vector<double> &x1,
                        const std::vector<double> &x2,
                        dqrng::xoroshiro128plus &rng);
};



#endif //RACE_TEST_DISPATCHING_H
