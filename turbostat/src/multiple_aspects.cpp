//
// Created by filip on 28/09/2021.
//

#include "multiple_aspects.h"

phase_1_result::phase_1_result(const std::vector<std::vector<double>> &aspects_perm_stats,
                               unsigned tabc_obs)
                               : aspects_perm_stats(aspects_perm_stats), tabc_obs(tabc_obs) {}
