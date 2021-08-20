//
// Created by filip on 20/08/2021.
//

#include "runlength.h"
#include "../stat/Ta.h"


double testA(NumericVector x1, NumericVector x2, int B) {
    std::vector<double> x1_c(x1.size());
    for (int j = 0; j < x1.size(); ++j) {
        x1_c[j] = x1[j];
    }
    std::vector<double> x2_c(x2.size());
    for (int j = 0; j < x2.size(); ++j) {
        x2_c[j] = x2[j];
    }
    std::pair<double, double> pair = test_A(x1_c, x2_c, B);
    return NumericVector::create(pair.second ,pair.first);
}

NumericVector
unconditional_run_length_distribution(unsigned int n,
                                      NumericVector phaseI_sample,
                                      unsigned int nsim,
                                      double LCL) {
    Ta ta (1000, 42);
    unsigned m = phaseI_sample.size();
    NumericVector run_lengths(nsim);
    for (int j = 0; j < ; ++j) {
        NumericVector phaseI_sample_boot = Rcpp::sample(phaseI_sample, m);
        unsigned run_length = 0;
        for (;;) {
            NumericVector test_sample = Rcpp::sample(phaseI_sample, n);
            double plotting_stat = testA(phaseI_sample_boot, test_sample);
            if (plotting_stat > LCL){

            } else{
                
            }

        }
    }

    return vector<double>();
}
