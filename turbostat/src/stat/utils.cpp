//
// Created by filip on 25/08/2021.
//

#include <algorithm>
#include <cassert>
#include "utils.h"

// https://stackoverflow.com/questions/39153082/rcpp-rank-function-that-does-average-ties
//
//class Comparator {
//private:
//    const Rcpp::NumericVector& ref;
//
//    bool is_na(double x) const
//    {
//        return Rcpp::traits::is_na<REALSXP>(x);
//    }
//
//public:
//    Comparator(const Rcpp::NumericVector& ref_)
//            : ref(ref_)
//    {}
//
//    bool operator()(const int ilhs, const int irhs) const
//    {
//        double lhs = ref[ilhs], rhs = ref[irhs];
//        if (is_na(lhs)) return false;
//        if (is_na(rhs)) return true;
//        return lhs < rhs;
//    }
//};
//
//Rcpp::NumericVector avg_rank(Rcpp::NumericVector x)
//{
//    R_xlen_t sz = x.size();
//    Rcpp::IntegerVector w = Rcpp::seq(0, sz - 1);
//    std::sort(w.begin(), w.end(), Comparator(x));
//
//    Rcpp::NumericVector r = Rcpp::no_init_vector(sz);
//    for (R_xlen_t n, i = 0; i < sz; i += n) {
//        n = 1;
//        while (i + n < sz && x[w[i]] == x[w[i + n]]) ++n;
//        for (R_xlen_t k = 0; k < n; k++) {
//            r[w[i + k]] = i + (n + 1) / 2.;
//        }
//    }
//
//    return r;
//}

std::vector<double> avg_rank(const std::vector<double> &v){
    std::vector<std::size_t> w(v.size());
    std::iota(begin(w), end(w), 0);
    std::sort(begin(w), end(w),
              [&v](std::size_t i, std::size_t j) { return v[i] < v[j]; });

    std::vector<double> r(w.size());
    for (std::size_t n, i = 0; i < w.size(); i += n){
        n = 1;
        while (i + n < w.size() && v[w[i]] == v[w[i+n]]) ++n;
        for (std::size_t k = 0; k < n; ++k){
            r[w[i+k]] = i + (n + 1) / 2.0; // average rank of n tied values
            // r[w[i+k]] = i + 1;          // min
            // r[w[i+k]] = i + n;          // max
            // r[w[i+k]] = i + k + 1;      // random order
        }
    }
    return r;
}

double median (std::vector<double> len){
    assert(!len.empty());
    if (len.size() % 2 == 0) {
        const auto median_it1 = len.begin() + len.size() / 2 - 1;
        const auto median_it2 = len.begin() + len.size() / 2;

        std::nth_element(len.begin(), median_it1 , len.end());
        const auto e1 = *median_it1;

        std::nth_element(len.begin(), median_it2 , len.end());
        const auto e2 = *median_it2;

        return (e1 + e2) / 2;

    } else {
        const auto median_it = len.begin() + len.size() / 2;
        std::nth_element(len.begin(), median_it , len.end());
        return *median_it;
    }
}

double mean(const std::vector<double> &x){
    return std::accumulate(x.begin(), x.end() , 0.0) / (double) x.size();
}

double standard_deviation(const std::vector<double> &v){
    double m = mean(v);
    std::vector<double> diff(v.size());
    std::transform(v.begin(), v.end(), diff.begin(), [m](double x) { return x - m; });
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / (double) v.size());
    return stdev;
}


//Rcpp::IntegerVector order(Rcpp::NumericVector v) {
//
//    // initialize original index locations
//    Rcpp::IntegerVector idx = Rcpp::seq(0, v.size()-1);
//
//    // sort indexes based on comparing values in v
//    // using std::stable_sort instead of std::sort
//    // to avoid unnecessary index re-orderings
//    // when v contains elements of equal values
//    std::stable_sort(idx.begin(), idx.end(),
//                     [&v](int i1, int i2) {return v[i1] < v[i2];});
//
//    return idx;
//}
//
//Rcpp::IntegerVector order(Rcpp::IntegerVector v) {
//
//    // initialize original index locations
//    Rcpp::IntegerVector idx = Rcpp::seq(0, v.size()-1);
//
//    // sort indexes based on comparing values in v
//    // using std::stable_sort instead of std::sort
//    // to avoid unnecessary index re-orderings
//    // when v contains elements of equal values
//    std::stable_sort(idx.begin(), idx.end(),
//                     [&v](int i1, int i2) {return v[i1] < v[i2];});
//
//    return idx;
//}
//
//Rcpp::NumericVector sample_with_replacement(Rcpp::NumericVector v, unsigned sample_size, dqrng::xoroshiro128plus &rng){
//    std::uniform_int_distribution<> dist(0, v.size()-1);
//    Rcpp::NumericVector res (sample_size);
//    for (unsigned i = 0; i < sample_size; ++i) {
//        unsigned rn = dist(rng);
//        res[i] = v[rn];
//    }
//    return res;
//}
