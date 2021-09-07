//
// Created by filip on 27/08/2021.
//

#ifndef RACE_CALIBRATION_H
#define RACE_CALIBRATION_H
#include "Rcpp.h"

//' Find UCL
//'
//' Compute approximated pvalue for the Tb test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
//' @export
// [[Rcpp::export(find_UCL)]]
Rcpp::List find_UCL(Rcpp::NumericVector reference_sample,
                unsigned n,
                double target_ARL,
                unsigned nsim,
                unsigned nperm,
                const std::string &test,
                unsigned seed);

#endif //RACE_CALIBRATION_H
