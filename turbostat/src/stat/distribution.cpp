//
// Created by filip on 24/09/2021.
//

#include "distribution.h"

normalized_rate_one_exponential::normalized_rate_one_exponential(): exp_boost(1.0){}

normalized_t_with_two_pont_five_degrees::normalized_t_with_two_pont_five_degrees(): t_dist_boost(2.5){}

standard_half_cauchy::standard_half_cauchy(): cauchy_boost(0,1){}

centered_gamma_with_shape_equal_four::centered_gamma_with_shape_equal_four(): gamma_boost(4.0, 0.5){}

mirrored_centered_gamma_with_shape_equal_four::mirrored_centered_gamma_with_shape_equal_four(): gamma_boost(4.0, 0.5){}
