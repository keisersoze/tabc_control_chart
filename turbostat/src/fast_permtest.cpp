//
// Created by filip on 28/11/2021.
//

#include "fast_permtest.h"

#include "Rcpp.h"

#include <algorithm>    // std::count_if

#include <boost/random/normal_distribution.hpp>

fast_permtest::fast_permtest(unsigned m,
                             unsigned n,
                             unsigned n_perm,
                             const simple_statistic &s,
                             dqrng::xoshiro256plus &rng):s(s),perm_stats(n_perm){
    std::vector<double> pooled_sample(m + n);
    boost::random::normal_distribution<double> std_normal_dist (0, 1);
    std::generate(pooled_sample.begin(), pooled_sample.end(),
                  [&rng, &std_normal_dist]() { return std_normal_dist(rng);});
    for (unsigned i = 0; i < n_perm ; ++i) {
        std::shuffle(pooled_sample.begin(), pooled_sample.end(), rng);
        std::vector<double> x1(pooled_sample.begin(), pooled_sample.begin() + m);
        std::vector<double> x2(pooled_sample.begin() + m, pooled_sample.end());
        perm_stats[i] = s(x1,x2);
    }

}

double fast_permtest::operator () (const std::vector<double> &x1,
                                   const std::vector<double> &x2,
                                   dqrng::xoshiro256plus &rng){
    double obs_stat = this->s(x1,x2);
    unsigned position = std::count_if(perm_stats.begin(), perm_stats.end(), [&obs_stat](double x){return x <= obs_stat;});
    double p_value = (double) position / (double) this->perm_stats.size();
    return p_value;
}