//
// Created by filip on 20/08/2021.
//

#ifndef RACE_RUNLENGTH_H
#define RACE_RUNLENGTH_H

#include <Rcpp.h>

#include "distribution.h"

double testCExact(Rcpp::NumericVector x1, Rcpp::NumericVector x2);


//' Test UCL
//'
//' Compute approximated pvalue for the Tb test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
//' @export
// [[Rcpp::export(rl.conditional)]]
Rcpp::DataFrame conditional_run_length_distribution_bootstrap(const std::vector<double> &reference_sample,
                                                              unsigned n,
                                                              unsigned nsim,
                                                              unsigned nperm,
                                                              const std::vector<double> &shifts,
                                                              double LCL,
                                                              const std::string &test,
                                                              unsigned run_length_cap);

std::vector<std::vector<unsigned>> unconditional_unidirectional_evaluation(unsigned m,
                                                                           unsigned n,
                                                                           const distribution &ic_distribution,
                                                                           unsigned nsim,
                                                                           unsigned nperm,
                                                                           const std::vector<double> &shifts,
                                                                           double LCL,
                                                                           const std::string &chart,
                                                                           unsigned run_length_cap);


#endif //RACE_RUNLENGTH_H
