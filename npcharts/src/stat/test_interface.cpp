//
// Created by filip on 07/09/2021.
//

#include "test_interface.h"

test_result::test_result(double obs_stat, double p_value) : obs_stat(obs_stat), p_value(p_value) {}

perm_test_result::perm_test_result(double obs_stat, unsigned int n_perm, unsigned int pos)
        : test_result(obs_stat, (double) pos / (double) n_perm), n_perm(n_perm), pos(pos) {}

multiaspect_phase_1_result::multiaspect_phase_1_result(const std::vector<std::vector<double>> &aspects_perm_stats,
                                                       unsigned min_pos)
        : aspects_perm_stats(aspects_perm_stats), min_pos(min_pos) {}