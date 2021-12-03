//
// Created by filip on 27/08/2021.
//

#include "monitoring_statistic_wrappers.h"

#include "../stat/tests/single_aspect.h"
#include "../stat/tests/multiple_aspects.h"

#include <map>

permutation_pvalue_monitoring_statistic::permutation_pvalue_monitoring_statistic(const permutation_test &pt,
                                                                                 unsigned B)
        : pt(pt), B(B) {}


double permutation_pvalue_monitoring_statistic::operator()(const std::vector<double> &x1,
                                                           const std::vector<double> &x2,
                                                           dqrng::xoshiro256plus &rng) {
    perm_test_result res = this->pt(x1, x2, this->B, rng);
    return res.p_value;
}

multiaspect_obs_value_monitoring_statistic::multiaspect_obs_value_monitoring_statistic(
        const multiaspect_test_phase_1 &mtp1,
        unsigned B)
        : mtp1(mtp1), B(B) {}


double multiaspect_obs_value_monitoring_statistic::operator()(const std::vector<double> &x1,
                                                              const std::vector<double> &x2,
                                                              dqrng::xoshiro256plus &rng) {
    multiaspect_phase_1_result res = this->mtp1(x1, x2, this->B, rng);
    return (double) res.min_pos / (double) (this->B);
}


simple_monitoring_statistic::simple_monitoring_statistic(const simple_statistic &s) : s(s) {}


double simple_monitoring_statistic::operator()(const std::vector<double> &x1,
                                               const std::vector<double> &x2,
                                               dqrng::xoshiro256plus &rng) {
    return s(x1, x2);
}