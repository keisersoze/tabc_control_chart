//
// Created by filip on 19/08/2021.
//

#include <numeric>
#include "Ta.h"
#include "shared.h"

Ta::Ta(unsigned B, unsigned seed) {
    this->B = B;
    this->seed = seed;
}

double Ta::stat_iter(vector<double>::const_iterator start, vector<double>::const_iterator end) {
    return accumulate(start , end, 0.0);
}

double Ta::compute_stat(const vector<double> &pooled_sample, unsigned n1) const{
    return accumulate(pooled_sample.begin() + n1 , pooled_sample.end(), 0.0);
}

pair<double, double> Ta::compute_test(const vector<double> &x1, const vector<double> &x2) const {
    return single_aspect_with_permutations(x1,x2,this->B, *this, this->seed);
}

double Ta::compute_stat(const vector<double> &x1, const vector<double> &x2) const{
    return accumulate(x2.begin() , x2.end(), 0.0);
}
