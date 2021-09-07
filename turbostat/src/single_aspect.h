//
// Created by filip on 23/08/2021.
//

#ifndef RACE_SINGLE_ASPECT_H
#define RACE_SINGLE_ASPECT_H

#include <vector>

#include <xoshiro.h>
#include "test_result.h"


perm_test_result t_a_permtest (const std::vector<double> &x1,
                                       const std::vector<double> &x2,
                                       unsigned n_perm,
                                       dqrng::xoroshiro128plus &rng);

perm_test_result t_b_permtest (const std::vector<double> &x1,
                                       const std::vector<double> &x2,
                                       unsigned n_perm,
                                       dqrng::xoroshiro128plus &rng);

perm_test_result t_c_permtest (const std::vector<double> &x1,
                                       const std::vector<double> &x2,
                                       unsigned n_perm,
                                       dqrng::xoroshiro128plus &rng);

#endif //RACE_SINGLE_ASPECT_H
