//
// Created by filip on 22/08/2021.
//

#ifndef RACE_UTILS_H
#define RACE_UTILS_H

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

Rcpp::IntegerVector order(Rcpp::IntegerVector v) {

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

#endif //RACE_UTILS_H
