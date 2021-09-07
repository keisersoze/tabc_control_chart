// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// t_a_binding
Rcpp::DataFrame t_a_binding(const std::vector<double>& x1, const std::vector<double>& x2, unsigned B, unsigned seed);
RcppExport SEXP _turbostat_t_a_binding(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP, SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    Rcpp::traits::input_parameter< unsigned >::type seed(seedSEXP);
    rcpp_result_gen = Rcpp::wrap(t_a_binding(x1, x2, B, seed));
    return rcpp_result_gen;
END_RCPP
}
// t_b_binding
Rcpp::DataFrame t_b_binding(const std::vector<double>& x1, const std::vector<double>& x2, unsigned B, unsigned seed);
RcppExport SEXP _turbostat_t_b_binding(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP, SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    Rcpp::traits::input_parameter< unsigned >::type seed(seedSEXP);
    rcpp_result_gen = Rcpp::wrap(t_b_binding(x1, x2, B, seed));
    return rcpp_result_gen;
END_RCPP
}
// t_c_binding
Rcpp::DataFrame t_c_binding(const std::vector<double>& x1, const std::vector<double>& x2, unsigned B, unsigned seed);
RcppExport SEXP _turbostat_t_c_binding(SEXP x1SEXP, SEXP x2SEXP, SEXP BSEXP, SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x1(x1SEXP);
    Rcpp::traits::input_parameter< const std::vector<double>& >::type x2(x2SEXP);
    Rcpp::traits::input_parameter< unsigned >::type B(BSEXP);
    Rcpp::traits::input_parameter< unsigned >::type seed(seedSEXP);
    rcpp_result_gen = Rcpp::wrap(t_c_binding(x1, x2, B, seed));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_turbostat_t_a_binding", (DL_FUNC) &_turbostat_t_a_binding, 4},
    {"_turbostat_t_b_binding", (DL_FUNC) &_turbostat_t_b_binding, 4},
    {"_turbostat_t_c_binding", (DL_FUNC) &_turbostat_t_c_binding, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_turbostat(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
