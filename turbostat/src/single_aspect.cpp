//
// Created by filip on 25/08/2021.
//

#include "utils.h"
#include "single_aspect.h"
#include "data_aspects.h"

Rcpp::NumericVector single_aspect (Rcpp::NumericVector x1,
                                   Rcpp::NumericVector x2,
                                   unsigned B,
                                   Rcpp::NumericVector (*aspect)(Rcpp::NumericVector),
                                   dqrng::xoroshiro128plus &rng){
    unsigned n1 = x1.size();
    unsigned n2 = x2.size();
    Rcpp::NumericVector pooled_sample(x1.size() + x2.size());
    for (unsigned i = 0; i < n1; ++i) {
        pooled_sample[i] = x1[i];
    }
    for (unsigned i = 0; i < n2 ; ++i) {
        pooled_sample[n1 + i] = x2[i];
    }

    Rcpp::NumericVector transformed_pooled_sample = aspect(pooled_sample);

    // Rcpp::Rcout << "transformed_pooled_sample " << transformed_pooled_sample << std::endl;

    double obs_stat = std::accumulate(transformed_pooled_sample.begin() , transformed_pooled_sample.begin() + n1 , 0.0)-
                      std::accumulate(transformed_pooled_sample.begin() + n1 , transformed_pooled_sample.end() , 0.0);

    Rcpp::NumericVector perm_stats(B);
    for (unsigned i = 0; i < B ; ++i) {
        std::shuffle(transformed_pooled_sample.begin(), transformed_pooled_sample.end(), rng);
        // transformed_pooled_sample = Rcpp::sample(transformed_pooled_sample, pooled_sample.size());
        perm_stats[i] = std::accumulate(transformed_pooled_sample.begin() , transformed_pooled_sample.begin() + n1 , 0.0)-
                        std::accumulate(transformed_pooled_sample.begin() + n1 , transformed_pooled_sample.end() , 0.0);

    }
    double p_value = (double)Rcpp::sum(Rcpp::ifelse( perm_stats <= obs_stat, 1, 0))/(double)B;
    return Rcpp::NumericVector::create(obs_stat,p_value);
}

Rcpp::NumericVector t_a_permtest_impl (Rcpp::NumericVector x1,
                                       Rcpp::NumericVector x2,
                                       unsigned B,
                                       dqrng::xoroshiro128plus &rng){

    return single_aspect(x1, x2, B, a_aspect, rng);
}

Rcpp::NumericVector t_b_permtest_impl (Rcpp::NumericVector x1,
                                       Rcpp::NumericVector x2,
                                       unsigned B,
                                       dqrng::xoroshiro128plus &rng){
    return single_aspect(x1, x2, B, b_aspect, rng);
}

Rcpp::NumericVector t_c_permtest_impl (Rcpp::NumericVector x1,
                                       Rcpp::NumericVector x2,
                                       unsigned B,
                                       dqrng::xoroshiro128plus &rng){
    return single_aspect(x1, x2, B, c_aspect, rng);
}

Rcpp::NumericVector t_a_permtest (Rcpp::NumericVector x1,
                                  Rcpp::NumericVector x2,
                                  unsigned B,
                                  unsigned seed){
    dqrng::xoroshiro128plus rng(seed);
    return t_a_permtest_impl(x1, x2, B, rng);
}

Rcpp::NumericVector t_b_permtest (Rcpp::NumericVector x1,
                                  Rcpp::NumericVector x2,
                                  unsigned B,
                                  unsigned seed){
    dqrng::xoroshiro128plus rng(seed);
    return t_b_permtest_impl(x1, x2, B, rng);
}

Rcpp::NumericVector t_c_permtest (Rcpp::NumericVector x1,
                                  Rcpp::NumericVector x2,
                                  unsigned B,
                                  unsigned seed){
    dqrng::xoroshiro128plus rng(seed);
    return t_c_permtest_impl(x1, x2, B, rng);
}
