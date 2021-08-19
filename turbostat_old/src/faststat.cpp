//
// Created by filip on 13/08/2021.
//

#include "faststat.h"
#include "utils.h"
#include <random>


double sum_of_ranks (const vector<double> &sample){
    vector<double> ranks = ranks_with_mean_strategy_for_tides(sample);
    return accumulate(ranks.begin(), ranks.end(), 0.0);
}

double T_a (const vector<double> &pooled_sample, unsigned n1){
    return accumulate(pooled_sample.begin() + n1 , pooled_sample.end(), 0.0);
}

double T_c (const vector<double> &pooled_sample, unsigned n1){
    vector<double> ranks = ranks_with_mean_strategy_for_tides(pooled_sample);
    return accumulate(ranks.begin() + n1 , ranks.end(), 0.0);
}

pair<double, double> single_aspect (const vector<double> &x1, const vector<double> &x2, unsigned B, double (*stat)(const vector<double> &, unsigned)){
    vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    double obs_stat = stat(pooled_sample, x1.size());
    random_device rd;
    std::mt19937 generator(rd());
    vector<double> permutations_stats(B);
    for (int i = 0; i < B ; ++i) {
        std::shuffle(pooled_sample.begin(), pooled_sample.end(), generator );
        double perm_stat = stat(pooled_sample, x1.size());
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

pair<double, double> test_A (const vector<double> &x1, const vector<double> &x2, unsigned B){
    return single_aspect (x1, x2, B, T_a);
}

pair<double, double> test_C (const vector<double> &x1, const vector<double> &x2, unsigned B){
    return single_aspect (x1, x2, B, T_c);
}

/*pair<double, double> T_a (const vector<double> &x1, const vector<double> &x2, unsigned B){
    double obs_stat = accumulate(x2.begin(), x2.end(), 0.0);
    vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());
    random_device rd;
    std::mt19937 generator(rd());
    vector<double> permutations_stats(B);
    for (int i = 0; i < B ; ++i) {
        std::shuffle(pooled_sample.begin(), pooled_sample.end(), generator );
        double perm_stat = accumulate(pooled_sample.begin() + x1.size() , pooled_sample.end(), 0.0);
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
}*/



