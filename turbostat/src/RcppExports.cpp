// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// calibrate_unconditional
Rcpp::NumericMatrix calibrate_unconditional(unsigned m, unsigned n, const std::string& distribution_key, Rcpp::List distribution_parameters, const std::string& monitoring_statistic_key, Rcpp::List monitoring_statistic_parameters, const std::vector<double>& limits_seq, bool is_upper_limit, unsigned nsim, unsigned run_length_cap);
RcppExport SEXP _turbostat_calibrate_unconditional(SEXP mSEXP, SEXP nSEXP, SEXP distribution_keySEXP, SEXP distribution_parametersSEXP, SEXP monitoring_statistic_keySEXP, SEXP monitoring_statistic_parametersSEXP, SEXP limits_seqSEXP, SEXP is_upper_limitSEXP, SEXP nsimSEXP, SEXP run_length_capSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< unsigned >::type m(mSEXP);
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type distribution_key(distribution_keySEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type distribution_parameters(distribution_parametersSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type monitoring_statistic_key(monitoring_statistic_keySEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type monitoring_statistic_parameters(monitoring_statistic_parametersSEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type limits_seq(limits_seqSEXP);
    Rcpp::traits::input_parameter< bool >::type is_upper_limit(is_upper_limitSEXP);
    Rcpp::traits::input_parameter< unsigned >::type nsim(nsimSEXP);
    Rcpp::traits::input_parameter< unsigned >::type run_length_cap(run_length_capSEXP);
    rcpp_result_gen = Rcpp::wrap(calibrate_unconditional(m, n, distribution_key, distribution_parameters, monitoring_statistic_key, monitoring_statistic_parameters, limits_seq, is_upper_limit, nsim, run_length_cap));
    return rcpp_result_gen;
END_RCPP
}
// evaluate_unconditional
Rcpp::DataFrame evaluate_unconditional(unsigned m, unsigned n, Rcpp::List limits, double location_shift, double scale_multiplier, const std::string& distribution_key, Rcpp::List distribution_parameters, const std::string& monitoring_statistic_key, Rcpp::List monitoring_statistic_parameters, unsigned nsim, unsigned run_length_cap);
RcppExport SEXP _turbostat_evaluate_unconditional(SEXP mSEXP, SEXP nSEXP, SEXP limitsSEXP, SEXP location_shiftSEXP, SEXP scale_multiplierSEXP, SEXP distribution_keySEXP, SEXP distribution_parametersSEXP, SEXP monitoring_statistic_keySEXP, SEXP monitoring_statistic_parametersSEXP, SEXP nsimSEXP, SEXP run_length_capSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< unsigned >::type m(mSEXP);
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type limits(limitsSEXP);
    Rcpp::traits::input_parameter< double >::type location_shift(location_shiftSEXP);
    Rcpp::traits::input_parameter< double >::type scale_multiplier(scale_multiplierSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type distribution_key(distribution_keySEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type distribution_parameters(distribution_parametersSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type monitoring_statistic_key(monitoring_statistic_keySEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type monitoring_statistic_parameters(monitoring_statistic_parametersSEXP);
    Rcpp::traits::input_parameter< unsigned >::type nsim(nsimSEXP);
    Rcpp::traits::input_parameter< unsigned >::type run_length_cap(run_length_capSEXP);
    rcpp_result_gen = Rcpp::wrap(evaluate_unconditional(m, n, limits, location_shift, scale_multiplier, distribution_key, distribution_parameters, monitoring_statistic_key, monitoring_statistic_parameters, nsim, run_length_cap));
    return rcpp_result_gen;
END_RCPP
}
// calibrate_conditional
double calibrate_conditional(const std::vector<double>& reference_sample, unsigned n, const std::string& monitoring_statistic_key, Rcpp::List monitoring_statistic_parameters, unsigned target_ARL, bool is_upper_limit, unsigned nsim);
RcppExport SEXP _turbostat_calibrate_conditional(SEXP reference_sampleSEXP, SEXP nSEXP, SEXP monitoring_statistic_keySEXP, SEXP monitoring_statistic_parametersSEXP, SEXP target_ARLSEXP, SEXP is_upper_limitSEXP, SEXP nsimSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type reference_sample(reference_sampleSEXP);
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type monitoring_statistic_key(monitoring_statistic_keySEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type monitoring_statistic_parameters(monitoring_statistic_parametersSEXP);
    Rcpp::traits::input_parameter< unsigned >::type target_ARL(target_ARLSEXP);
    Rcpp::traits::input_parameter< bool >::type is_upper_limit(is_upper_limitSEXP);
    Rcpp::traits::input_parameter< unsigned >::type nsim(nsimSEXP);
    rcpp_result_gen = Rcpp::wrap(calibrate_conditional(reference_sample, n, monitoring_statistic_key, monitoring_statistic_parameters, target_ARL, is_upper_limit, nsim));
    return rcpp_result_gen;
END_RCPP
}
// evaluate_conditional
Rcpp::DataFrame evaluate_conditional(const std::vector<double>& reference_sample, unsigned n, double limit, bool is_upper_limit, const std::vector<double>& shifts, const std::string& monitoring_statistic_key, Rcpp::List monitoring_statistic_parameters, unsigned nsim, unsigned run_length_cap);
RcppExport SEXP _turbostat_evaluate_conditional(SEXP reference_sampleSEXP, SEXP nSEXP, SEXP limitSEXP, SEXP is_upper_limitSEXP, SEXP shiftsSEXP, SEXP monitoring_statistic_keySEXP, SEXP monitoring_statistic_parametersSEXP, SEXP nsimSEXP, SEXP run_length_capSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type reference_sample(reference_sampleSEXP);
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    Rcpp::traits::input_parameter< double >::type limit(limitSEXP);
    Rcpp::traits::input_parameter< bool >::type is_upper_limit(is_upper_limitSEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type shifts(shiftsSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type monitoring_statistic_key(monitoring_statistic_keySEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type monitoring_statistic_parameters(monitoring_statistic_parametersSEXP);
    Rcpp::traits::input_parameter< unsigned >::type nsim(nsimSEXP);
    Rcpp::traits::input_parameter< unsigned >::type run_length_cap(run_length_capSEXP);
    rcpp_result_gen = Rcpp::wrap(evaluate_conditional(reference_sample, n, limit, is_upper_limit, shifts, monitoring_statistic_key, monitoring_statistic_parameters, nsim, run_length_cap));
    return rcpp_result_gen;
END_RCPP
}
// compute_permutation_distribution_r
std::vector<double> compute_permutation_distribution_r(std::string statistic, unsigned m, unsigned n, unsigned n_perm);
RcppExport SEXP _turbostat_compute_permutation_distribution_r(SEXP statisticSEXP, SEXP mSEXP, SEXP nSEXP, SEXP n_permSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type statistic(statisticSEXP);
    Rcpp::traits::input_parameter< unsigned >::type m(mSEXP);
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    Rcpp::traits::input_parameter< unsigned >::type n_perm(n_permSEXP);
    rcpp_result_gen = Rcpp::wrap(compute_permutation_distribution_r(statistic, m, n, n_perm));
    return rcpp_result_gen;
END_RCPP
}
// set_seed
void set_seed(Rcpp::IntegerVector seed);
RcppExport SEXP _turbostat_set_seed(SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::IntegerVector >::type seed(seedSEXP);
    set_seed(seed);
    return R_NilValue;
END_RCPP
}
// t_a_binding
Rcpp::DataFrame t_a_binding(const std::vector<double>& x1, const std::vector<double>& x2, unsigned B);
RcppExport SEXP _turbostat_t_a_binding(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    rcpp_result_gen = Rcpp::wrap(t_a_binding(x1, x2, B));
    return rcpp_result_gen;
END_RCPP
}
// t_b_binding
Rcpp::DataFrame t_b_binding(const std::vector<double>& x1, const std::vector<double>& x2, unsigned B);
RcppExport SEXP _turbostat_t_b_binding(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    rcpp_result_gen = Rcpp::wrap(t_b_binding(x1, x2, B));
    return rcpp_result_gen;
END_RCPP
}
// t_c_binding
Rcpp::DataFrame t_c_binding(const std::vector<double>& x1, const std::vector<double>& x2, unsigned B);
RcppExport SEXP _turbostat_t_c_binding(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    rcpp_result_gen = Rcpp::wrap(t_c_binding(x1, x2, B));
    return rcpp_result_gen;
END_RCPP
}
// t_abc_binding
Rcpp::DataFrame t_abc_binding(const std::vector<double>& x1, const std::vector<double>& x2, unsigned B);
RcppExport SEXP _turbostat_t_abc_binding(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    rcpp_result_gen = Rcpp::wrap(t_abc_binding(x1, x2, B));
    return rcpp_result_gen;
END_RCPP
}
// t_ab_binding
Rcpp::DataFrame t_ab_binding(const std::vector<double>& x1, const std::vector<double>& x2, unsigned B);
RcppExport SEXP _turbostat_t_ab_binding(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    rcpp_result_gen = Rcpp::wrap(t_ab_binding(x1, x2, B));
    return rcpp_result_gen;
END_RCPP
}
// t_bc_binding
Rcpp::DataFrame t_bc_binding(const std::vector<double>& x1, const std::vector<double>& x2, unsigned B);
RcppExport SEXP _turbostat_t_bc_binding(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    rcpp_result_gen = Rcpp::wrap(t_bc_binding(x1, x2, B));
    return rcpp_result_gen;
END_RCPP
}
// t_ac_binding
Rcpp::DataFrame t_ac_binding(const std::vector<double>& x1, const std::vector<double>& x2, unsigned B);
RcppExport SEXP _turbostat_t_ac_binding(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    rcpp_result_gen = Rcpp::wrap(t_ac_binding(x1, x2, B));
    return rcpp_result_gen;
END_RCPP
}
// centered_gamma_with_shape_equal_four_r_test
std::vector<double> centered_gamma_with_shape_equal_four_r_test(unsigned n);
RcppExport SEXP _turbostat_centered_gamma_with_shape_equal_four_r_test(SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    rcpp_result_gen = Rcpp::wrap(centered_gamma_with_shape_equal_four_r_test(n));
    return rcpp_result_gen;
END_RCPP
}
// mirrored_centered_gamma_with_shape_equal_four_r_test
std::vector<double> mirrored_centered_gamma_with_shape_equal_four_r_test(unsigned n);
RcppExport SEXP _turbostat_mirrored_centered_gamma_with_shape_equal_four_r_test(SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    rcpp_result_gen = Rcpp::wrap(mirrored_centered_gamma_with_shape_equal_four_r_test(n));
    return rcpp_result_gen;
END_RCPP
}
// test_exp
std::vector<double> test_exp(unsigned n);
RcppExport SEXP _turbostat_test_exp(SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    rcpp_result_gen = Rcpp::wrap(test_exp(n));
    return rcpp_result_gen;
END_RCPP
}
// test_t_due_e_mezzo
std::vector<double> test_t_due_e_mezzo(unsigned n);
RcppExport SEXP _turbostat_test_t_due_e_mezzo(SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    rcpp_result_gen = Rcpp::wrap(test_t_due_e_mezzo(n));
    return rcpp_result_gen;
END_RCPP
}
// test_laplace
std::vector<double> test_laplace(unsigned n, double location, double scale);
RcppExport SEXP _turbostat_test_laplace(SEXP nSEXP, SEXP locationSEXP, SEXP scaleSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    Rcpp::traits::input_parameter< double >::type location(locationSEXP);
    Rcpp::traits::input_parameter< double >::type scale(scaleSEXP);
    rcpp_result_gen = Rcpp::wrap(test_laplace(n, location, scale));
    return rcpp_result_gen;
END_RCPP
}
// test_cauchy
std::vector<double> test_cauchy(unsigned n, double location, double scale);
RcppExport SEXP _turbostat_test_cauchy(SEXP nSEXP, SEXP locationSEXP, SEXP scaleSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    Rcpp::traits::input_parameter< double >::type location(locationSEXP);
    Rcpp::traits::input_parameter< double >::type scale(scaleSEXP);
    rcpp_result_gen = Rcpp::wrap(test_cauchy(n, location, scale));
    return rcpp_result_gen;
END_RCPP
}
// test_standard_half_cauchy
std::vector<double> test_standard_half_cauchy(unsigned n);
RcppExport SEXP _turbostat_test_standard_half_cauchy(SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    rcpp_result_gen = Rcpp::wrap(test_standard_half_cauchy(n));
    return rcpp_result_gen;
END_RCPP
}
// test1
std::vector<double> test1(unsigned n);
RcppExport SEXP _turbostat_test1(SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    rcpp_result_gen = Rcpp::wrap(test1(n));
    return rcpp_result_gen;
END_RCPP
}
// test_ansari_bradley
double test_ansari_bradley(const std::vector<double>& x1, const std::vector<double>& x2);
RcppExport SEXP _turbostat_test_ansari_bradley(SEXP x1SEXP, SEXP x2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    rcpp_result_gen = Rcpp::wrap(test_ansari_bradley(x1, x2));
    return rcpp_result_gen;
END_RCPP
}
// test_difference_of_means_klotz
double test_difference_of_means_klotz(const std::vector<double>& x1, const std::vector<double>& x2);
RcppExport SEXP _turbostat_test_difference_of_means_klotz(SEXP x1SEXP, SEXP x2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    rcpp_result_gen = Rcpp::wrap(test_difference_of_means_klotz(x1, x2));
    return rcpp_result_gen;
END_RCPP
}
// test_lepage
double test_lepage(const std::vector<double>& x1, const std::vector<double>& x2);
RcppExport SEXP _turbostat_test_lepage(SEXP x1SEXP, SEXP x2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    rcpp_result_gen = Rcpp::wrap(test_lepage(x1, x2));
    return rcpp_result_gen;
END_RCPP
}
// test_cucconi
double test_cucconi(const std::vector<double>& x1, const std::vector<double>& x2);
RcppExport SEXP _turbostat_test_cucconi(SEXP x1SEXP, SEXP x2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    rcpp_result_gen = Rcpp::wrap(test_cucconi(x1, x2));
    return rcpp_result_gen;
END_RCPP
}
// test_percentiles
double test_percentiles(const std::vector<double>& x1, const std::vector<double>& x2, double r, double s);
RcppExport SEXP _turbostat_test_percentiles(SEXP x1SEXP, SEXP x2SEXP, SEXP rSEXP, SEXP sSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< double >::type r(rSEXP);
    Rcpp::traits::input_parameter< double >::type s(sSEXP);
    rcpp_result_gen = Rcpp::wrap(test_percentiles(x1, x2, r, s));
    return rcpp_result_gen;
END_RCPP
}
// test_centered_percentiles
double test_centered_percentiles(const std::vector<double>& x1, const std::vector<double>& x2, double r, double s);
RcppExport SEXP _turbostat_test_centered_percentiles(SEXP x1SEXP, SEXP x2SEXP, SEXP rSEXP, SEXP sSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< double >::type r(rSEXP);
    Rcpp::traits::input_parameter< double >::type s(sSEXP);
    rcpp_result_gen = Rcpp::wrap(test_centered_percentiles(x1, x2, r, s));
    return rcpp_result_gen;
END_RCPP
}
// hello
double hello();
RcppExport SEXP _turbostat_hello() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(hello());
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_turbostat_calibrate_unconditional", (DL_FUNC) &_turbostat_calibrate_unconditional, 10},
    {"_turbostat_evaluate_unconditional", (DL_FUNC) &_turbostat_evaluate_unconditional, 11},
    {"_turbostat_calibrate_conditional", (DL_FUNC) &_turbostat_calibrate_conditional, 7},
    {"_turbostat_evaluate_conditional", (DL_FUNC) &_turbostat_evaluate_conditional, 9},
    {"_turbostat_compute_permutation_distribution_r", (DL_FUNC) &_turbostat_compute_permutation_distribution_r, 4},
    {"_turbostat_set_seed", (DL_FUNC) &_turbostat_set_seed, 1},
    {"_turbostat_t_a_binding", (DL_FUNC) &_turbostat_t_a_binding, 3},
    {"_turbostat_t_b_binding", (DL_FUNC) &_turbostat_t_b_binding, 3},
    {"_turbostat_t_c_binding", (DL_FUNC) &_turbostat_t_c_binding, 3},
    {"_turbostat_t_abc_binding", (DL_FUNC) &_turbostat_t_abc_binding, 3},
    {"_turbostat_t_ab_binding", (DL_FUNC) &_turbostat_t_ab_binding, 3},
    {"_turbostat_t_bc_binding", (DL_FUNC) &_turbostat_t_bc_binding, 3},
    {"_turbostat_t_ac_binding", (DL_FUNC) &_turbostat_t_ac_binding, 3},
    {"_turbostat_centered_gamma_with_shape_equal_four_r_test", (DL_FUNC) &_turbostat_centered_gamma_with_shape_equal_four_r_test, 1},
    {"_turbostat_mirrored_centered_gamma_with_shape_equal_four_r_test", (DL_FUNC) &_turbostat_mirrored_centered_gamma_with_shape_equal_four_r_test, 1},
    {"_turbostat_test_exp", (DL_FUNC) &_turbostat_test_exp, 1},
    {"_turbostat_test_t_due_e_mezzo", (DL_FUNC) &_turbostat_test_t_due_e_mezzo, 1},
    {"_turbostat_test_laplace", (DL_FUNC) &_turbostat_test_laplace, 3},
    {"_turbostat_test_cauchy", (DL_FUNC) &_turbostat_test_cauchy, 3},
    {"_turbostat_test_standard_half_cauchy", (DL_FUNC) &_turbostat_test_standard_half_cauchy, 1},
    {"_turbostat_test1", (DL_FUNC) &_turbostat_test1, 1},
    {"_turbostat_test_ansari_bradley", (DL_FUNC) &_turbostat_test_ansari_bradley, 2},
    {"_turbostat_test_difference_of_means_klotz", (DL_FUNC) &_turbostat_test_difference_of_means_klotz, 2},
    {"_turbostat_test_lepage", (DL_FUNC) &_turbostat_test_lepage, 2},
    {"_turbostat_test_cucconi", (DL_FUNC) &_turbostat_test_cucconi, 2},
    {"_turbostat_test_percentiles", (DL_FUNC) &_turbostat_test_percentiles, 4},
    {"_turbostat_test_centered_percentiles", (DL_FUNC) &_turbostat_test_centered_percentiles, 4},
    {"_turbostat_hello", (DL_FUNC) &_turbostat_hello, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_turbostat(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
