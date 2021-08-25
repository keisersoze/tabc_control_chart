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


#endif //RACE_RUNLENGTH_H
