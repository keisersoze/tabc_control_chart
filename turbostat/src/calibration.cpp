//
// Created by filip on 27/08/2021.
//

#include "calibration.h"
#include "test_dispatching.h"
#include "utils.h"

#include <xoshiro.h>

Rcpp::List find_UCL(Rcpp::NumericVector reference_sample,
                unsigned n,
                double target_ARL,
                unsigned nsim,
                unsigned nperm,
                const std::string &test,
                unsigned seed){
    test_fun_ptr test_f = dispatch_from_string(test);
    // double type_1_error_prob = 1.0 / (double) target_ARL;
    unsigned n_iterations = target_ARL * nsim;
    Rcpp::NumericVector counts(nperm + 1);
    dqrng::xoroshiro128plus rng(seed);
    for (unsigned i = 0; i < n_iterations; ++i) {
        Rcpp::NumericVector test_sample_boot = sample_with_replacement(reference_sample, n, rng);
        unsigned position = test_f(reference_sample,test_sample_boot, nperm, rng)[2];
        counts[position] ++ ;
    }
    unsigned tot_count = 0;
    unsigned i = 0;
    unsigned max_type_1_error_counts = nsim; // (double) target_ARL * nsim * type_1_error_prob; (equal to nsim)
    while (tot_count <= max_type_1_error_counts) {
        tot_count += counts[i];
        i++;
    }
    double LCL = (double) (i - 1) / (double) nperm;
    return Rcpp::List::create(Rcpp::Named("LCL") = LCL,
                              Rcpp::Named("distribution") = counts );
}