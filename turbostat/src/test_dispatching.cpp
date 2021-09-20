//
// Created by filip on 27/08/2021.
//

#include "test_dispatching.h"
#include "single_aspect.h"
#include "multiple_aspects.h"

#include <map>

std::map<std::string, test_fun_ptr> m = {{"a",   t_a_permtest<dqrng::xoroshiro128plus>},
                                         {"b",   t_b_permtest<dqrng::xoroshiro128plus>},
                                         {"c",   t_c_permtest<dqrng::xoroshiro128plus>},
                                         {"abc", t_abc<dqrng::xoroshiro128plus>},
                                         {"ab", t_ab<dqrng::xoroshiro128plus>},
                                         {"ac", t_ac<dqrng::xoroshiro128plus>},
                                         {"bc", t_bc<dqrng::xoroshiro128plus>}
};

test_fun_ptr dispatch_from_string(const std::string &s) {
    return m[s];
}
