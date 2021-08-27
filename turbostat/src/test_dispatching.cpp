//
// Created by filip on 27/08/2021.
//

#include "test_dispatching.h"
#include "single_aspect.h"
#include "turbotabc.h"

std::map<std::string, test_fun_ptr> m = {{"a", t_a_permtest},
                                         {"b", t_b_permtest},
                                         {"c", t_c_permtest},
                                         {"abc", t_abc_permtest}};

test_fun_ptr dispatch_from_string(const std::string &s){
    return m[s];
}
