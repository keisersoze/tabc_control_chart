//
// Created by filip on 07/09/2021.
//

#ifndef RACE_TEST_INTERFACE_H
#define RACE_TEST_INTERFACE_H

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


#endif //RACE_TEST_INTERFACE_H
