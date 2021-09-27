//
// Created by filip on 27/08/2021.
//

#include "permutation_monitoring_statistic.h"

#include "single_aspect.h"
#include "multiple_aspects.h"

#include <map>

permutation_pvalue_monitoring_statistic::permutation_pvalue_monitoring_statistic(const permutation_test &pt,
                                                                                 unsigned B)
                                                                                 : pt(pt), B(B){}


double permutation_pvalue_monitoring_statistic::operator () (const std::vector<double> &x1,
                                                             const std::vector<double> &x2,
                                                             dqrng::xoroshiro128plus &rng) {
    perm_test_result res = this->pt(x1, x2, this->B, rng);
    return res.p_value;
}