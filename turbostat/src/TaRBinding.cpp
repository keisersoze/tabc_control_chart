//
// Created by filip on 20/08/2021.
//

#include "TaRBinding.h"
#include "stat/Ta.cpp"

TaRBinding::TaRBinding(unsigned B, unsigned seed) : ta(3,3) {}

double TaRBinding::stat(const vector<double> &x1, const vector<double> &x2) const {
    return this->ta.compute_stat(x1,x2);
}
