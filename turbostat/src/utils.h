//
// Created by filip on 22/08/2021.
//

#ifndef RACE_UTILS_H
#define RACE_UTILS_H

#include <Rcpp.h>

#include <xoshiro.h>

Rcpp::NumericVector avg_rank(Rcpp::NumericVector x);

Rcpp::IntegerVector order(Rcpp::NumericVector v);

Rcpp::IntegerVector order(Rcpp::IntegerVector v);

Rcpp::NumericVector sample_with_replacement(Rcpp::NumericVector v, unsigned sample_size, dqrng::xoroshiro128plus &rng);

template <class T>
std::vector<T> sample_with_replacement(const std::vector<T> &v, unsigned sample_size, dqrng::xoroshiro128plus &rng){
    std::uniform_int_distribution<> dist(0, v.size()-1);
    std::vector<T> res (sample_size);
    for (unsigned i = 0; i < sample_size; ++i) {
        unsigned rn = dist(rng);
        res[i] = v[rn];
    }
    return res;
}

double median (const std::vector<double> &len){
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

#endif //RACE_UTILS_H
