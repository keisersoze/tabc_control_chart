//
// Created by filip on 22/08/2021.
//

#ifndef RACE_MULTIPLE_ASPECTS_H
#define RACE_MULTIPLE_ASPECTS_H

#include <numeric>
#include <algorithm>

# include "test_interface.h"
# include "data_aspects.h"
# include "utils.h"

template <class RNG>
perm_test_result t_abc (const std::vector<double> &x1,
                        const std::vector<double> &x2,
                        unsigned n_perm,
                        RNG &rng){
    unsigned n1 = x1.size();
    unsigned n2 = x2.size();
    std::vector<double> pooled_sample(x1.size() + x2.size());
    for (unsigned i = 0; i < n1; ++i) {
        pooled_sample[i] = x1[i];
    }
    for (unsigned i = 0; i < n2 ; ++i) {
        pooled_sample[n1 + i] = x2[i];
    }

    std::vector<double> categorical_aspect = b_aspect(pooled_sample);
    std::vector<double> rank_aspect = c_aspect(pooled_sample);

    double ta_obs = std::accumulate(pooled_sample.begin() , pooled_sample.begin() + n1 , 0.0)-
                    std::accumulate(pooled_sample.begin() + n1 , pooled_sample.end() , 0.0);
    double tb_obs = std::accumulate(categorical_aspect.begin() , categorical_aspect.begin() + n1 , 0.0)-
                    std::accumulate(categorical_aspect.begin() + n1 , categorical_aspect.end() , 0.0);
    double tc_obs = std::accumulate(rank_aspect.begin() , rank_aspect.begin() + n1 , 0.0) -
                    std::accumulate(rank_aspect.begin() + n1 , rank_aspect.end() , 0.0);

//    Rcpp::Rcout << "Ta_obs " << ta_obs << std::endl;
//    Rcpp::Rcout << "Tb_obs " << tb_obs << std::endl;
//    Rcpp::Rcout << "Tc_obs " << tc_obs << std::endl;

    std::vector<double> ta_perm (n_perm);
    std::vector<double> tb_perm (n_perm);
    std::vector<double> tc_perm (n_perm);

    // Rcpp::Rcout.precision(10);

    std::vector<unsigned> p(pooled_sample.size());
    std::iota(p.begin(), p.end(), 0);
    for (unsigned i = 0; i < n_perm ; ++i) {
        std::shuffle(p.begin(), p.end(), rng);

//        ta_perm[i] = T_a(permuted_pooled_sample, n1);
//        tb_perm[i] = T_b(permuted_pooled_sample, n1, median);
//        tc_perm[i] = T_c(permuted_pooled_sample, n1);

        double  sum_of_x1_numerical = 0;
        double  sum_of_x2_numerical = 0;
        for (unsigned j = 0; j < n1; ++j) {
            sum_of_x1_numerical = sum_of_x1_numerical + pooled_sample[p[j]];
        }
        for (unsigned j = n1; j < pooled_sample.size(); ++j) {
            sum_of_x2_numerical = sum_of_x2_numerical + pooled_sample[p[j]];
        }
        ta_perm[i] = sum_of_x1_numerical - sum_of_x2_numerical;

        double  sum_of_x1_categorical = 0;
        double  sum_of_x2_categorical = 0;
        for (unsigned j = 0; j < n1; ++j) {
            sum_of_x1_categorical = sum_of_x1_categorical + categorical_aspect[p[j]];
        }
        for (unsigned j = n1; j < pooled_sample.size(); ++j) {
            sum_of_x2_categorical = sum_of_x2_categorical + categorical_aspect[p[j]];
        }
        tb_perm[i] = sum_of_x1_categorical - sum_of_x2_categorical;

        double sum_of_x1_ranks = 0;
        double sum_of_x2_ranks = 0;
        for (unsigned j = 0; j < n1; ++j) {
            sum_of_x1_ranks = sum_of_x1_ranks + rank_aspect[p[j]];
        }
        for (unsigned j = n1; j < pooled_sample.size(); ++j) {
            sum_of_x2_ranks = sum_of_x2_ranks + rank_aspect[p[j]];
        }
        tc_perm[i] = sum_of_x1_ranks - sum_of_x2_ranks;
    }
//    Rcpp::Rcout << "Ta " << ta_perm << std::endl;
//    Rcpp::Rcout << "Tb " << tb_perm << std::endl;
//    Rcpp::Rcout << "Tc " << tc_perm << std::endl;

    unsigned pa = std::count_if(ta_perm.begin(), ta_perm.end(), [ta_obs](double x){return x <= ta_obs;});
    unsigned pb = std::count_if(tb_perm.begin(), tb_perm.end(), [tb_obs](double x){return x <= tb_obs;});
    unsigned pc = std::count_if(tc_perm.begin(), tc_perm.end(), [tc_obs](double x){return x <= tc_obs;});
    unsigned tabc_obs = std::min({pa, pb, pc});

//    Rcpp::Rcout << "pa " << pa << std::endl;
//    Rcpp::Rcout << "pb " << pb << std::endl;
//    Rcpp::Rcout << "pc " << pc << std::endl;
//    Rcpp::Rcout << "Tabc " << tabc_obs << std::endl;

    std::vector<unsigned> ta_perm_order = sort_permutation(ta_perm);
    std::vector<unsigned> tb_perm_order = sort_permutation(tb_perm);
    std::vector<unsigned> tc_perm_order = sort_permutation(tc_perm);

    apply_permutation_in_place(ta_perm, ta_perm_order);
    apply_permutation_in_place(tb_perm, tb_perm_order);
    apply_permutation_in_place(tc_perm, tc_perm_order);

//    Rcpp::Rcout << "Ta " << ta_perm_sorted << std::endl;
//    Rcpp::Rcout << "Tb " << tb_perm_sorted << std::endl;
//    Rcpp::Rcout << "Tc " << tc_perm_sorted << std::endl;

    int ta_tides = 0;
    int tb_tides = 0;
    int tc_tides = 0;

    std::vector<int> tabc_perm(n_perm, -1);

    for (unsigned i = 0; i < n_perm ; ++i) {

        if (i != n_perm - 1 and ta_perm[i] == ta_perm[i + 1]){
            ta_tides ++;
        } else{
            while (ta_tides > - 1){
                unsigned j = ta_perm_order[ i - ta_tides];
                if (tabc_perm[j] == -1){
                    tabc_perm[j] = i ;
                }
                ta_tides --;
            }
            ta_tides =  0;
        }

        if (i != n_perm - 1 and tb_perm[i] == tb_perm[i + 1]){
            tb_tides ++;
        } else{
            while (tb_tides > - 1){
                unsigned j = tb_perm_order[ i - tb_tides];
                if (tabc_perm[j] == -1){
                    tabc_perm[j] = i;
                }
                tb_tides --;
            }
            tb_tides =  0;
        }

        if (i != n_perm - 1 and tc_perm[i] == tc_perm[i + 1]){
            tc_tides ++;
        } else{
            while (tc_tides > - 1){
                unsigned j = tc_perm_order[ i - tc_tides];
                if (tabc_perm[j] == -1){
                    tabc_perm[j] = i ;
                }
                tc_tides --;
            }
            tc_tides =  0;
        }

    }

    // Rcpp::Rcout << "Tabc perm " << tabc_perm << std::endl;

    unsigned position = std::count_if(tabc_perm.begin(), tabc_perm.end(), [tabc_obs](double x){return x <= tabc_obs;});

    perm_test_result res(tabc_obs, n_perm, position);

    return res;
}


#endif //RACE_MULTIPLE_ASPECTS_H
