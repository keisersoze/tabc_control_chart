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
std::vector<double> t_a_permtest (const std::vector<double> &x1,
                                  const std::vector<double> &x2,
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
std::vector<double> t_b_permtest (const std::vector<double> &x1,
                                  const std::vector<double> &x2,
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
std::vector<double> t_c_permtest (const std::vector<double> &x1,
                                  const std::vector<double> &x2,
                                  unsigned B,
                                  unsigned seed);

std::vector<double> t_a_permtest_impl (const std::vector<double> &x1,
                                       const std::vector<double> &x2,
                                       unsigned B,
                                       dqrng::xoroshiro128plus &rng);

std::vector<double> t_b_permtest_impl (const std::vector<double> &x1,
                                       const std::vector<double> &x2,
                                       unsigned B,
                                       dqrng::xoroshiro128plus &rng);

std::vector<double> t_c_permtest_impl (const std::vector<double> &x1,
                                       const std::vector<double> &x2,
                                       unsigned B,
                                       dqrng::xoroshiro128plus &rng);

#endif //RACE_SINGLE_ASPECT_H
