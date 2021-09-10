//
// Created by filip on 03/09/2021.
//

#include <algorithm>    // std::transform

#include "data_aspects.h"
#include "utils.h"

std::vector<double> a_aspect(const std::vector<double> &pooled_sample){
    return pooled_sample;
}

std::vector<double> b_aspect(const std::vector<double> &pooled_sample){
    double m = median(pooled_sample);
    std::vector<double> res(pooled_sample.size());
    std::transform(pooled_sample.begin(),
                   pooled_sample.end(),
                   res.begin(),
                   [m] (double x) -> double { return (x >= m) ? 1.0 : 0.0; });
    return res;
}

std::vector<double> c_aspect(const std::vector<double> &pooled_sample){
    return avg_rank(pooled_sample);
}
