//
// Created by filip on 28/11/2021.
//

#include "npc_df_chart.h"

#include "Rcpp.h"

#include <algorithm>    // std::count_if std::upper_bound

#include <cmath>        // std::abs

#include <boost/random/normal_distribution.hpp>
#include <boost/math/distributions/normal.hpp>



std::vector<double> generate_permutation_distribution(unsigned m,
                                                      unsigned n,
                                                      unsigned n_perm,
                                                      const simple_statistic &s,
                                                      dqrng::xoshiro256plus &rng){
    std::vector<double> permutation_distribution(n_perm);
    std::vector<double> pooled_sample(m + n);
    boost::random::normal_distribution<double> std_normal_dist (0, 1);
    std::generate(pooled_sample.begin(), pooled_sample.end(),
                  [&rng, &std_normal_dist]() { return std_normal_dist(rng);});
    for (unsigned i = 0; i < n_perm ; ++i) {
        std::shuffle(pooled_sample.begin(), pooled_sample.end(), rng);
        std::vector<double> x1(pooled_sample.begin(), pooled_sample.begin() + m);
        std::vector<double> x2(pooled_sample.begin() + m, pooled_sample.end());
        permutation_distribution[i] = s(x1,x2);
    }
    return permutation_distribution;
}

fast_permtest::fast_permtest(const simple_statistic &s,
                             const std::vector<double> &permutation_distribution,
                             const std::string &tail_key)
                             :s(s),permutation_distribution(permutation_distribution){
    if(tail_key == "left"){
        is_two_sided = false;
        comparator = std::less<double>();
        std::sort(this->permutation_distribution.begin(), this->permutation_distribution.end(), comparator);
    } else if (tail_key == "right") {
        is_two_sided = false;
        comparator = std::greater<double>();
        std::sort(this->permutation_distribution.begin(), this->permutation_distribution.end(), comparator);
    }else if (tail_key == "two_sided"){
        is_two_sided = true;
        comparator = std::greater<double>();
        std::transform(this->permutation_distribution.begin(),
                       this->permutation_distribution.end(),
                       this->permutation_distribution.begin(),
                       [] (double x) -> double {return std::abs(x);});
        std::sort(this->permutation_distribution.begin(), this->permutation_distribution.end(), comparator);
//        for (int i = 0; i < this->permutation_distribution.size(); ++i) {
//            Rcpp::Rcout << this->permutation_distribution[i] << std::endl;
//        }
    } else {
        throw std::invalid_argument( "tail_key" );
    }
}

double fast_permtest::operator () (const std::vector<double> &x1,
                                   const std::vector<double> &x2,
                                   dqrng::xoshiro256plus &rng){
    double obs_stat = s(x1,x2);
    if (is_two_sided){
        obs_stat = std::abs(obs_stat);
    }
    auto it = std::upper_bound(permutation_distribution.begin(),
                               permutation_distribution.end(),
                               obs_stat,
                               comparator);
    unsigned position = it - permutation_distribution.begin();
    double p_value = (0.5 + (double) position) / (1.0 + (double) permutation_distribution.size());
    return p_value;
}

double tippet(const std::vector<double> &p_values){
    return *std::min_element(p_values.begin(),p_values.end());
}

double fisher(const std::vector<double> &p_values){
    std::vector<double> p_values_copy(p_values.size());
    std::transform(p_values.begin(),
                   p_values.end(),
                   p_values_copy.begin(),
                   [] (double x) -> double {return std::log(x);});
    return std::accumulate(p_values_copy.begin(), p_values_copy.end() , 0.0);
}

double liptak(const std::vector<double> &p_values){
    std::vector<double> p_values_copy(p_values.size());
    boost::math::normal dist(0.0, 1.0);
    std::transform(p_values.begin(),
                   p_values.end(),
                   p_values_copy.begin(),
                   [&dist] (double x) -> double {return cdf(dist,x);});
    return std::accumulate(p_values_copy.begin(), p_values_copy.end() , 0.0);
}


npc_df_chart::npc_df_chart(const std::vector<fast_permtest> &perm_tests,
                           const combining_function &cf)
                           :perm_tests(perm_tests), cf(cf) {}

double npc_df_chart::operator () (const std::vector<double> &x1,
                                  const std::vector<double> &x2,
                                  dqrng::xoshiro256plus &rng){
    std::vector<double> p_values(perm_tests.size());
    for (int i = 0; i < perm_tests.size(); ++i) {
        p_values[i] = perm_tests[i](x1,x2,rng);
    }
    return cf(p_values);
}