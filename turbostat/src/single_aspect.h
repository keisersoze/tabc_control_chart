//
// Created by filip on 23/08/2021.
//

#ifndef RACE_SINGLE_ASPECT_H
#define RACE_SINGLE_ASPECT_H

#include <vector>
#include <algorithm>    // std::count_if
#include <numeric>

#include "test_interface.h"
#include "utils.h"
#include "single_aspect.h"
#include "data_aspects.h"

template <class RNG>
perm_test_result single_aspect (const std::vector<double> &x1,
                                const std::vector<double> &x2,
                                unsigned n_perm,
                                std::vector<double> (*aspect)(const std::vector<double> &),
                                RNG &rng){
    unsigned n1 = x1.size();
    unsigned n2 = x2.size();
    std::vector<double> pooled_sample(x1.size() + x2.size());
    for (unsigned i = 0; i < n1; ++i) {
        pooled_sample[i] = x1[i];
    }
    for (unsigned i = 0; i < n2 ; ++i) {
        pooled_sample[n1 + i] = x2[i];
    }

    std::vector<double> transformed_pooled_sample = aspect(pooled_sample);

    // Rcpp::Rcout << "transformed_pooled_sample " << transformed_pooled_sample << std::endl;

    double obs_stat = std::accumulate(transformed_pooled_sample.begin() + n1 , transformed_pooled_sample.end() , 0.0);

    std::vector<double> perm_stats(n_perm);
    for (unsigned i = 0; i < n_perm ; ++i) {
        std::shuffle(transformed_pooled_sample.begin(), transformed_pooled_sample.end(), rng);
        perm_stats[i] = std::accumulate(transformed_pooled_sample.begin() + n1 , transformed_pooled_sample.end() , 0.0);

    }

    unsigned position = std::count_if(perm_stats.begin(), perm_stats.end(), [obs_stat](double x){return x >= obs_stat;});

    perm_test_result res(obs_stat, n_perm, position);
    return res;
}

template <class RNG>
perm_test_result t_a_permtest (const std::vector<double> &x1,
                               const std::vector<double> &x2,
                               unsigned n_perm,
                               RNG &rng){

    return single_aspect(x1, x2, n_perm, a_aspect, rng);
}

template <class RNG>
perm_test_result t_b_permtest (const std::vector<double> &x1,
                               const std::vector<double> &x2,
                               unsigned n_perm,
                               RNG &rng){
    return single_aspect(x1, x2, n_perm, b_aspect, rng);
}

template <class RNG>
perm_test_result t_c_permtest (const std::vector<double> &x1,
                               const std::vector<double> &x2,
                               unsigned n_perm,
                               RNG &rng){
    return single_aspect(x1, x2, n_perm, c_aspect, rng);
}
#endif //RACE_SINGLE_ASPECT_H
