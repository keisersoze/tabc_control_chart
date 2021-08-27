// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// find_UCL
double find_UCL(Rcpp::NumericVector reference_sample, unsigned n, double target_ARL, unsigned nsim, unsigned nperm, const std::string& test);
RcppExport SEXP _turbostat_find_UCL(SEXP reference_sampleSEXP, SEXP nSEXP, SEXP target_ARLSEXP, SEXP nsimSEXP, SEXP npermSEXP, SEXP testSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type reference_sample(reference_sampleSEXP);
    Rcpp::traits::input_parameter< unsigned >::type n(nSEXP);
    Rcpp::traits::input_parameter< double >::type target_ARL(target_ARLSEXP);
    Rcpp::traits::input_parameter< unsigned >::type nsim(nsimSEXP);
    Rcpp::traits::input_parameter< unsigned >::type nperm(npermSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type test(testSEXP);
    rcpp_result_gen = Rcpp::wrap(find_UCL(reference_sample, n, target_ARL, nsim, nperm, test));
    return rcpp_result_gen;
END_RCPP
}
// t_a_permtest
Rcpp::NumericVector t_a_permtest(Rcpp::NumericVector x1, Rcpp::NumericVector x2, unsigned B);
RcppExport SEXP _turbostat_t_a_permtest(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    rcpp_result_gen = Rcpp::wrap(t_a_permtest(x1, x2, B));
    return rcpp_result_gen;
END_RCPP
}
// t_b_permtest
Rcpp::NumericVector t_b_permtest(Rcpp::NumericVector x1, Rcpp::NumericVector x2, unsigned B);
RcppExport SEXP _turbostat_t_b_permtest(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    rcpp_result_gen = Rcpp::wrap(t_b_permtest(x1, x2, B));
    return rcpp_result_gen;
END_RCPP
}
// t_c_permtest
Rcpp::NumericVector t_c_permtest(Rcpp::NumericVector x1, Rcpp::NumericVector x2, unsigned B);
RcppExport SEXP _turbostat_t_c_permtest(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    rcpp_result_gen = Rcpp::wrap(t_c_permtest(x1, x2, B));
    return rcpp_result_gen;
END_RCPP
}
// t_abc_permtest
Rcpp::NumericVector t_abc_permtest(Rcpp::NumericVector x1, Rcpp::NumericVector x2, unsigned B);
RcppExport SEXP _turbostat_t_abc_permtest(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    rcpp_result_gen = Rcpp::wrap(t_abc_permtest(x1, x2, B));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_turbostat_find_UCL", (DL_FUNC) &_turbostat_find_UCL, 6},
    {"_turbostat_t_a_permtest", (DL_FUNC) &_turbostat_t_a_permtest, 3},
    {"_turbostat_t_b_permtest", (DL_FUNC) &_turbostat_t_b_permtest, 3},
    {"_turbostat_t_c_permtest", (DL_FUNC) &_turbostat_t_c_permtest, 3},
    {"_turbostat_t_abc_permtest", (DL_FUNC) &_turbostat_t_abc_permtest, 3},
    {NULL, NULL, 0}
};

RcppExport void R_init_turbostat(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
