//
// Created by filip on 22/08/2021.
//

#ifndef RACE_TURBOTABC_H
#define RACE_TURBOTABC_H

#include <Rcpp.h>

double t_abc_permtest (Rcpp::NumericVector x1,
                       Rcpp::NumericVector x2,
                       unsigned B);

#endif //RACE_TURBOTABC_H
