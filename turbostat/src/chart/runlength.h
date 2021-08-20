//
// Created by filip on 20/08/2021.
//

#ifndef RACE_RUNLENGTH_H
#define RACE_RUNLENGTH_H

#include <Rcpp.h>

NumericVector unconditional_run_length_distribution (unsigned n,
                                unsigned m,
                                NumericVector shift_seq,
                                unsigned nsim,
                                double LCL,
                                double UCL);

#endif //RACE_RUNLENGTH_H
