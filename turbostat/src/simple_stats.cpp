//
// Created by filip on 09/10/2021.
//

#include "simple_stats.h"

#include "data_aspects.h"

#include "numeric" //accumulate

double wilcoxon (const std::vector<double> &x1,
                 const std::vector<double> &x2){
    unsigned n1 = x1.size();
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    std::vector<double> transformed_pooled_sample = c_aspect(pooled_sample);
    double obs_stat = std::accumulate(transformed_pooled_sample.begin() , transformed_pooled_sample.begin() + n1 , 0.0)-
                      std::accumulate(transformed_pooled_sample.begin() + n1 , transformed_pooled_sample.end() , 0.0);
    return obs_stat;
}
