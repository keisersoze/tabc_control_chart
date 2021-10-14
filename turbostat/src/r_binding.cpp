//
// Created by Filippo Maganza on 05/11/2020.
//

#include <string>
#include <vector>
#include <iostream>

#include <Rcpp.h>
#include <xoshiro.h>

#include "global_rng.h"

#include "single_aspect.h"
#include "multiple_aspects.h"
#include "simple_stats.h"

#include "distribution.h"
#include <boost/random/normal_distribution.hpp>
#include <boost/random/cauchy_distribution.hpp>
#include <boost/random/laplace_distribution.hpp>
#include <boost/random/student_t_distribution.hpp>

#include "monitoring_statistic_wrappers.h"

#include "calibration.h"

#include "evaluation.h"

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

distribution build_distribution(const std::string &dist_s, Rcpp::List distribution_params){
    if (dist_s == "norm"){
        double mean = distribution_params["mean"];
        double sd = distribution_params["sd"];
        return boost::random::normal_distribution<double>(mean, sd);
    } else if (dist_s == "t") {
        unsigned df = distribution_params["df"];
        return boost::random::student_t_distribution<double>(df);
    }else if (dist_s == "normalized_t_with_two_pont_five_degrees"){
        return normalized_t_with_two_pont_five_degrees();
    } else if (dist_s == "normalized_rate_one_exponential"){
        return normalized_rate_one_exponential();
    } else {
        Rcpp::stop("Monitoring statistic not recognized");
    }
}

// Unidirectional charts unconditional calibration and evaluation

std::map<std::string, permutation_test> permutation_pvalue_monitoring_stat_map = {
        {"a",   t_a_permtest<dqrng::xoroshiro128plus>},
        {"b",   t_b_permtest<dqrng::xoroshiro128plus>},
        {"c",   t_c_permtest<dqrng::xoroshiro128plus>},
        {"abc", t_abc<dqrng::xoroshiro128plus>},
        {"ab", t_ab<dqrng::xoroshiro128plus>},
        {"ac", t_ac<dqrng::xoroshiro128plus>},
        {"bc", t_bc<dqrng::xoroshiro128plus>}
};

std::map<std::string, multiaspect_test_phase_1> multiaspect_obs_value_monitoring_stat_map = {
        {"abc-2", t_abc_phase_1<dqrng::xoroshiro128plus>},
        {"ab-2", t_ab_phase_1<dqrng::xoroshiro128plus>},
        {"ac-2", t_ac_phase_1<dqrng::xoroshiro128plus>},
        {"bc-2", t_bc_phase_1<dqrng::xoroshiro128plus>}
};

std::map<std::string, monitoring_statistic> simple_monitoring_stat_map = {
        {"wilcoxon", simple_monitoring_statistic(wilcoxon_rank_sum)},
        {"mann-whitney", simple_monitoring_statistic(mann_whitney)},
        {"sum-of-sings", simple_monitoring_statistic(sum_of_signs)},
        {"difference_of_sums", simple_monitoring_statistic(difference_of_sums)},
        {"difference_of_means", simple_monitoring_statistic(difference_of_means)},
        {"sum-of-x2", simple_monitoring_statistic(x2_sum)}
};


monitoring_statistic build_monitoring_statistic(const std::string &monitoring_stat_s, Rcpp::List monitoring_stat_params){
    if (permutation_pvalue_monitoring_stat_map.find(monitoring_stat_s) != permutation_pvalue_monitoring_stat_map.end()){
        permutation_test pt = permutation_pvalue_monitoring_stat_map[monitoring_stat_s];
        unsigned n_permutations = monitoring_stat_params["n_permutations"];
        permutation_pvalue_monitoring_statistic monitoring_stat(pt, n_permutations);
        return monitoring_stat;
    } else if (multiaspect_obs_value_monitoring_stat_map.find(monitoring_stat_s) != multiaspect_obs_value_monitoring_stat_map.end()){
        multiaspect_test_phase_1 mtp1 = multiaspect_obs_value_monitoring_stat_map[monitoring_stat_s];
        unsigned n_permutations = monitoring_stat_params["n_permutations"];
        multiaspect_obs_value_monitoring_statistic monitoring_stat(mtp1, n_permutations);
        return monitoring_stat;
    } else if (simple_monitoring_stat_map.find(monitoring_stat_s) != simple_monitoring_stat_map.end()){
        return simple_monitoring_stat_map[monitoring_stat_s];
    } else {
        Rcpp::stop("Monitoring statistic not recognized");
    }
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
                                            const std::string &distribution_key,
                                            Rcpp::List distribution_parameters,
                                            const std::string &monitoring_statistic_key,
                                            Rcpp::List monitoring_statistic_parameters,
                                            const std::vector<double> &limits_seq,
                                            bool upper_limit,
                                            unsigned nsim,
                                            unsigned run_length_cap) {
    distribution ic_distribution = build_distribution(distribution_key, distribution_parameters);
    monitoring_statistic ms = build_monitoring_statistic(monitoring_statistic_key, monitoring_statistic_parameters);
    std::vector<std::vector<int>> res_matrix = unconditional_unidirectional_calibration(m,
                                                                                        n,
                                                                                        ic_distribution,
                                                                                        ms,
                                                                                        limits_seq,
                                                                                        upper_limit,
                                                                                        nsim,
                                                                                        run_length_cap);
    Rcpp::NumericMatrix res_rcpp(nsim, limits_seq.size());

    for (unsigned i = 0; i < nsim; ++i) {
        for (unsigned j = 0; j < limits_seq.size(); ++j) {
            res_rcpp(i, j) = res_matrix[i][j];
        }
    }

    return res_rcpp;
}


//' Unconditional evaluation
//'
//' to do
//'
//' @param x1 An numeric vector
//' @param x2 An numeric vector
//' @param B the number of permutations to be used for estimating the pvalue
//' @export
// [[Rcpp::export(evaluate.unconditional)]]
Rcpp::DataFrame evaluate_unconditional(unsigned m,
                                       unsigned n,
                                       double limit,
                                       bool upper_limit,
                                       const std::vector<double> &shifts,
                                       const std::string &distribution_key,
                                       Rcpp::List distribution_parameters,
                                       const std::string &monitoring_statistic_key,
                                       Rcpp::List monitoring_statistic_parameters,
                                       unsigned nsim,
                                       unsigned run_length_cap) {
    distribution ic_distribution = build_distribution(distribution_key, distribution_parameters);
    monitoring_statistic ms = build_monitoring_statistic(monitoring_statistic_key, monitoring_statistic_parameters);
    std::vector<std::vector<unsigned>> run_lengths_matrix = unconditional_unidirectional_evaluation(m,
                                                                                                    n,
                                                                                                    limit,
                                                                                                    upper_limit,
                                                                                                    shifts,
                                                                                                    ic_distribution,
                                                                                                    ms,
                                                                                                    nsim,
                                                                                                    run_length_cap);
    Rcpp::NumericVector arls(shifts.size());
    Rcpp::NumericVector sds(shifts.size());
    for (unsigned shift_index = 0; shift_index < shifts.size() ; ++shift_index) {
        std::vector<unsigned> &run_lengths = run_lengths_matrix[shift_index];
        Rcpp::NumericVector run_lengths_r = Rcpp::wrap(run_lengths);
        arls[shift_index] = Rcpp::mean(run_lengths_r);
        sds[shift_index] = Rcpp::sd(run_lengths_r);
    }
    Rcpp::DataFrame result = Rcpp::DataFrame::create(Rcpp::Named("ARLs") = arls,
                                                     Rcpp::Named("SD") = sds);
    return result;

}


// [[Rcpp::export(test.exp)]]
std::vector<double> test_exp(unsigned n) {
    normalized_rate_one_exponential d;
    std::vector<double> v(n);
    std::generate(v.begin(), v.end(),
                  [&d]() { return d(global_rng::instance);});
    return v;
}

// [[Rcpp::export(test.t_due_e_mezzo)]]
std::vector<double> test_t_due_e_mezzo(unsigned n) {
    normalized_t_with_two_pont_five_degrees d;
    std::vector<double> v(n);
    std::generate(v.begin(), v.end(),
                  [&d]() { return d(global_rng::instance);});
    return v;
}

// [[Rcpp::export(test1)]]
std::vector<double>  test1(unsigned n) {
    std::vector<double> v(n);
    for (unsigned i = 0; i < n; ++i) {
        boost::random::normal_distribution<double> dist(0.0, 1.0);
        std::vector<double> reference_sample(100);
        std::vector<double> test_sample(10);
        std::generate(reference_sample.begin(), reference_sample.end(),
                      [&dist]() { return dist(global_rng::instance);});
        std::generate(test_sample.begin(), test_sample.end(),
                      [&dist]() { return dist(global_rng::instance);});
        v[i]= difference_of_sums(reference_sample,test_sample);
    }
    return v;
}


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
//        Rcpp::function("turbotabc", &T_abc_permtest)