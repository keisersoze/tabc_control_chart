//
// Created by filip on 22/08/2021.
//

#ifndef RACE_TURBOTABC_H
#define RACE_TURBOTABC_H

#include <Rcpp.h>
#include <xoshiro.h>


//' Tabc permutation test
//'
//' Compute approximated pvalue for the Tabc test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
//' @export
// [[Rcpp::export(permtest.tabc)]]
Rcpp::NumericVector t_abc_permtest (Rcpp::NumericVector x1,
                                    Rcpp::NumericVector x2,
                                    unsigned B,
                                    unsigned seed);

Rcpp::NumericVector t_abc_permtest_impl (Rcpp::NumericVector x1,
                                         Rcpp::NumericVector x2,
                                         unsigned B,
                                         dqrng::xoroshiro128plus &rng);

#endif //RACE_TURBOTABC_H
