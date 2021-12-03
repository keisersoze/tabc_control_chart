//
// Created by filip on 09/10/2021.
//

#include "simple_stats.h"

#include "data_aspects.h"

#include "numeric" //accumulate

#include "utils.h" //median

#include <cmath>        // std::abs
#include <math.h>       /* pow */

#include <boost/math/distributions/normal.hpp>

#include "Rcpp.h"



double wilcoxon_rank_sum (const std::vector<double> &x1,
                          const std::vector<double> &x2){
    unsigned n1 = x1.size();
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    std::vector<double> transformed_pooled_sample = c_aspect(pooled_sample);
    double obs_stat = std::accumulate(transformed_pooled_sample.begin() , transformed_pooled_sample.begin() + n1 , 0.0)-
                      std::accumulate(transformed_pooled_sample.begin() + n1 , transformed_pooled_sample.end() , 0.0);
    return obs_stat;
}

double difference_of_rank_means (const std::vector<double> &x1,
                                 const std::vector<double> &x2){
    unsigned n1 = x1.size();
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    std::vector<double> transformed_pooled_sample = c_aspect(pooled_sample);
    double obs_stat = std::accumulate(transformed_pooled_sample.begin() , transformed_pooled_sample.begin() + n1 , 0.0) / (double) x1.size() -
                      std::accumulate(transformed_pooled_sample.begin() + n1 , transformed_pooled_sample.end() , 0.0) / (double) x2.size();
    return obs_stat;
}

double mann_whitney (const std::vector<double> &x1,
                     const std::vector<double> &x2){
    unsigned n1 = x1.size();
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    std::vector<double> ranks = c_aspect(pooled_sample);
    double sum_of_x1_ranks = std::accumulate(ranks.begin(), ranks.begin() + n1, 0.0);
    double obs_stat = sum_of_x1_ranks - (double) n1 * ((double) (n1 + 1))/2.0;
    return obs_stat;
}

double sum_of_signs (const std::vector<double> &x1,
                     const std::vector<double> &x2){
    unsigned n1 = x1.size();
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    std::vector<double> signs = b_aspect(pooled_sample);
    double obs_stat = std::accumulate(signs.begin() + n1, signs.end(), 0.0);
    return obs_stat;
}

double difference_of_sums (const std::vector<double> &x1,
                           const std::vector<double> &x2){
    double obs_stat = std::accumulate(x1.begin(), x1.end() , 0.0)-
                      std::accumulate(x2.begin(), x2.end() , 0.0);
    return obs_stat;
}

double difference_of_means (const std::vector<double> &x1,
                           const std::vector<double> &x2){
    double obs_stat = std::accumulate(x1.begin(), x1.end() , 0.0) / (double) x1.size() -
                      std::accumulate(x2.begin(), x2.end() , 0.0) / (double) x2.size();
    return obs_stat;
}

double x2_sum (const std::vector<double> &x1,
               const std::vector<double> &x2){
    double obs_stat = std::accumulate(x2.begin(), x2.end() , 0.0);
    return obs_stat;
}

double x2_mean (const std::vector<double> &x1,
                const std::vector<double> &x2){
    double obs_stat = std::accumulate(x2.begin(), x2.end() , 0.0);
    return obs_stat / (double) x2.size();
}

double precedence (const std::vector<double> &x1,
                   const std::vector<double> &x2){
    double m = median(x2);
    double stat = std::count_if(x1.begin(), x1.end(), [&m](double x) { return x >= m; });
    return stat;
}

double sum_of_signs_v2 (const std::vector<double> &x1,
                        const std::vector<double> &x2){
    double m = median(x1);
    double stat = std::count_if(x2.begin(), x2.end(), [&m](double x) { return x >= m; });
    return stat;
}

// Scale

double conover_statistic (const std::vector<double> &x1,
                          const std::vector<double> &x2){
    double x1_mean = mean(x1);
    double x2_mean = mean(x2);
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    for (int i = 0; i < x1.size(); ++i) {
        pooled_sample[i] = std::abs(pooled_sample[i] - x1_mean);
    }
    for (int i = x1.size(); i < x1.size() + x2.size(); ++i) {
        pooled_sample[i] = std::abs(pooled_sample[i] - x2_mean);
    }
    std::vector<double> ranks = avg_rank(pooled_sample);
    std::transform(ranks.begin(),
                   ranks.end(),
                   ranks.begin(),
                   [] (double x) -> double { return x*x; });
    double conover_stat = 0;
    for (int i = x1.size(); i < x1.size() + x2.size(); ++i) {
        conover_stat += ranks[i];
    }
    return conover_stat;
}

double mood_statistic (const std::vector<double> &x1,
                       const std::vector<double> &x2){
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    std::vector<double> ranks = avg_rank(pooled_sample);
    double mood_stat = 0;
    for (int i = x1.size(); i < x1.size() + x2.size(); ++i) {
        mood_stat += std::pow(ranks[i] - (x1.size() + x2.size() + 1.0)/2.0, 2.0);
    }
    return mood_stat;
}

double ab_statistic (const std::vector<double> &x1,
                     const std::vector<double> &x2){
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    std::vector<double> ranks = avg_rank(pooled_sample);
    double ab_statistic = 0;
    for (int i = x1.size(); i < x1.size() + x2.size(); ++i) {
        ab_statistic += std::abs(ranks[i] - (x1.size() + x2.size() + 1.0)/2.0);
    }
    return ab_statistic;
}

double difference_of_means_ab_statistic (const std::vector<double> &x1,
                                         const std::vector<double> &x2){
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    std::vector<double> ranks = avg_rank(pooled_sample);
    double ab_stat_x1 = 0;
    for (int i = 0; i < x1.size(); ++i) {
        ab_stat_x1 += std::abs(ranks[i] - (x1.size() + x2.size() + 1.0)/2.0);
    }
    double ab_stat_x2 = 0;
    for (int i = x1.size(); i < x1.size() + x2.size(); ++i) {
        ab_stat_x2 += std::abs(ranks[i] - (x1.size() + x2.size() + 1.0)/2.0);
    }
    return ab_stat_x1 / x1.size() - ab_stat_x2 / x2.size();
}

double klotz_statistic (const std::vector<double> &x1,
                        const std::vector<double> &x2){
    boost::math::normal dist(0.0, 1.0);
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    std::vector<double> ranks = avg_rank(pooled_sample);
    double klotz_stat = 0;
    for (int i = x1.size(); i < x1.size() + x2.size(); ++i) {
        double _x = quantile(dist, ranks[i]/(x1.size() + x2.size() + 1));
        klotz_stat += std::pow(_x, 2.0);
    }
    return klotz_stat;
}

double difference_of_means_klotz (const std::vector<double> &x1,
                                  const std::vector<double> &x2){
    boost::math::normal dist(0.0, 1.0);
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    std::vector<double> ranks = avg_rank(pooled_sample);
    double klotz_stat_x1 = 0;
    for (int i = 0; i < x1.size() ; ++i) {
        double _x = quantile(dist, ranks[i]/(x1.size() + x2.size() + 1));
        klotz_stat_x1 += std::pow(_x, 2.0);
    }
    double klotz_stat_x2 = 0;
    for (int i = x1.size(); i < x1.size() + x2.size(); ++i) {
        double _x = quantile(dist, ranks[i]/(x1.size() + x2.size() + 1));
        klotz_stat_x2 += std::pow(_x, 2.0);
    }
    return klotz_stat_x1 / x1.size() - klotz_stat_x2 / x2.size() ;
}

double fab_statistic (const std::vector<double> &x1,
                      const std::vector<double> &x2){
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    std::vector<double> ranks = avg_rank(pooled_sample);
    double ab_stat = 0;
    for (int i = x1.size(); i < x1.size() + x2.size(); ++i) {
        ab_stat += std::abs(ranks[i] - (x1.size() + x2.size() + 1.0)/2.0);
    }
    return (x2.size() * (x1.size() + x2.size() + 1.0))/2.0 - ab_stat;
}

double cucconi (const std::vector<double> &x1,
                const std::vector<double> &x2){
    std::vector<double> vett(x1);
    vett.insert(vett.end(), x2.begin(), x2.end());
    double enne1 = (double) x1.size();
    double enne2 = (double) x2.size();
    double enne = (double) vett.size();
    double media = enne2 * (enne + 1.0) * (2.0 * enne + 1.0);
    double scarto = std::sqrt(enne1 * enne2 * (enne + 1.0) * (2.0 * enne + 1.0) * (8.0 * enne + 11.0)/5.0);
    double ro = 2.0 * (std::pow(enne, 2.0) - 4.0)/(2.0 * enne + 1.0)/(8.0 * enne + 11.0) - 1.0;


    std::vector<double> ranghi = avg_rank(vett);

    std::vector<double> squared_ranks(enne2);
    std::transform(ranghi.begin() + enne1,
                   ranghi.end(),
                   squared_ranks.begin(),
                   [] (double x) -> double { return std::pow(x, 2.0); });
    double sum_of_squared_ranks = std::accumulate(squared_ranks.begin() , squared_ranks.end() , 0.0);

    std::vector<double> squared_contrary_ranks(enne2);
    std::transform(ranghi.begin() + enne1,
                   ranghi.end(),
                   squared_contrary_ranks.begin(),
                   [enne] (double x) -> double { return std::pow(enne + 1.0 - x,2.0); });
    double sum_of_squared_contrary_ranks = std::accumulate(squared_contrary_ranks.begin() , squared_contrary_ranks.end() , 0.0);

    double u = (6.0 * sum_of_squared_ranks - media)/scarto;
    double v = (6.0 * sum_of_squared_contrary_ranks-media)/scarto;
    double cuc = (std::pow(u,2.0)+std::pow(v,2.0)-2.0*u*v*ro)/2.0/(1.0-std::pow(ro, 2.0));

    return cuc;
}

double lepage (const std::vector<double> &x1,
               const std::vector<double> &x2){
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    std::vector<double> ranks = avg_rank(pooled_sample);

    double m = (double) x1.size();
    double n = (double) x2.size();
    double N = n + m;

    double wilcoxon_rank_sum = std::accumulate(ranks.begin() + x1.size()  , ranks.end() , 0.0);
    double ab_statistic = 0;
    for (int i = x1.size(); i < x1.size() + x2.size() ; ++i) {
        ab_statistic += std::abs(ranks[i] - (m + n + 1.0)/2.0);
    }

    double wilcoxon_mean = (n/2.0) * (N + 1);
    double wilcoxon_var = (1.0/12.0) * m * n * (N + 1);
    double standardized_wilcoxon = std::pow(wilcoxon_rank_sum - wilcoxon_mean, 2.0)/ wilcoxon_var;

    double ab_mean;
    double ab_var;
    if ((x1.size() + x2.size()) % 2 == 0) {
        ab_mean = (n * N) / 4.0;
        ab_var = (1.0/48.0) * m * n * (std::pow(N, 2.0) - 4.0)/(N - 1) ;

    } else {
        ab_mean = (n * (std::pow(N, 2.0) - 1))/(4.0 * N);
        ab_var = (1.0/48.0) * m * n * (N + 1) *  (std::pow(N, 2.0) + 3.0) / std::pow(N, 2.0);
    }
    double standardized_ab =  std::pow(ab_statistic - ab_mean, 2.0)/ ab_var;

    return standardized_wilcoxon +  standardized_ab;

}

