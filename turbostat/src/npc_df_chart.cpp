//
// Created by filip on 28/11/2021.
//

#include "npc_df_chart.h"

#include "Rcpp.h"

#include <algorithm>    // std::count_if

#include <boost/random/normal_distribution.hpp>


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
        comparator = std::less_equal<double>();
    } else if (tail_key == "right"){
        comparator = std::greater_equal<double>();
    } else {
        throw std::invalid_argument( "tail_key" );
    }
}

double fast_permtest::operator () (const std::vector<double> &x1,
                                   const std::vector<double> &x2,
                                   dqrng::xoshiro256plus &rng){
    double obs_stat = s(x1,x2);
    unsigned position = std::count_if(permutation_distribution.begin(),
                                      permutation_distribution.end(),
                                      [&obs_stat, this](double x){return comparator(x, obs_stat);});
    double p_value = (double) position / (double) permutation_distribution.size();
    return p_value;
}


npc_df_chart::npc_df_chart(const std::vector<fast_permtest> &perm_tests):perm_tests(perm_tests){}

double npc_df_chart::operator () (const std::vector<double> &x1,
                                  const std::vector<double> &x2,
                                  dqrng::xoshiro256plus &rng){
    std::vector<double> p_values(perm_tests.size());
    for (int i = 0; i < perm_tests.size(); ++i) {
        p_values[i] = perm_tests[i](x1,x2,rng);
    }
    return *std::min_element(p_values.begin(),p_values.end());
}