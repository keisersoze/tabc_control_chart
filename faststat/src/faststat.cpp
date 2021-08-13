//
// Created by filip on 13/08/2021.
//

#include "faststat.h"
#include "utils.h"

double sum_of_ranks (const vector<double> &sample){
    vector<double> ranks = ranks_with_mean_strategy_for_tides(sample);
    return accumulate(ranks.begin(), ranks.end(), 0.0);
}

