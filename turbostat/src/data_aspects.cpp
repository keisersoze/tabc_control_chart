//
// Created by filip on 03/09/2021.
//

#include <algorithm>    // std::count_if

#include "data_aspects.h"
#include "../utils.h"

std::vector<double> a_aspect(const std::vector<double> &pooled_sample){
    return pooled_sample;
}

std::vector<double> b_aspect(const std::vector<double> &pooled_sample){
    double median = median(pooled_sample);
    return std::count_if(pooled_sample.begin(), pooled_sample.end(), [](int x){return x >= median;});
}

std::vector<double> c_aspect(const std::vector<double> &pooled_sample){
    return avg_rank(pooled_sample);
}
