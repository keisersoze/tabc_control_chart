//
// Created by filip on 20/08/2021.
//

#ifndef RACE_RUNLENGTH_H
#define RACE_RUNLENGTH_H

#include <Rcpp.h>

// https://stackoverflow.com/questions/39153082/rcpp-rank-function-that-does-average-ties

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

double T_a (Rcpp::NumericVector pooled_sample, unsigned n1){
    return std::accumulate(pooled_sample.begin() , pooled_sample.begin() + n1 , 0.0)-
           std::accumulate(pooled_sample.begin() + n1 , pooled_sample.end() , 0.0);
}


double T_b (Rcpp::NumericVector pooled_sample, unsigned n1, double median){
    Rcpp::IntegerVector categorical_aspect = Rcpp::ifelse( pooled_sample >= median, 1, 0);
    return std::accumulate(categorical_aspect.begin() , categorical_aspect.begin() + n1 , 0.0)-
           std::accumulate(categorical_aspect.begin() + n1 , categorical_aspect.end() , 0.0);;
}

double T_c (Rcpp::NumericVector pooled_sample, unsigned n1){
    Rcpp::NumericVector ranks = avg_rank(pooled_sample);
    double a = std::accumulate(ranks.begin() , ranks.begin() + n1 , 0.0);
    double b = std::accumulate(ranks.begin() + n1 , ranks.end() , 0.0);
//    Rcpp::Rcout << a << std::endl;
//    Rcpp::Rcout << b << std::endl;
    return a-b;
}


Rcpp::IntegerVector order(Rcpp::NumericVector v) {

    // initialize original index locations
    Rcpp::IntegerVector idx = Rcpp::seq(0, v.size()-1);

    // sort indexes based on comparing values in v
    // using std::stable_sort instead of std::sort
    // to avoid unnecessary index re-orderings
    // when v contains elements of equal values
    stable_sort(idx.begin(), idx.end(),
                [&v](int i1, int i2) {return v[i1] < v[i2];});

    return idx;
}

double turbotabc (Rcpp::NumericVector x1,
                        Rcpp::NumericVector x2,
                        unsigned B){
    unsigned n1 = x1.size();
    unsigned n2 = x2.size();
    Rcpp::NumericVector pooled_sample(x1.size() + x2.size());
    for (unsigned i = 0; i < n1; ++i) {
        pooled_sample[i] = x1[i];
    }
    for (unsigned i = 0; i < n2 ; ++i) {
        pooled_sample[n1 + i] = x2[i];
    }

    double median = Rcpp::median(pooled_sample);
    Rcpp::NumericVector ranks = avg_rank(pooled_sample);
    Rcpp::IntegerVector categorical_aspect = Rcpp::ifelse( pooled_sample > median, 1, 0);

    double ta_obs = std::accumulate(pooled_sample.begin() , pooled_sample.begin() + n1 , 0.0)-
            std::accumulate(pooled_sample.begin() + n1 , pooled_sample.end() , 0.0);
    double tb_obs = std::accumulate(categorical_aspect.begin() , categorical_aspect.begin() + n1 , 0.0)-
                    std::accumulate(categorical_aspect.begin() + n1 , categorical_aspect.end() , 0.0);
    double tc_obs = std::accumulate(ranks.begin() , ranks.begin() + n1 , 0.0)-
                    std::accumulate(ranks.begin() + n1 , ranks.end() , 0.0);

//    Rcpp::Rcout << ta_obs << std::endl;
//    Rcpp::Rcout << tb_obs << std::endl;
//    Rcpp::Rcout << tc_obs << std::endl;

    Rcpp::NumericVector ta_perm (B);
    Rcpp::NumericVector tb_perm (B);
    Rcpp::NumericVector tc_perm (B);

    // Rcpp::Rcout.precision(10);

    // Rcpp::IntegerVector p = Rcpp::seq(0, pooled_sample.size()-1);
    for (unsigned i = 0; i < B ; ++i) {
        Rcpp::NumericVector permuted_pooled_sample = Rcpp::sample(pooled_sample, pooled_sample.size());
        // Rcpp::Rcout << permuted_pooled_sample << std::endl;
        ta_perm[i] = T_a(permuted_pooled_sample, n1);
        tb_perm[i] = T_b(permuted_pooled_sample, n1, median);
        tc_perm[i] = T_c(permuted_pooled_sample, n1);
//        p = Rcpp::sample(p, pooled_sample.size());
//        double  sum_of_x1_numerical = 0;
//        double  sum_of_x2_numerical = 0;
//        for (unsigned j = 0; j < n1; ++j) {
//            sum_of_x1_numerical = sum_of_x1_numerical + pooled_sample[p[j]];
//        }
//        for (unsigned j = n1; j < pooled_sample.size(); ++j) {
//            sum_of_x2_numerical = sum_of_x2_numerical + pooled_sample[p[j]];
//        }
//        ta_perm[i] = sum_of_x1_numerical - sum_of_x2_numerical;
//        unsigned  sum_of_x1_categorical = 0;
//        unsigned  sum_of_x2_categorical = 0;
//        for (unsigned j = 0; j < n1; ++j) {
//            sum_of_x1_categorical = sum_of_x1_categorical + categorical_aspect[p[j]];
//        }
//        for (unsigned j = n1; j < pooled_sample.size(); ++j) {
//            sum_of_x2_categorical = sum_of_x2_categorical + categorical_aspect[p[j]];
//        }
//        tb_perm[i] = sum_of_x1_categorical - sum_of_x2_categorical;
//        double sum_of_x1_ranks = 0;
//        double sum_of_x2_ranks = 0;
//        for (unsigned j = 0; j < n1; ++j) {
//            sum_of_x1_ranks = sum_of_x1_ranks + ranks[p[j]];
//        }
//        for (unsigned j = n1; j < pooled_sample.size(); ++j) {
//            sum_of_x2_ranks = sum_of_x2_ranks + ranks[p[j]];
//        }
//        tc_perm[i] = sum_of_x1_ranks - sum_of_x2_ranks;
    }
    Rcpp::Rcout << Rcpp::sum(Rcpp::ifelse( ta_perm <= ta_obs, 1, 0)) << std::endl;
//    Rcpp::Rcout << tb_perm << std::endl;
//    Rcpp::Rcout << tc_perm << std::endl;

    double pa_obs = (double)Rcpp::sum(Rcpp::ifelse( ta_perm <= ta_obs, 1, 0))/(double)B;
    double pb_obs = (double)Rcpp::sum(Rcpp::ifelse( tb_perm <= tb_obs, 1, 0))/(double)B;
    double pc_obs = (double)Rcpp::sum(Rcpp::ifelse( tc_perm <= tc_obs, 1, 0))/(double)B;
    double tabc_obs = std::min({ta_obs, tb_obs, tc_obs});
    Rcpp::Rcout << pa_obs << std::endl;
    Rcpp::Rcout << pb_obs << std::endl;
    Rcpp::Rcout << pc_obs << std::endl;

//    Rcpp::IntegerVector ta_perm_order = order(ta_perm);
//    Rcpp::IntegerVector tb_perm_order = order(tb_perm);
//    Rcpp::IntegerVector tc_perm_order = order(tc_perm);
//
//    Rcpp::NumericVector ta_perm_sorted = ta_perm[ta_perm_order];
//    Rcpp::NumericVector tb_perm_sorted = tb_perm[tb_perm_order];
//    Rcpp::NumericVector tc_perm_sorted = tc_perm[tc_perm_order];
//
//    int ta_tides = 0;
//    int tb_tides = 0;
//    int tc_tides = 0;
//
//    Rcpp::NumericVector tabc_perm(B, -1);
//
//    for (unsigned i = 0; i < B ; ++i) {
//
//        if (i != B and ta_perm_sorted[i] ==  ta_perm_sorted[i + 1]){
//            ta_tides ++;
//        } else{
//            while (ta_tides > - 1){
//                unsigned j = ta_perm_order[ i - ta_tides];
//                if (tabc_perm[j] == -1){
//                    tabc_perm[j] = i / B;
//                }
//                ta_tides --;
//            }
//            ta_tides =  0;
//        }
//
//        if (i != B and tb_perm_sorted[i] ==  ta_perm_sorted[i + 1]){
//            tb_tides ++;
//        } else{
//            while (tb_tides > - 1){
//                unsigned j = tb_perm_order[ i - tb_tides];
//                if (tabc_perm[j] == -1){
//                    tabc_perm[j] = i / B;
//                }
//                tb_tides --;
//            }
//            tb_tides =  0;
//        }
//
//        if (i != B and tc_perm_sorted[i] ==  tc_perm_sorted[i + 1]){
//            tc_tides ++;
//        } else{
//            while (tc_tides >= - 1){
//                unsigned j = tc_perm_order[ i - tc_tides];
//                if (tabc_perm[j] == -1){
//                    tabc_perm[j] = i / B;
//                }
//                tc_tides --;
//            }
//            tc_tides =  0;
//        }
//    }
//
//    unsigned count = 0;
//    for (auto elem: tabc_perm){
//        if (elem <= tabc_obs ){
//            count ++;
//        }
//    }

    return 0 ;
}

double
unconditional_run_length_distribution(unsigned int n,
                                      Rcpp::NumericVector phaseI_sample,
                                      unsigned int nsim,
                                      double LCL,
                                      unsigned run_length_cap) {
    Ta ta (1000, 42);
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

#endif //RACE_RUNLENGTH_H
