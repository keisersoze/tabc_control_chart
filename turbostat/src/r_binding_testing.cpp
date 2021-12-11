//
// Created by filip on 03/12/2021.
//

#include <string>
#include <vector>
#include <iostream>

#include <Rcpp.h>
#include <xoshiro.h>
#include <convert_seed.h>

#include "rng/global_rng.h"

#include "stat/tests/single_aspect.h"
#include "stat/tests/multiple_aspects.h"
#include "stat/simple_stats.h"
#include "charts/npc/npc_df_chart.h"

#include "stat/distribution.h"
#include <boost/random/normal_distribution.hpp>
#include <boost/random/cauchy_distribution.hpp>
#include <boost/random/laplace_distribution.hpp>
#include <boost/random/student_t_distribution.hpp>
#include <boost/random/chi_squared_distribution.hpp>

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

// [[Rcpp::export(test.ansari_bradley)]]
double  test_ansari_bradley(const std::vector<double> &x1,
                            const std::vector<double> &x2) {
    return ab_statistic(x1, x2);
}

// [[Rcpp::export(test.difference_of_means_klotz)]]
double  test_difference_of_means_klotz(const std::vector<double> &x1,
                                       const std::vector<double> &x2) {
    return difference_of_means_klotz(x1, x2);
}

// [[Rcpp::export(test.lepage)]]
double  test_lepage(const std::vector<double> &x1,
                    const std::vector<double> &x2) {
    return lepage(x1, x2);
}

// [[Rcpp::export(test.cucconi)]]
double  test_cucconi(const std::vector<double> &x1,
                     const std::vector<double> &x2) {
    return cucconi(x1, x2);
}

//' @export
// [[Rcpp::export(test.percentiles)]]
double  test_percentiles(const std::vector<double> &x1,
                     const std::vector<double> &x2,
                     double r,
                     double s) {
    return wilcoxon_percentiles(x1, x2, r, s);
}


// [[Rcpp::export(hello)]]
double hello() {
    return 3.0;
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
//        Rcpp::function("hello"