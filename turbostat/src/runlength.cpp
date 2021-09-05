//
// Created by filip on 25/08/2021.
//

#include "runlength.h"
#include "utils.h"
#include "test_dispatching.h"
#include "utils.h"

#include <xoshiro.h>


double testCExact(Rcpp::NumericVector x1, Rcpp::NumericVector x2) {
    const unsigned m = x1.size();
    const unsigned n = x2.size();
    Rcpp::NumericVector pooled_sample(x1.size() + x2.size());
    for (unsigned i = 0; i < m; ++i) {
        pooled_sample[i] = x1[i];
    }
    for (unsigned i = 0; i < n ; ++i) {
        pooled_sample[x1.size() + i] = x2[i];
    }
    // Rcpp::print(pooled_sample);
    Rcpp::NumericVector ranks = avg_rank(pooled_sample);
    // Rcpp::print(ranks);
    unsigned sum_of_x2_ranks = std::accumulate(ranks.begin(), ranks.begin() + m, 0.0);
    double obs_stat = sum_of_x2_ranks - m * (m + 1)/2;
    // Rcpp::Rcout << obs_stat << std::endl;
    return R::pwilcox( obs_stat, m, n, true, false);

}

//double
//unconditional_run_length_distribution(unsigned int n,
//                                      Rcpp::NumericVector phaseI_sample,
//                                      unsigned int nsim,
//                                      double LCL,
//                                      unsigned run_length_cap) {
//    unsigned m = phaseI_sample.size();
//    Rcpp::NumericVector run_lengths(nsim);
//    for (unsigned i = 0; i < nsim; ++i) {
//        Rcpp::NumericVector phaseI_sample_boot = Rcpp::sample(phaseI_sample, m, true);
//        unsigned run_length = 0;
//        for (;;) {
//            Rcpp::NumericVector test_sample = Rcpp::sample(phaseI_sample, n);
//            double plotting_stat = testCExact(phaseI_sample_boot, test_sample);
//            if (plotting_stat > LCL and run_length <= run_length_cap){
//                run_length ++;
//            } else{
//                break;
//            }
//        }
//        run_lengths[i]= run_length;
//    }
//    return Rcpp::mean(run_lengths);
//}

//double
//unconditional_arl_distribution_free_charts(unsigned int n,
//                                           unsigned int m,
//                                           unsigned int nsim,
//                                           double LCL,
//                                           unsigned run_length_cap) {
//    Rcpp::NumericVector run_lengths(nsim);
//    for (unsigned i = 0; i < nsim; ++i) {
//        Rcpp::NumericVector phaseI_sample_boot = Rcpp::rnorm(phaseI_sample, m, true);
//        unsigned run_length = 0;
//        for (;;) {
//            Rcpp::NumericVector test_sample = Rcpp::sample(phaseI_sample, n);
//            double plotting_stat = testCExact(phaseI_sample_boot, test_sample);
//            if (plotting_stat > LCL and run_length <= run_length_cap){
//                run_length ++;
//            } else{
//                break;
//            }
//        }
//        run_lengths[i]= run_length;
//    }
//    return Rcpp::mean(run_lengths);
//}

Rcpp::DataFrame  conditional_run_length_distribution_bootstrap(Rcpp::NumericVector reference_sample,
                                                     unsigned n,
                                                     unsigned nsim,
                                                     unsigned nperm,
                                                     Rcpp::NumericVector shifts,
                                                     double LCL,
                                                     const std::string &test,
                                                     unsigned run_length_cap,
                                                     unsigned seed) {
    Rcpp::NumericVector arls(shifts.size());
    Rcpp::NumericVector sds(shifts.size());
    test_fun_ptr test_f = dispatch_from_string(test);
    dqrng::xoroshiro128plus rng(seed);
    for (int shift_index = 0; shift_index < shifts.size(); ++shift_index) {
        double shift = shifts[shift_index];
        Rcpp::NumericVector run_lengths(nsim);
        Rcpp::NumericVector shifted_reference_sample = reference_sample + shift;
        for (unsigned i = 0; i < nsim; ++i) {
            unsigned run_length = 0;
            double stat;
            do {
                run_length ++;
                Rcpp::NumericVector test_sample_boot = sample_with_replacement(shifted_reference_sample, n, rng);
                stat = test_f(reference_sample, test_sample_boot, nperm, rng)[1];
            } while (stat > LCL and run_length <= run_length_cap );
            run_lengths[i] = run_length;
        }
        arls[shift_index] = Rcpp::mean(run_lengths);
        sds[shift_index] = Rcpp::sd(run_lengths);
    }
    Rcpp::DataFrame result = Rcpp::DataFrame::create(Rcpp::Named("ARLs") = arls,
                                                     Rcpp::Named("Standard deviations") = sds);
    return result;
}


//Rcpp::NumericVector uncoditional_find_UCL (unsigned m,
//                              unsigned n,
//                              Rcpp::NumericVector UCLs,
//                              unsigned w ,
//                              Rcpp::NumericVector (*sampling_func)(unsigned )){
//    Rcpp::NumericVector reference_sample = sampling_func(m);
//
//
//
//}
//


