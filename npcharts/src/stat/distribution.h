//
// Created by filip on 12/09/2021.
//

#ifndef RACE_DISTRRIBUTION_DISPATCHING_H
#define RACE_DISTRRIBUTION_DISPATCHING_H

#include <boost/random/exponential_distribution.hpp>
#include <boost/random/student_t_distribution.hpp>
#include <boost/random/cauchy_distribution.hpp>
#include <boost/random/gamma_distribution.hpp>

#include <xoshiro.h>

#include <stdexcept>
#include <cmath>        // std::abs
#include <vector>

typedef std::function<double (dqrng::xoshiro256plus &)> distribution;

class normalized_rate_one_exponential{
private:
    boost::random::exponential_distribution<double> exp_boost;
public:
    normalized_rate_one_exponential();
    template<class Engine>
    double operator () (Engine &rng) {
        return exp_boost(rng) - 1.0;
    }
};

class normalized_t_with_two_pont_five_degrees{
private:
    boost::random::student_t_distribution<double> t_dist_boost;
public:
    normalized_t_with_two_pont_five_degrees();
    template<class Engine>
    double operator () (Engine &rng) {
        return t_dist_boost(rng) / 2.0;
    }
};

class standard_half_cauchy{
private:
    boost::random::cauchy_distribution<double> cauchy_boost;
public:
    standard_half_cauchy();
    template<class Engine>
    double operator () (Engine &rng) {
        return std::abs(cauchy_boost(rng));
    }
};

class centered_gamma_with_shape_equal_four{
private:
    boost::random::gamma_distribution<double> gamma_boost;
public:
    centered_gamma_with_shape_equal_four();
    template<class Engine>
    double operator () (Engine &rng) {
        return gamma_boost(rng) - 2.0;
    }
};

class mirrored_centered_gamma_with_shape_equal_four{
private:
    boost::random::gamma_distribution<double> gamma_boost;
public:
    mirrored_centered_gamma_with_shape_equal_four();
    template<class Engine>
    double operator () (Engine &rng) {
        return -(gamma_boost(rng) - 2.0);
    }
};

#endif //RACE_DISTRRIBUTION_DISPATCHING_H
