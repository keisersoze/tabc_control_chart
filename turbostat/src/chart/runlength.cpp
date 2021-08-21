//
// Created by filip on 20/08/2021.
//

#include "runlength.h"

class Comparator {
private:
    const Rcpp::NumericVector& ref;

    bool is_na(double x) const
    {
        return Rcpp::traits::is_na<REALSXP>(x);
    }

public:
    Comparator(const Rcpp::NumericVector& ref_)
            : ref(ref_)
    {}

    bool operator()(const int ilhs, const int irhs) const
    {
        double lhs = ref[ilhs], rhs = ref[irhs];
        if (is_na(lhs)) return false;
        if (is_na(rhs)) return true;
        return lhs < rhs;
    }
};

Rcpp::NumericVector avg_rank(Rcpp::NumericVector x)
{
    R_xlen_t sz = x.size();
    Rcpp::IntegerVector w = Rcpp::seq(0, sz - 1);
    std::sort(w.begin(), w.end(), Comparator(x));

    Rcpp::NumericVector r = Rcpp::no_init_vector(sz);
    for (R_xlen_t n, i = 0; i < sz; i += n) {
        n = 1;
        while (i + n < sz && x[w[i]] == x[w[i + n]]) ++n;
        for (R_xlen_t k = 0; k < n; k++) {
            r[w[i + k]] = i + (n + 1) / 2.;
        }
    }

    return r;
}

double testC(NumericVector x1, NumericVector x2) {
    NumericVector pooled_sample(x1.size() + x2.size());
    for (int i = 0; i < x1.size(); ++i) {
        pooled_sample[i] = x1[i];
    }
    for (int i = 0; i < x2.size() ; ++i) {
        pooled_sample[x1.size() + i] = x2[i];
    }
    Rcpp::NumericVector ranks = avg_rank(pooled_sample);
    Rcpp::NumericVector x2_ranks = ranks[Rcpp::Range(x1.size(), ranks.size())];
    unsigned sum_of_x2_ranks = Rcpp::sum(x2_ranks);
    return Rcpp::pwilcox(sum_of_x2_ranks, x2.size(), x1.size());

}

double
unconditional_run_length_distribution(unsigned int n,
                                      NumericVector phaseI_sample,
                                      unsigned int nsim,
                                      double LCL,
                                      unsigned run_length_cap) {
    Ta ta (1000, 42);
    unsigned m = phaseI_sample.size();
    NumericVector run_lengths(nsim);
    for (int i = 0; i < ; ++i) {
        NumericVector phaseI_sample_boot = Rcpp::sample(phaseI_sample, m);
        unsigned run_length = 0;
        for (;;) {
            NumericVector test_sample = Rcpp::sample(phaseI_sample, n);
            double plotting_stat = testC(phaseI_sample_boot, test_sample);
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
