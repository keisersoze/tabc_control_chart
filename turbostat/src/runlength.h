//
// Created by filip on 20/08/2021.
//

#ifndef RACE_RUNLENGTH_H
#define RACE_RUNLENGTH_H

#include <Rcpp.h>

double testCExact(Rcpp::NumericVector x1, Rcpp::NumericVector x2);

double
unconditional_run_length_distribution(unsigned int n,
                                      Rcpp::NumericVector phaseI_sample,
                                      unsigned int nsim,
                                      double LCL,
                                      unsigned run_length_cap);


//' Test UCL
//'
//' Compute approximated pvalue for the Tb test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
//' @export
// [[Rcpp::export(rl.conditional)]]
double conditional_run_length_distribution(Rcpp::NumericVector reference_sample,
                                           unsigned n,
                                           double target_ARL,
                                           unsigned nsim,
                                           unsigned nperm,
                                           double LCL,
                                           const std::string &test);


#endif //RACE_RUNLENGTH_H
