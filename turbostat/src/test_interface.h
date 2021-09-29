//
// Created by filip on 07/09/2021.
//

#ifndef RACE_TEST_INTERFACE_H
#define RACE_TEST_INTERFACE_H

#include <vector>

struct test_result {
    double obs_stat;
    double p_value;

    test_result(double obs_stat, double p_value);

};

struct perm_test_result : public test_result {
    unsigned n_perm;
    unsigned pos;

    perm_test_result(double obs_stat, unsigned int n_perm, unsigned int pos);

};

struct multiaspect_phase_1_result {
    std::vector<std::vector<double>> aspects_perm_stats;
    unsigned min_pos;

    multiaspect_phase_1_result(const std::vector<std::vector<double>>  &aspects_perm_stats,
                   unsigned min_pos);
};



#endif //RACE_TEST_INTERFACE_H
