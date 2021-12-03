//
// Created by filip on 03/12/2021.
//

#include "stat/tests/single_aspect.h"
#include "stat/tests/multiple_aspects.h"

#include "rng/global_rng.h"

#include <Rcpp.h>


//' Ta permutation test
//'
//' Estimate the right tail permutation pvalue for the Ta test using a finite number of permutations.
//'
//' @param x1 The first group's observations provided as a numeric vector.
//' @param x2 The second group's observations provided as a numeric vector.
//' @param B The number of permutations used for estimating the pvalue
//' @return The estimated permutation pvalue and the observed statistic
//' @export
// [[Rcpp::export(permtest.ta)]]
Rcpp::DataFrame t_a_binding(const std::vector<double> &x1,
                            const std::vector<double> &x2,
                            unsigned B) {
    perm_test_result res = t_a_permtest(x1, x2, B, global_rng::instance);
    return Rcpp::DataFrame::create(Rcpp::Named("pvalue") = res.p_value,
                                   Rcpp::Named("obsStat") = res.obs_stat,
                                   Rcpp::Named("nPerm") = res.n_perm,
                                   Rcpp::Named("pos") = res.pos);
}

//' Tb permutation test
//'
//' Estimate the right tail permutation pvalue for the Tb test using a finite number of permutations.
//'
//' @param x1 The first group's observations provided as a numeric vector.
//' @param x2 The second group's observations provided as a numeric vector.
//' @param B The number of permutations used for estimating the pvalue
//' @return The estimated permutation pvalue and the observed statistic
//' @export
// [[Rcpp::export(permtest.tb)]]
Rcpp::DataFrame t_b_binding(const std::vector<double> &x1,
                            const std::vector<double> &x2,
                            unsigned B) {
    perm_test_result res = t_b_permtest(x1, x2, B, global_rng::instance);
    return Rcpp::DataFrame::create(Rcpp::Named("pvalue") = res.p_value,
                                   Rcpp::Named("obsStat") = res.obs_stat,
                                   Rcpp::Named("nPerm") = res.n_perm,
                                   Rcpp::Named("pos") = res.pos);
}

//' Tc permutation test
//'
//' Estimate the right tail permutation pvalue for the Tc test using a finite number of permutations.
//'
//' @param x1 The first group's observations provided as a numeric vector.
//' @param x2 The second group's observations provided as a numeric vector.
//' @param B The number of permutations used for estimating the pvalue
//' @return The estimated permutation pvalue and the observed statistic
//' @export
// [[Rcpp::export(permtest.tc)]]
Rcpp::DataFrame t_c_binding(const std::vector<double> &x1,
                            const std::vector<double> &x2,
                            unsigned B) {
    perm_test_result res = t_c_permtest(x1, x2, B, global_rng::instance);
    return Rcpp::DataFrame::create(Rcpp::Named("pvalue") = res.p_value,
                                   Rcpp::Named("obsStat") = res.obs_stat,
                                   Rcpp::Named("nPerm") = res.n_perm,
                                   Rcpp::Named("pos") = res.pos);
}


//' Tabc combined permutation test
//'
//' Estimate the right tail permutation pvalue for the Tabc test using a finite number of permutations.
//'
//' @param x1 The first group's observations provided as a numeric vector.
//' @param x2 The second group's observations provided as a numeric vector.
//' @param B The number of permutations used for estimating the pvalue
//' @return The estimated permutation pvalue and the observed statistic
//' @export
// [[Rcpp::export(permtest.tabc)]]
Rcpp::DataFrame t_abc_binding(const std::vector<double> &x1,
                              const std::vector<double> &x2,
                              unsigned B) {
    perm_test_result res = t_abc(x1, x2, B, global_rng::instance);
    return Rcpp::DataFrame::create(Rcpp::Named("pvalue") = res.p_value,
                                   Rcpp::Named("obsStat") = res.obs_stat,
                                   Rcpp::Named("nPerm") = res.n_perm,
                                   Rcpp::Named("pos") = res.pos);
}

//' Tab combined permutation test
//'
//' Estimate the right tail permutation pvalue for the Tab test using a finite number of permutations.
//'
//' @param x1 The first group's observations provided as a numeric vector.
//' @param x2 The second group's observations provided as a numeric vector.
//' @param B The number of permutations used for estimating the pvalue
//' @return The estimated permutation pvalue and the observed statistic
//' @export
// [[Rcpp::export(permtest.tab)]]
Rcpp::DataFrame t_ab_binding(const std::vector<double> &x1,
                             const std::vector<double> &x2,
                             unsigned B) {
    perm_test_result res = t_ab(x1, x2, B, global_rng::instance);
    return Rcpp::DataFrame::create(Rcpp::Named("pvalue") = res.p_value,
                                   Rcpp::Named("obsStat") = res.obs_stat,
                                   Rcpp::Named("nPerm") = res.n_perm,
                                   Rcpp::Named("pos") = res.pos);
}

//' Tbc combined permutation test
//'
//' Estimate the right tail permutation pvalue for the Tbc test using a finite number of permutations.
//'
//' @param x1 The first group's observations provided as a numeric vector.
//' @param x2 The second group's observations provided as a numeric vector.
//' @param B The number of permutations used for estimating the pvalue
//' @return The estimated permutation pvalue and the observed statistic
//' @export
// [[Rcpp::export(permtest.tbc)]]
Rcpp::DataFrame t_bc_binding(const std::vector<double> &x1,
                             const std::vector<double> &x2,
                             unsigned B) {
    perm_test_result res = t_bc(x1, x2, B, global_rng::instance);
    return Rcpp::DataFrame::create(Rcpp::Named("pvalue") = res.p_value,
                                   Rcpp::Named("obsStat") = res.obs_stat,
                                   Rcpp::Named("nPerm") = res.n_perm,
                                   Rcpp::Named("pos") = res.pos);
}

//' Tac combined permutation test
//'
//' Estimate the right tail permutation pvalue for the Tac test using a finite number of permutations.
//'
//' @param x1 The first group's observations provided as a numeric vector.
//' @param x2 The second group's observations provided as a numeric vector.
//' @param B The number of permutations used for estimating the pvalue
//' @return The estimated permutation pvalue and the observed statistic
//' @export
// [[Rcpp::export(permtest.tac)]]
Rcpp::DataFrame t_ac_binding(const std::vector<double> &x1,
                             const std::vector<double> &x2,
                             unsigned B) {
    perm_test_result res = t_ac(x1, x2, B, global_rng::instance);
    return Rcpp::DataFrame::create(Rcpp::Named("pvalue") = res.p_value,
                                   Rcpp::Named("obsStat") = res.obs_stat,
                                   Rcpp::Named("nPerm") = res.n_perm,
                                   Rcpp::Named("pos") = res.pos);
}