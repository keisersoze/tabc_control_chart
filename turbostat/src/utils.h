//
// Created by filip on 22/08/2021.
//

#ifndef RACE_UTILS_H
#define RACE_UTILS_H

#include <Rcpp.h>

#include <xoshiro.h>

Rcpp::NumericVector avg_rank(Rcpp::NumericVector x);

Rcpp::IntegerVector order(Rcpp::NumericVector v);

Rcpp::IntegerVector order(Rcpp::IntegerVector v);

Rcpp::NumericVector sample_with_replacement(Rcpp::NumericVector v, unsigned sample_size, dqrng::xoroshiro128plus &rng);

#endif //RACE_UTILS_H
