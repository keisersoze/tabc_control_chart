//
// Created by filip on 08/09/2021.
//

#ifndef RACE_RNG_H
#define RACE_RNG_H

#include <xoshiro.h>

namespace global_rng {
    extern dqrng::xoroshiro128plus instance;
}

#endif //RACE_RNG_H
