//
// Created by filip on 23/08/2021.
//

#ifndef RACE_SINGLE_ASPECT_H
#define RACE_SINGLE_ASPECT_H

#include <Rcpp.h>

Rcpp::NumericVector t_a_permtest (Rcpp::NumericVector x1,
                                  Rcpp::NumericVector x2,
                                  unsigned B);

Rcpp::NumericVector t_b_permtest (Rcpp::NumericVector x1,
                                  Rcpp::NumericVector x2,
                                  unsigned B);

Rcpp::NumericVector t_c_permtest (Rcpp::NumericVector x1,
                                  Rcpp::NumericVector x2,
                                  unsigned B);
#endif //RACE_SINGLE_ASPECT_H
