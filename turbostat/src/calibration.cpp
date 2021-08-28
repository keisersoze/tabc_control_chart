//
// Created by filip on 27/08/2021.
//

#include "calibration.h"
#include "test_dispatching.h"

double find_UCL(Rcpp::NumericVector reference_sample,
                unsigned n,
                double target_ARL,
                unsigned nsim,
                unsigned nperm,
                const std::string &test){
    test_fun_ptr test_f = dispatch_from_string(test);
    double type_1_error_prob = 1/target_ARL;
    unsigned n_iterations = target_ARL * nsim;
    Rcpp::NumericVector stats(n_iterations);
    for (unsigned i = 0; i < n_iterations; ++i) {
        Rcpp::NumericVector test_sample_boot = Rcpp::sample(reference_sample, n, true);
        stats[i] = test_f(reference_sample,test_sample_boot, nperm)[1];
    }
    stats.sort();
    double LCL = stats[(int)round(stats.size() * type_1_error_prob)];
    return LCL;
}