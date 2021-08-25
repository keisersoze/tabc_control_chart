//
// Created by filip on 25/08/2021.
//

#include "runlength.h"
#include "utils.h"

double testCExact(Rcpp::NumericVector x1, Rcpp::NumericVector x2) {
    const unsigned m = x1.size();
    const unsigned n = x2.size();
    Rcpp::NumericVector pooled_sample(x1.size() + x2.size());
    for (int i = 0; i < m; ++i) {
        pooled_sample[i] = x1[i];
    }
    for (int i = 0; i < n ; ++i) {
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

double
unconditional_run_length_distribution(unsigned int n,
                                      Rcpp::NumericVector phaseI_sample,
                                      unsigned int nsim,
                                      double LCL,
                                      unsigned run_length_cap) {
    unsigned m = phaseI_sample.size();
    Rcpp::NumericVector run_lengths(nsim);
    for (unsigned i = 0; i < nsim; ++i) {
        Rcpp::NumericVector phaseI_sample_boot = Rcpp::sample(phaseI_sample, m, true);
        unsigned run_length = 0;
        for (;;) {
            Rcpp::NumericVector test_sample = Rcpp::sample(phaseI_sample, n);
            double plotting_stat = testCExact(phaseI_sample_boot, test_sample);
            if (plotting_stat > LCL and run_length <= run_length_cap){
                run_length ++;
            } else{
                break;
            }
        }
        run_lengths[i]= run_length;
    }
    return Rcpp::mean(run_lengths);
}

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


