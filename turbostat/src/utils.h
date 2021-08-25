//
// Created by filip on 22/08/2021.
//

#ifndef RACE_UTILS_H
#define RACE_UTILS_H

#include <Rcpp.h>

Rcpp::NumericVector avg_rank(Rcpp::NumericVector x);

Rcpp::IntegerVector order(Rcpp::NumericVector v);

Rcpp::IntegerVector order(Rcpp::IntegerVector v);

#endif //RACE_UTILS_H
