//
// Created by filip on 27/08/2021.
//

#ifndef RACE_TEST_DISPATCHING_H
#define RACE_TEST_DISPATCHING_H

#include "Rcpp.h"

#include <xoshiro.h>

typedef Rcpp::NumericVector (*test_fun_ptr) (Rcpp::NumericVector x1,
                                             Rcpp::NumericVector x2,
                                             unsigned B,
                                             dqrng::xoroshiro128plus &rng);

test_fun_ptr dispatch_from_string(const std::string &s);

#endif //RACE_TEST_DISPATCHING_H
