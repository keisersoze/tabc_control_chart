//
// Created by filip on 19/08/2021.
//

#ifndef RACE_SHARED_H
#define RACE_SHARED_H

#include <random>
#include <vector>
#include <algorithm>

pair<double, double> single_aspect_with_permutations (const vector<double> &x1,
                                                      const vector<double> &x2,
                                                      unsigned B,
                                                      const IStat &t,
                                                      unsigned seed){
    vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    double obs_stat = t.compute_stat(pooled_sample, x1.size());
//    Does not work in with MinGW compiler...
//    random_device rd;
//    unsigned seed = rd();

    std::mt19937 generator(seed);
    vector<double> permutations_stats(B);
    for (int i = 0; i < B ; ++i) {
        shuffle(pooled_sample.begin(), pooled_sample.end(), generator );
        double perm_stat = t.compute_stat(pooled_sample, x1.size());
        permutations_stats[i] = perm_stat;
    }
    int acc = 0;
    for (auto permutation_stat : permutations_stats) {
        if (permutation_stat < obs_stat) {
            acc++;
        }
    }
    double p_value = ((double) acc) / ((double) B);
    pair<double, double> pair(p_value, obs_stat);
    return pair;
}

#endif //RACE_SHARED_H
