//
// Created by filip on 27/08/2021.
//

#ifndef RACE_TEST_DISPATCHING_H
#define RACE_TEST_DISPATCHING_H

#include <vector>
#include <xoshiro.h>

#include "test_interface.h"

typedef perm_test_result (*test_fun_ptr)(const std::vector<double> &x1,
                                         const std::vector<double> &x2,
                                         unsigned B,
                                         dqrng::xoroshiro128plus &rng);

test_fun_ptr dispatch_from_string(const std::string &s);

#endif //RACE_TEST_DISPATCHING_H
