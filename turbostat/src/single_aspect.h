//
// Created by filip on 23/08/2021.
//

#ifndef RACE_SINGLE_ASPECT_H
#define RACE_SINGLE_ASPECT_H

#include <Rcpp.h>
#include <xoshiro.h>


//' Ta permutation test
//'
//' Compute approximated pvalue for the Ta test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
//' @export
// [[Rcpp::export(permtest.ta)]]
Rcpp::NumericVector t_a_permtest (Rcpp::NumericVector x1,
                                  Rcpp::NumericVector x2,
                                  unsigned B,
                                  unsigned seed);

//' Tb permutation test
//'
//' Compute approximated pvalue for the Tb test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
//' @export
// [[Rcpp::export(permtest.tb)]]
Rcpp::NumericVector t_b_permtest (Rcpp::NumericVector x1,
                                  Rcpp::NumericVector x2,
                                  unsigned B,
                                  unsigned seed);

//' Tc permutation test
//'
//' Compute approximated pvalue for the Tc test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
//' @export
// [[Rcpp::export(permtest.tc)]]
Rcpp::NumericVector t_c_permtest (Rcpp::NumericVector x1,
                                  Rcpp::NumericVector x2,
                                  unsigned B,
                                  unsigned seed);

Rcpp::NumericVector t_a_permtest_impl (Rcpp::NumericVector x1,
                                       Rcpp::NumericVector x2,
                                       unsigned B,
                                       dqrng::xoroshiro128plus &rng);

Rcpp::NumericVector t_b_permtest_impl (Rcpp::NumericVector x1,
                                       Rcpp::NumericVector x2,
                                       unsigned B,
                                       dqrng::xoroshiro128plus &rng);

Rcpp::NumericVector t_c_permtest_impl (Rcpp::NumericVector x1,
                                       Rcpp::NumericVector x2,
                                       unsigned B,
                                       dqrng::xoroshiro128plus &rng);

#endif //RACE_SINGLE_ASPECT_H
