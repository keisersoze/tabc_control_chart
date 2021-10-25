//
// Created by filip on 09/10/2021.
//

#include "simple_stats.h"

#include "data_aspects.h"

#include "numeric" //accumulate

#include "utils.h" //median


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

double precedence (const std::vector<double> &x1,
                   const std::vector<double> &x2){
    double m = median(x2);
    double stat = std::count_if(x1.begin(), x1.end(), [&m](double x) { return x >= m; });
    return stat;
}
