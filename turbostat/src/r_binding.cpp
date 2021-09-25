//
// Created by Filippo Maganza on 05/11/2020.
//

#include <string>
#include <vector>
#include <iostream>

#include <Rcpp.h>
#include <xoshiro.h>

#include "single_aspect.h"
#include "multiple_aspects.h"
#include "global_rng.h"
#include "calibration.h"

#include "distributions.h"
#include "distribution_dispatching.h"

std::string hello() {
    return "Hello world";
}

//' Ta permutation test
//'
//' Compute approximated pvalue for the Ta test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
//' @export
// [[Rcpp::export(turbostat.setseed)]]
void setseed(unsigned s) {
    global_rng::instance.seed(s);
}

//' Ta permutation test
//'
//' Compute approximated pvalue for the Ta test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
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
//' Compute approximated pvalue for the Tb test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
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
//' Compute approximated pvalue for the Tc test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
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


//' Tabc permutation test
//'
//' Compute approximated pvalue for the Tabc test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
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

//' Tab permutation test
//'
//' Compute approximated pvalue for the Tabc test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
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

//' Tbc permutation test
//'
//' Compute approximated pvalue for the Tabc test using a finite number of permutations.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
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

//' Tac permutation test
//'
//' Compute pvalue estimate for the Tac test.
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
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

//' Unconditional calibration
//'
//' to do
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
//' @export
// [[Rcpp::export(calibrate.unconditional)]]
Rcpp::NumericMatrix calibrate_unconditional(unsigned m,
                                           unsigned n,
                                           const std::string &dist,
                                           unsigned nsim,
                                           unsigned nperm,
                                           const std::vector<double> &lcl_seq,
                                           const std::string &chart,
                                           unsigned run_length_cap) {
    std::vector<std::vector<int>> res_matrix = unconditional_unidirectional_calibration(m,
                                                                                        n,
                                                                                        dispatch_generator_from_string(dist),
                                                                                        nsim,
                                                                                        nperm,
                                                                                        lcl_seq,
                                                                                        chart,
                                                                                        run_length_cap);

    Rcpp::NumericMatrix res_rcpp(nsim, lcl_seq.size());

    for (unsigned i = 0; i < nsim; ++i) {
        for (unsigned j = 0; j < lcl_seq.size(); ++j) {
            res_rcpp(i, j) = res_matrix[i][j];
        }
    }

    return res_rcpp;

}


// [[Rcpp::export(test.normal)]]
std::vector<double> test_normal(unsigned n,
                                double mean,
                                double sd) {
    std::vector<double> v(n);
    rnorm(mean, sd, v, global_rng::instance);
    return v;
}

// [[Rcpp::export(test.exp)]]
std::vector<double> test_exp(unsigned n) {
    normalized_exponential_generator<dqrng::xoroshiro128plus> gen;
    std::vector<double> v(n);
    gen(global_rng::instance, v);
    return v;
}




//NumericVector testA(NumericVector x1, NumericVector x2, int B) {
//    std::vector<double> x1_c(x1.size());
//    for (int j = 0; j < x1.size(); ++j) {
//        x1_c[j] = x1[j];
//    }
//    std::vector<double> x2_c(x2.size());
//    for (int j = 0; j < x2.size(); ++j) {
//        x2_c[j] = x2[j];
//    }
//    std::pair<double, double> pair = test_A(x1_c, x2_c, B);
//    return NumericVector::create(pair.second ,pair.first);
//}
//
//NumericVector testC(NumericVector x1, NumericVector x2, int B) {
//    std::vector<double> x1_c(x1.size());
//    for (int j = 0; j < x1.size(); ++j) {
//        x1_c[j] = x1[j];
//    }
//    std::vector<double> x2_c(x2.size());
//    for (int j = 0; j < x2.size(); ++j) {
//        x2_c[j] = x2[j];
//    }
//    std::pair<double, double> pair = test_C(x1_c, x2_c, B);
//    return NumericVector::create(pair.second ,pair.first);
//}

//double sumcpp(const std::vector<double>& x) {
//    return accumulate(x.begin() , x.end(), 0.0);
//}

//NumericVector rnormcpp(int i) {
//    return Rcpp::rnorm(i);
//}

//RCPP_MODULE(test_module) {
//        class_<TestClass>( "TestClass" )
//                .constructor<int>()
//                .method( "returnA", &TestClass::returnA )
//        ;
//        class_<TaRBinding>( "TaRBinding" )
//                .constructor<unsigned ,unsigned >()
//                .method( "stat", &TaRBinding::stat )
//        ;
//        Rcpp::function("hello" , &hello);
//        Rcpp::function("testC", &testC);
//        Rcpp::function("sumcpp", &sumcpp);
//        Rcpp::function("rnormcpp", &rnormcpp);
//        Rcpp::function("uncoditional_run_length", &unconditional_run_length_distribution);
//        Rcpp::function("testCrcpp", &testCExact);
//        Rcpp::function("turbotabc", &T_abc_permtest);
//}

//RCPP_MODULE(test_module) {
//        Rcpp::function("hello" , &hello);
//        // Rcpp::function("testC", &testC);
//        Rcpp::function("uncoditional_run_length", &unconditional_run_length_distribution);
//        Rcpp::function("exact.tc", &testCExact);
//
//        Rcpp::function("permtest.ta", &t_a_permtest);
//        Rcpp::function("permtest.tb", &t_b_permtest);
//        Rcpp::function("permtest.tc", &t_c_permtest);
//        Rcpp::function("permtest.tabc", &t_abc_permtest);
//}


