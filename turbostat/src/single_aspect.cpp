//
// Created by filip on 25/08/2021.
//

#include "utils.h"
#include "single_aspect.h"
#include "old_Rcpp/data_aspects.h"

std::vector<double> single_aspect (const std::vector<double> &x1,
                                   const std::vector<double> &x2,
                                   unsigned B,
                                   std::vector<double> (*aspect)(const std::vector<double> &),
                                   dqrng::xoroshiro128plus &rng){
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

    double obs_stat = std::accumulate(transformed_pooled_sample.begin() , transformed_pooled_sample.begin() + n1 , 0.0)-
                      std::accumulate(transformed_pooled_sample.begin() + n1 , transformed_pooled_sample.end() , 0.0);

    std::vector<double> perm_stats(B);
    for (unsigned i = 0; i < B ; ++i) {
        std::shuffle(transformed_pooled_sample.begin(), transformed_pooled_sample.end(), rng);
        perm_stats[i] = std::accumulate(transformed_pooled_sample.begin() , transformed_pooled_sample.begin() + n1 , 0.0)-
                        std::accumulate(transformed_pooled_sample.begin() + n1 , transformed_pooled_sample.end() , 0.0);

    }

    unsigned position = std::count_if(perm_stats.begin(), perm_stats.end(), [](int x){return x <= obs_stat;});

    double p_value = (double) position /(double)B;

    return std::vector<double>({obs_stat,p_value, position});
}

std::vector<double> t_a_permtest_impl (const std::vector<double> &x1,
                                       const std::vector<double> &x2,
                                       unsigned B,
                                       dqrng::xoroshiro128plus &rng){

    return single_aspect(x1, x2, B, a_aspect, rng);
}

std::vector<double> t_b_permtest_impl (const std::vector<double> &x1,
                                       const std::vector<double> &x2,
                                       unsigned B,
                                       dqrng::xoroshiro128plus &rng){
    return single_aspect(x1, x2, B, b_aspect, rng);
}

std::vector<double> t_c_permtest_impl (const std::vector<double> &x1,
                                       const std::vector<double> &x2,
                                       unsigned B,
                                       dqrng::xoroshiro128plus &rng){
    return single_aspect(x1, x2, B, c_aspect, rng);
}

std::vector<double> t_a_permtest (const std::vector<double> &x1,
                                  const std::vector<double> &x2,
                                  unsigned B,
                                  unsigned seed){
    dqrng::xoroshiro128plus rng(seed);
    return t_a_permtest_impl(x1, x2, B, rng);
}

std::vector<double> t_b_permtest (const std::vector<double> &x1,
                                  const std::vector<double> &x2,
                                  unsigned B,
                                  unsigned seed){
    dqrng::xoroshiro128plus rng(seed);
    return t_b_permtest_impl(x1, x2, B, rng);
}

std::vector<double> t_c_permtest (const std::vector<double> &x1,
                                  const std::vector<double> &x2,
                                  unsigned B,
                                  unsigned seed){
    dqrng::xoroshiro128plus rng(seed);
    return t_c_permtest_impl(x1, x2, B, rng);
}
