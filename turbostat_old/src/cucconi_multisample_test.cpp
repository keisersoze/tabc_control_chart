//
// Created by Filippo Maganza on 06/11/2020.
//

#include <cmath>
#include <numeric>
#include <random>
#include "cucconi_multisample_test.h"
#include "utils.h"
#include <omp.h>


double multisample_cucconi_statistic(
        vector<double> const &pooled_ranks,
        vector<unsigned int> const &indexes_in_pooled_sample,
        double const &covariance,
        vector<double> const &means,
        vector<double> const &standard_deviations) {

    const unsigned int n = pooled_ranks.size();

    vector<vector<double>> grouped_ranks;
    for (auto it = indexes_in_pooled_sample.begin(); it != indexes_in_pooled_sample.end() - 1; ++it) {
        grouped_ranks.emplace_back(pooled_ranks.begin() + (*it), pooled_ranks.begin() + (*(it + 1)));
    }

    const unsigned int k = grouped_ranks.size();

    vector<vector<double>> grouped_contrary_ranks(grouped_ranks);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < grouped_contrary_ranks[i].size(); ++j) {
            grouped_contrary_ranks[i][j] = n + 1 - grouped_ranks[i][j];
        }
    }

    vector<vector<double>> grouped_squared_ranks(grouped_ranks);
    for (auto &group : grouped_squared_ranks) {
        for (auto &elem : group) {
            elem = std::pow(elem, 2);
        }
    }

    vector<vector<double>> grouped_squared_contrary_ranks(grouped_contrary_ranks);
    for (auto &group : grouped_squared_contrary_ranks) {
        for (auto &elem : group) {
            elem = std::pow(elem, 2);
        }
    }

    vector<double> squared_ranks_sums;
    for (auto &group : grouped_squared_ranks) {
        double sum = 0;
        for (auto &elem : group) {
            sum = sum + elem;
        }
        squared_ranks_sums.push_back(sum);
    }
    vector<double> squared_contrary_ranks_sums;
    for (auto &group : grouped_squared_contrary_ranks) {
        double sum = 0;
        for (auto &elem : group) {
            sum = sum + elem;
        }
        squared_contrary_ranks_sums.push_back(sum);
    }
    vector<double> u_stats(k);
    vector<double> v_stats(k);
    vector<double> partial_mc_stats(k);
    for (int i = 0; i < k; ++i) {
        u_stats[i] = (squared_ranks_sums[i] - means[i]) / standard_deviations[i];
        v_stats[i] = (squared_contrary_ranks_sums[i] - means[i]) / standard_deviations[i];
        partial_mc_stats[i] = (pow(u_stats[i], 2) + pow(v_stats[i], 2) - 2 * u_stats[i] * v_stats[i] * covariance) / 2 /
                              (1 - pow(covariance, 2));
    }
    double sum = accumulate(partial_mc_stats.begin(), partial_mc_stats.end(), 0.0);
    return sum / k;
}

pair<double, double> multisample_cucconi_test(vector<vector<double>> samples, int B) {
    const unsigned k = samples.size();

    vector<unsigned int> indexes_in_pooled_sample(samples.size() + 1);
    indexes_in_pooled_sample[0] = 0;
    for (int i = 1; i < samples.size() + 1; ++i) {
        indexes_in_pooled_sample[i] = indexes_in_pooled_sample[i - 1] + samples[i - 1].size();
    }
    vector<double> pooled_sample(samples.front());
    for (auto it = samples.begin() + 1; it != samples.end(); ++it) {
        pooled_sample.insert(pooled_sample.end(), it->begin(), it->end());
    }

    const unsigned n = pooled_sample.size();

    double covariance = (double) -(30 * n + 14 * pow(n, 2) + 19) / (8 * n + 11) / (2 * n + 1);
    // the mean of the sum of the squared ranks of a group k depends only on the group size and the size of the pooled sample
    vector<double> means(B);
    vector<double> standard_deviations(B);
    for (int i = 0; i < k; ++i) {
        const int n_k = samples[i].size();
        means[i] = (double) n_k * (n + 1) * (2 * n + 1) / 6;
        standard_deviations[i] = sqrt(n_k * (n - n_k) * (n + 1) * (2 * n + 1) * (8 * n + 11) / 180);
    }

    vector<double> pooled_ranks = ranks_with_mean_strategy_for_tides(pooled_sample);

    double observed_mc_stat = multisample_cucconi_statistic(pooled_ranks,
                                                            indexes_in_pooled_sample,
                                                            covariance,
                                                            means,
                                                            standard_deviations);

    vector<double> permutations_stats(B);
    int n_threads = omp_get_max_threads();
    vector<std::mt19937> generators(B);
    std::random_device rd;
    for (int i = 0; i < n_threads; ++i) {
        std::mt19937 generator(rd());
        generators[i] = generator;
    }
    #pragma omp parallel for default(none) shared(pooled_ranks, generators, permutations_stats, indexes_in_pooled_sample, covariance, means, standard_deviations,B)
    for (int i = 0; i < B ; ++i) {
        int tid = omp_get_thread_num();
        vector<double> permutated_pooled_ranks(pooled_ranks);
        std::shuffle(permutated_pooled_ranks.begin(), permutated_pooled_ranks.end(), generators[tid] );
        permutations_stats[i] = multisample_cucconi_statistic(permutated_pooled_ranks,
                                                              indexes_in_pooled_sample,
                                                              covariance,
                                                              means,
                                                              standard_deviations);
    }
    int acc = 0;
    for (auto permutation_stat : permutations_stats) {
        if (permutation_stat >= observed_mc_stat) {
            acc++;
        }
    }
    double p_value = ((double) acc) / ((double) B);
    pair<double, double> pair(p_value, observed_mc_stat);
    return pair;
}


