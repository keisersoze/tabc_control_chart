//
// Created by filip on 24/09/2021.
//

#include "distribution_dispatching.h"
#include <map>

normalized_rate_one_exponential::normalized_rate_one_exponential(): exp_boost(1.0){};

std::map<std::string, distribution> mymap = {{"norm", boost::random::normal_distribution<double>(0.0, 1.0)},
                                             {"normalized_rate_one_exponential", normalized_rate_one_exponential()}};

distribution dispatch_generator_from_string(const std::string &s) {
    return mymap[s];
}
