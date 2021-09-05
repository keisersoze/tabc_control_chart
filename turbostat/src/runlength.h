//
// Created by filip on 20/08/2021.
//

#ifndef RACE_RUNLENGTH_H
#define RACE_RUNLENGTH_H

#include <Rcpp.h>

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
Rcpp::DataFrame  conditional_run_length_distribution_bootstrap(Rcpp::NumericVector reference_sample,
                                                               unsigned n,
                                                               unsigned nsim,
                                                               unsigned nperm,
                                                               Rcpp::NumericVector shifts,
                                                               double LCL,
                                                               const std::string &test,
                                                               unsigned run_length_cap,
                                                               unsigned seed);


#endif //RACE_RUNLENGTH_H
