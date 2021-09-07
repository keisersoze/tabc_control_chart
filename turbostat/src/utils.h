//
// Created by filip on 22/08/2021.
//

#ifndef RACE_UTILS_H
#define RACE_UTILS_H

#include <Rcpp.h>

#include <xoshiro.h>


std::vector<double> avg_rank(const std::vector<double> &v);

double median (std::vector<double> len);

template <class T>
std::vector<T> sample_with_replacement(const std::vector<T> &v, unsigned sample_size, dqrng::xoroshiro128plus &rng){
    std::uniform_int_distribution<> dist(0, v.size()-1);
    std::vector<T> res (sample_size);
    for (unsigned i = 0; i < sample_size; ++i) {
        unsigned rn = dist(rng);
        res[i] = v[rn];
    }
    return res;
}


#endif //RACE_UTILS_H
