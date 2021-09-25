//
// Created by filip on 24/09/2021.
//

#include "distribution_dispatching.h"
#include <map>

std::map<std::string, generator> mymap = {{"norm",           normal_generator<dqrng::xoroshiro128plus>(0.0, 1.0)},
                                          {"normalized_exp", normalized_exponential_generator<dqrng::xoroshiro128plus>()}
};

generator dispatch_generator_from_string(const std::string &s) {
    return mymap[s];
}
