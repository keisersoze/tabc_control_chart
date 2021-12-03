//
// Created by Filippo Maganza on 05/11/2020.
//

#include <string>
#include <vector>
#include <iostream>

#include <Rcpp.h>
#include <xoshiro.h>

#include "rng/global_rng.h"

#include "stat/tests/single_aspect.h"
#include "stat/tests/multiple_aspects.h"
#include "stat/simple_stats.h"
#include "stat/distribution.h"

#include <boost/random/normal_distribution.hpp>
#include <boost/random/cauchy_distribution.hpp>
#include <boost/random/laplace_distribution.hpp>
#include <boost/random/student_t_distribution.hpp>
#include <boost/random/chi_squared_distribution.hpp>

#include "charts/monitoring_statistic_wrappers.h"
#include "charts/calibration/calibration.h"
#include "charts/evaluation/evaluation.h"
#include "charts/npc/npc_df_chart.h"


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

std::map<std::string, simple_statistic> stat_map = {
        {"wilcoxon_rank_sum", wilcoxon_rank_sum},
        {"mann_whitney", mann_whitney},
        {"sum_of_sings", sum_of_signs},
        {"conover_statistic", conover_statistic},
        {"mood_statistic", mood_statistic},
        {"ab_statistic", ab_statistic},
        {"klotz_statistic", klotz_statistic},
        {"difference_of_rank_means", difference_of_rank_means},
        {"difference_of_means_klotz", difference_of_means_klotz},
        {"difference_of_means_ab", difference_of_means_ab_statistic},
        {"lepage", lepage},
        {"cucconi", cucconi}
};

std::map<std::string, combining_function> combining_function_map = {
        {"tippet", tippet},
        {"fisher", fisher},
        {"liptak", liptak}
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
    } else if (monitoring_stat_s == "simple_statistic"){
        std::string statistic_key = monitoring_stat_params["statistic"];
        simple_statistic s = stat_map[statistic_key];
        return simple_monitoring_statistic(s);
    } else if (monitoring_stat_s == "fast_pvalue"){
        std::vector<double> permutation_distribution = monitoring_stat_params["permutation_distribution"];
        std::string simple_monitoring_statistic_key = monitoring_stat_params["statistic"];
        std::string tail_key = monitoring_stat_params["tail"];
        simple_statistic s = stat_map[simple_monitoring_statistic_key];
        return fast_permtest(s, permutation_distribution, tail_key);
    } else if (monitoring_stat_s == "npc") {
        Rcpp::List permutation_distributions_r = monitoring_stat_params["permutation_distributions"];
        std::vector<std::vector<double>> permutation_distributions;
        for (int i = 0; i < permutation_distributions_r.size() ; ++i) {
            std::vector<double> permutation_distribution = permutation_distributions_r[i];
            permutation_distributions.push_back(permutation_distribution);
        }
        Rcpp::List statistics_keys_r = monitoring_stat_params["statistics"];
        std::vector<std::string> statistics_keys;
        for (int i = 0; i < permutation_distributions_r.size() ; ++i) {
            std::string statistics_key = statistics_keys_r[i];
            statistics_keys.push_back(statistics_key);
        }
        Rcpp::List tail_keys_r = monitoring_stat_params["tails"];
        std::vector<std::string> tail_keys;
        for (int i = 0; i < permutation_distributions_r.size() ; ++i) {
            std::string tail_key = tail_keys_r[i];
            tail_keys.push_back(tail_key);
        }
        std::vector<fast_permtest> perm_tests;
        for (int i = 0; i < tail_keys.size(); ++i) {
            std::vector<double> permutation_distribution = permutation_distributions[i];
            std::string statistic_key = statistics_keys[i];
            simple_statistic s = stat_map[statistic_key];
            std::string tail_key = tail_keys[i];
            fast_permtest perm_test(s, permutation_distribution, tail_key);
            perm_tests.push_back(perm_test);
        }
        std::string combining_function_key = monitoring_stat_params["combining_function"];
        combining_function c = combining_function_map[combining_function_key];
        return npc_df_chart(perm_tests, c);
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

// [[Rcpp::export(evaluate.unconditional.location_scale)]]
Rcpp::DataFrame evaluate_unconditional_location_scale(unsigned m,
                                                      unsigned n,
                                                      double limit,
                                                      bool is_upper_limit,
                                                      Rcpp::List location_scale_changes,
                                                      const std::string &distribution_key,
                                                      Rcpp::List distribution_parameters,
                                                      const std::string &monitoring_statistic_key,
                                                      Rcpp::List monitoring_statistic_parameters,
                                                      unsigned nsim,
                                                      unsigned run_length_cap) {
    std::vector<std::pair<double, double>> location_scale_changes_c;
    for (int i = 0; i < location_scale_changes.size() ; ++i) {
        std::vector<double> location_scale_change = location_scale_changes[i];
        location_scale_changes_c.emplace_back(location_scale_change[0],location_scale_change[1]);
    }
    distribution ic_distribution = build_distribution(distribution_key, distribution_parameters);
    monitoring_statistic ms = build_monitoring_statistic(monitoring_statistic_key, monitoring_statistic_parameters, m, n);
    std::vector<std::vector<unsigned>> run_lengths_matrix = unconditional_unidirectional_evaluation_location_scale(m,
                                                                                                                   n,
                                                                                                                   limit,
                                                                                                                   is_upper_limit,
                                                                                                                   location_scale_changes_c,
                                                                                                                   ic_distribution,
                                                                                                                   ms,
                                                                                                                   nsim,
                                                                                                                   run_length_cap);
    Rcpp::NumericVector arls(location_scale_changes.size());
    Rcpp::NumericVector sds(location_scale_changes.size());
    for (unsigned shift_index = 0; shift_index < location_scale_changes.size() ; ++shift_index) {
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

// [[Rcpp::export(compute_permutation_distribution)]]
std::vector<double>  compute_permutation_distribution_r(std::string statistic,
                                                        unsigned m,
                                                        unsigned n,
                                                        unsigned n_perm) {
    simple_statistic s = stat_map[statistic];
    return generate_permutation_distribution(m, n, n_perm, s, global_rng::instance);
}


