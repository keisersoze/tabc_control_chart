//
// Created by Filippo Maganza on 05/11/2020.
//

#include <string>
#include <vector>
#include <iostream>

#include <Rcpp.h>
#include <xoshiro.h>
#include <convert_seed.h>

#include "global_rng.h"

#include "single_aspect.h"
#include "multiple_aspects.h"
#include "simple_stats.h"
#include "fast_permtest.h"

#include "distribution.h"
#include <boost/random/normal_distribution.hpp>
#include <boost/random/cauchy_distribution.hpp>
#include <boost/random/laplace_distribution.hpp>
#include <boost/random/student_t_distribution.hpp>
#include <boost/random/chi_squared_distribution.hpp>

#include "monitoring_statistic_wrappers.h"

#include "calibration.h"

#include "evaluation.h"

//' Set the seed used by this R packet
//'
//' @param s The seed. Either an integer scalar or an integer vector of length 2 representing a 64-bit seed.
//' @export
// [[Rcpp::export(turbostat.setseed)]]
void set_seed(Rcpp::IntegerVector seed) {
    uint64_t _s = dqrng::convert_seed<uint64_t>(seed);
    global_rng::instance.seed(_s);
}

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

distribution build_distribution(const std::string &dist_s, Rcpp::List distribution_params){
    if (dist_s == "norm"){
        double mean = distribution_params["mean"];
        double sd = distribution_params["sd"];
        return boost::random::normal_distribution<double>(mean, sd);
    } else if (dist_s == "t") {
        unsigned df = distribution_params["df"];
        return boost::random::student_t_distribution<double>(df);
    } else if (dist_s == "laplace") {
        double location = distribution_params["location"];
        double scale = distribution_params["scale"];
        return boost::random::laplace_distribution<double>(location, scale);
    } else if (dist_s == "cauchy") {
        double location = distribution_params["location"];
        double scale = distribution_params["scale"];
        return boost::random::cauchy_distribution<double>(location, scale);
    } else if  (dist_s == "chi_squared"){
        double df = distribution_params["df"];
        return boost::random::chi_squared_distribution<double>(df);
    } else if (dist_s == "normalized_t_with_two_pont_five_degrees"){
        return normalized_t_with_two_pont_five_degrees();
    } else if (dist_s == "normalized_rate_one_exponential"){
        return normalized_rate_one_exponential();
    }else if (dist_s == "standard_half_cauchy"){
        return standard_half_cauchy();
    } else {
        Rcpp::stop("Monitoring statistic not recognized");
    }
}

// Unidirectional charts unconditional calibration and evaluation

std::map<std::string, permutation_test> permutation_pvalue_monitoring_stat_map = {
        {"ta_pvalue",   t_a_permtest<dqrng::xoshiro256plus>},
        {"tb_pvalue",   t_b_permtest<dqrng::xoshiro256plus>},
        {"tc_pvalue",   t_c_permtest<dqrng::xoshiro256plus>},
        {"tabc_pvalue", t_abc<dqrng::xoshiro256plus>},
        {"tab_pvalue", t_ab<dqrng::xoshiro256plus>},
        {"tac_pvalue", t_ac<dqrng::xoshiro256plus>},
        {"tbc_pvalue", t_bc<dqrng::xoshiro256plus>}
};

std::map<std::string, multiaspect_test_phase_1> multiaspect_obs_value_monitoring_stat_map = {
        {"tabc_obs_stat", t_abc_phase_1<dqrng::xoshiro256plus>},
        {"tab_obs_stat", t_ab_phase_1<dqrng::xoshiro256plus>},
        {"tac_obs_stat", t_ac_phase_1<dqrng::xoshiro256plus>},
        {"tbc_obs_stat", t_bc_phase_1<dqrng::xoshiro256plus>}
};

std::map<std::string, monitoring_statistic> simple_monitoring_stat_map = {
        {"wilcoxon", simple_monitoring_statistic(wilcoxon_rank_sum)},
        {"mann-whitney", simple_monitoring_statistic(mann_whitney)},
        {"sum-of-sings", simple_monitoring_statistic(sum_of_signs)},
        {"difference_of_sums", simple_monitoring_statistic(difference_of_sums)},
        {"difference_of_means", simple_monitoring_statistic(difference_of_means)},
        {"x2_sum", simple_monitoring_statistic(x2_sum)},
        {"x2_mean", simple_monitoring_statistic(x2_mean)},
        {"precedence", simple_monitoring_statistic(precedence)},
        {"sum_of_sings_v2", simple_monitoring_statistic(sum_of_signs_v2)},
        {"conover_statistic", simple_monitoring_statistic(conover_statistic)},
        {"mood_statistic", simple_monitoring_statistic(mood_statistic)},
        {"ab_statistic", simple_monitoring_statistic(ab_statistic)},
        {"klotz_statistic", simple_monitoring_statistic(klotz_statistic)},
        {"fab_statistic", simple_monitoring_statistic(fab_statistic)}
};


monitoring_statistic build_monitoring_statistic(const std::string &monitoring_stat_s,
                                                Rcpp::List monitoring_stat_params,
                                                unsigned m,
                                                unsigned n){
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
    } else if (monitoring_stat_s == "mann_whitney_fast_pvalue"){
        unsigned n_perm = monitoring_stat_params["n_permutations"];
        return fast_permtest(m, n, n_perm, mann_whitney, global_rng::instance);
    } else {
        Rcpp::stop("Monitoring statistic not recognized");
    }
}

//' Unconditional calibration
//'
//' Unconditional calibration for the Stehwart-type charts implemented by this package
//'
//' @param m The dimension used for the reference sample.
//' @param n The dimension used for the test samples.
//' @param distribution_key A string which identifies a distribution or a distribution family. Used in combination with the "distribution_parameters" parameter in order to select the IC distribution.
//' @param distribution_parameters A list with the distribution parameters (an empty list should be supplied if the distribution has not parameters).
//' @param monitoring_statistic_key A string used to select the monitoring statistic of the chart to be calibrated.
//' @param monitoring_statistic_parameters A list with the parameters to be supplied for the selected monitoring statistic.
//' @param limits_seq The numeric vector of limits for which the run length should be recorded at each simulation.
//' @param is_upper_limit A boolean parameter used to select the direction of the OOC alternative.
//' @param nsim The number of simulations
//' @param run_length_cap A limit for the run length in the simulations used to guarantee convergence of the algorithm.
//' @return A numeric matrix of size nsim x length(limits_seq).
//' @export
// [[Rcpp::export(calibrate.unconditional)]]
Rcpp::NumericMatrix calibrate_unconditional(unsigned m,
                                            unsigned n,
                                            const std::string &distribution_key,
                                            Rcpp::List distribution_parameters,
                                            const std::string &monitoring_statistic_key,
                                            Rcpp::List monitoring_statistic_parameters,
                                            const std::vector<double> &limits_seq,
                                            bool is_upper_limit,
                                            unsigned nsim,
                                            unsigned run_length_cap) {
    distribution ic_distribution = build_distribution(distribution_key, distribution_parameters);
    monitoring_statistic ms = build_monitoring_statistic(monitoring_statistic_key, monitoring_statistic_parameters, m, n);
    std::vector<std::vector<int>> res_matrix = unconditional_unidirectional_calibration(m,
                                                                                        n,
                                                                                        ic_distribution,
                                                                                        ms,
                                                                                        limits_seq,
                                                                                        is_upper_limit,
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
//' Unconditional evaluation for the Stehwart-type charts implemented by this package
//'
//' @param m The dimension used for the reference sample.
//' @param n The dimension used for the test samples.
//' @param distribution_key A string which identifies a distribution or a distribution family. Used in combination with the "distribution_parameters" parameter in order to select the IC distribution.
//' @param distribution_parameters A list with the distribution parameters (an empty list should be supplied if the distribution has not parameters).
//' @param monitoring_statistic_key A string used to select the monitoring statistic of the chart to be calibrated.
//' @param monitoring_statistic_parameters A list with the parameters to be supplied for the selected monitoring statistic.
//' @param nsim The number of simulations
//' @param run_length_cap A limit for the run length in the simulations used to guarantee convergence of the algorithm.
//' @export
// [[Rcpp::export(evaluate.unconditional)]]
Rcpp::DataFrame evaluate_unconditional(unsigned m,
                                       unsigned n,
                                       double limit,
                                       bool is_upper_limit,
                                       const std::vector<double> &shifts,
                                       const std::string &distribution_key,
                                       Rcpp::List distribution_parameters,
                                       const std::string &monitoring_statistic_key,
                                       Rcpp::List monitoring_statistic_parameters,
                                       unsigned nsim,
                                       unsigned run_length_cap) {
    distribution ic_distribution = build_distribution(distribution_key, distribution_parameters);
    monitoring_statistic ms = build_monitoring_statistic(monitoring_statistic_key, monitoring_statistic_parameters, m, n);
    std::vector<std::vector<unsigned>> run_lengths_matrix = unconditional_unidirectional_evaluation(m,
                                                                                                    n,
                                                                                                    limit,
                                                                                                    is_upper_limit,
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

// [[Rcpp::export(evaluate.unconditional.scale)]]
Rcpp::DataFrame evaluate_unconditional_scale(unsigned m,
                                       unsigned n,
                                       double limit,
                                       bool is_upper_limit,
                                       const std::vector<double> &scale_multipliers,
                                       const std::string &distribution_key,
                                       Rcpp::List distribution_parameters,
                                       const std::string &monitoring_statistic_key,
                                       Rcpp::List monitoring_statistic_parameters,
                                       unsigned nsim,
                                       unsigned run_length_cap) {
    distribution ic_distribution = build_distribution(distribution_key, distribution_parameters);
    monitoring_statistic ms = build_monitoring_statistic(monitoring_statistic_key, monitoring_statistic_parameters, m, n);
    std::vector<std::vector<unsigned>> run_lengths_matrix = unconditional_unidirectional_evaluation_scale(m,
                                                                                                          n,
                                                                                                          limit,
                                                                                                          is_upper_limit,
                                                                                                          scale_multipliers,
                                                                                                          ic_distribution,
                                                                                                          ms,
                                                                                                          nsim,
                                                                                                          run_length_cap);
    Rcpp::NumericVector arls(scale_multipliers.size());
    Rcpp::NumericVector sds(scale_multipliers.size());
    for (unsigned shift_index = 0; shift_index < scale_multipliers.size() ; ++shift_index) {
        std::vector<unsigned> &run_lengths = run_lengths_matrix[shift_index];
        Rcpp::NumericVector run_lengths_r = Rcpp::wrap(run_lengths);
        arls[shift_index] = Rcpp::mean(run_lengths_r);
        sds[shift_index] = Rcpp::sd(run_lengths_r);
    }
    Rcpp::DataFrame result = Rcpp::DataFrame::create(Rcpp::Named("ARLs") = arls,
                                                     Rcpp::Named("SD") = sds);
    return result;

}

// [[Rcpp::export(calibrate.conditional)]]
double calibrate_conditional(const std::vector<double> &reference_sample,
                                          unsigned n,
                                          const std::string &monitoring_statistic_key,
                                          Rcpp::List monitoring_statistic_parameters,
                                          unsigned target_ARL,
                                          bool is_upper_limit,
                                          unsigned nsim) {
    monitoring_statistic ms = build_monitoring_statistic(monitoring_statistic_key, monitoring_statistic_parameters,reference_sample.size(),n);
    double limit = conditional_unidirectional_calibration(reference_sample,
                                                          n,
                                                          ms,
                                                          is_upper_limit,
                                                          target_ARL,
                                                          nsim);
    return limit;
}


// [[Rcpp::export(evaluate.conditional)]]
Rcpp::DataFrame evaluate_conditional(const std::vector<double> &reference_sample,
                                     unsigned n,
                                     double limit,
                                     bool is_upper_limit,
                                     const std::vector<double> &shifts,
                                     const std::string &monitoring_statistic_key,
                                     Rcpp::List monitoring_statistic_parameters,
                                     unsigned nsim,
                                     unsigned run_length_cap) {
    monitoring_statistic ms = build_monitoring_statistic(monitoring_statistic_key, monitoring_statistic_parameters,reference_sample.size(),n);
    std::vector<std::vector<unsigned>> run_lengths_matrix = conditional_unidirectional_evaluation(reference_sample,
                                                                                                  n,
                                                                                                  limit,
                                                                                                  is_upper_limit,
                                                                                                  shifts,
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

// [[Rcpp::export(test.laplace)]]
std::vector<double> test_laplace(unsigned n, double location, double scale) {
    boost::random::laplace_distribution<double> d (location, scale);
    std::vector<double> v(n);
    std::generate(v.begin(), v.end(),
                  [&d]() { return d(global_rng::instance);});
    return v;
}

// [[Rcpp::export(test.cauchy)]]
std::vector<double> test_cauchy(unsigned n, double location, double scale) {
    boost::random::cauchy_distribution<double> d (location, scale);
    std::vector<double> v(n);
    std::generate(v.begin(), v.end(),
                  [&d]() { return d(global_rng::instance);});
    return v;
}

// [[Rcpp::export(test.standard_half_cauchy)]]
std::vector<double> test_standard_half_cauchy(unsigned n) {
    standard_half_cauchy d;
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

// [[Rcpp::export(test.fasttest)]]
double  test_fastest(const std::vector<double> &x1,
                     const std::vector<double> &x2,
                     unsigned B) {
    fast_permtest mw_pvalue(x1.size(), x2.size(), B, mann_whitney, global_rng::instance);
    return mw_pvalue(x1, x2, global_rng::instance);
}

// [[Rcpp::export(test.ansari_bradley)]]
double  test_ansari_bradley(const std::vector<double> &x1,
                            const std::vector<double> &x2) {
    return ab_statistic(x1, x2);
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
//        Rcpp::function("turbotabc", &T_abc_permt