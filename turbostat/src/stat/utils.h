//
// Created by filip on 22/08/2021.
//

#ifndef RACE_UTILS_H
#define RACE_UTILS_H

#include <vector>
#include <random>
#include <algorithm>

std::vector<double> avg_rank(const std::vector<double> &v);

double median(std::vector<double> len);

double mean(std::vector<double> x);

template<class T, class RNG>
std::vector<T> sample_with_replacement(const std::vector<T> &v, unsigned sample_size, RNG &rng) {
    std::uniform_int_distribution<> dist(0, v.size() - 1);
    std::vector<T> res(sample_size);
    for (unsigned i = 0; i < sample_size; ++i) {
        unsigned rn = dist(rng);
        res[i] = v[rn];
    }
    return res;
}

// https://stackoverflow.com/questions/17074324/how-can-i-sort-two-vectors-in-the-same-way-with-criteria-that-uses-only-one-of
template<typename T>
std::vector<unsigned> sort_permutation(const std::vector<T> &vec, bool desc = false) {
    std::vector<unsigned> p(vec.size());
    std::iota(p.begin(), p.end(), 0);
    if (desc) {
        std::sort(p.begin(), p.end(),
                  [&](unsigned i, unsigned j) { return vec[i] > vec[j]; });
    } else {
        std::sort(p.begin(), p.end(),
                  [&](unsigned i, unsigned j) { return vec[i] < vec[j]; });
    }
    return p;
}

template<typename T>
std::vector<T> apply_permutation(const std::vector<T> &vec, const std::vector<unsigned> &p) {
    std::vector<T> sorted_vec(vec.size());
    std::transform(p.begin(), p.end(), sorted_vec.begin(),
                   [&](unsigned i) { return vec[i]; });
    return sorted_vec;
}

template<typename T>
void apply_permutation_in_place(
        std::vector<T> &vec,
        const std::vector<unsigned> &p) {
    std::vector<bool> done(vec.size());
    for (unsigned i = 0; i < vec.size(); ++i) {
        if (done[i]) {
            continue;
        }
        done[i] = true;
        unsigned prev_j = i;
        unsigned j = p[i];
        while (i != j) {
            std::swap(vec[prev_j], vec[j]);
            done[j] = true;
            prev_j = j;
            j = p[j];
        }
    }
}


#endif //RACE_UTILS_H
