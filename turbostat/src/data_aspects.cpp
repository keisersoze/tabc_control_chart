//
// Created by filip on 03/09/2021.
//

#include "data_aspects.h"
#include "utils.h"

Rcpp::NumericVector a_aspect(Rcpp::NumericVector pooled_sample){
    return pooled_sample;
}

Rcpp::NumericVector b_aspect(Rcpp::NumericVector pooled_sample){
    double median = Rcpp::median(pooled_sample);
    return Rcpp::ifelse( pooled_sample >= median, 1.0, 0.0);
}

Rcpp::NumericVector c_aspect(Rcpp::NumericVector pooled_sample){
    return avg_rank(pooled_sample);
}
