//
// Created by filip on 27/08/2021.
//

#ifndef RACE_CALIBRATION_H
#define RACE_CALIBRATION_H
#include "Rcpp.h"

struct calibration_result {

    double LCL;

    calibration_result(double LCL);

};

//' Find UCL
//'
//' Compute approximated pvalue for the Tb test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
//' @export
// [[Rcpp::export(find_UCL)]]
Rcpp::List find_ucl_conditional(const std::vector<double> &reference_sample,
                                        unsigned n,
                                        double target_ARL,
                                        unsigned nsim,
                                        unsigned nperm,
                                        const std::string &test);

// [[Rcpp::export(calibrate.uncoditional)]]
Rcpp::NumericMatrix find_lcl_uncoditional(unsigned m,
                                          unsigned n,
                                          unsigned nsim,
                                          unsigned nperm,
                                          const std::vector<double> &lcl_seq,
                                          const std::string &test,
                                          unsigned run_length_cap);

#endif //RACE_CALIBRATION_H
