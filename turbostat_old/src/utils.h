//
// Created by Filippo Maganza on 05/11/2020.
//

#ifndef RACE_UTILS_H
#define RACE_UTILS_H

#include <iostream>
#include <vector>
#include <numeric>      // std::iota
#include <algorithm>    // std::sort, std::stable_sort
#include <vector>

using namespace std;

/**
 * Returns ranks of elements in v using mean strategy for tides. Runs in nlogn + n = O(nlogn) where n is the size of v.
 * @tparam T
 * @param v
 * @return
 */
template<typename T>
vector<double> ranks_with_mean_strategy_for_tides(const vector<T> &v) {
    // initialize original index locations
    vector<pair<unsigned, T>> idx_value_pairs(v.size());
    for (int i = 0; i < v.size(); ++i) {
        idx_value_pairs[i].first = i;
        idx_value_pairs[i].second = v[i];
    }

    sort(idx_value_pairs.begin(), idx_value_pairs.end(),
                [&v](pair<unsigned, T> p1, pair<unsigned, T> p2) { return p1.second < p2.second; });
    vector<double> ranks(v.size());
    int tide_start;
    int tide_length = 0;
    for (int i = 0; i < v.size(); ++i) {
        if (i < v.size() - 1 and idx_value_pairs[i].second == idx_value_pairs[i + 1].second) {
            if (tide_length == 0) {
                tide_start = i;
            }
            tide_length++;
        } else {
            if (tide_length > 0) {
                for (int j = tide_start; j < tide_start + tide_length + 1; ++j) {
                    ranks[idx_value_pairs[j].first] = ((double) 2 * tide_start + tide_length + 2) / 2;
                }
                tide_length = 0;
            } else{
                ranks[idx_value_pairs[i].first] = i + 1;
            }
        }
    }
    return ranks;
}

//TODO improve it
template<typename T>
vector<double> ranks_2(const vector<T> &v) {
    vector<T> sorted_vector(v);
    stable_sort(sorted_vector.begin(), sorted_vector.end());
    vector<double> ranks(v.size());
    for (int i = 0; i < v.size(); ++i) {
        int num_matches = 0;
        bool is_first_match = true;
        int index_of_fist_match;
        for (int j = 0; j < v.size(); ++j) {
            if (sorted_vector[j] == v[i]) {
                num_matches++;
                if (is_first_match) {
                    index_of_fist_match = j;
                    is_first_match = false;
                }
            }
        }
        if (num_matches < 2) {
            ranks[i] = (double) index_of_fist_match + 1;
        } else {
            ranks[i] = ((double) 2 * index_of_fist_match + 1 + num_matches) / 2;
        }
    }
    return ranks;
}

#endif //RACE_UTILS_H
