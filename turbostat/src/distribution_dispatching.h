//
// Created by filip on 12/09/2021.
//

#ifndef RACE_DISTRRIBUTION_DISPATCHING_H
#define RACE_DISTRRIBUTION_DISPATCHING_H

#include <boost/random/normal_distribution.hpp>
#include <boost/random/cauchy_distribution.hpp>
#include <boost/random/laplace_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>

#include <stdexcept>
#include <cmath>        // std::abs


template<class Engine>
std::function<double (Engine&)> dispatch_norm(const std::vector<double> &params,
                                              double location_shift){
    double mean = params[0];
    double sd = params[1];
    return  boost::random::normal_distribution<double> (mean + location_shift, sd);
}

template<class Engine>
std::function<double (Engine&)> dispatch_cauchy(const std::vector<double> &params,
                                                double location_shift){
    double location = params[0];
    double scale = params[1];
    return  boost::random::cauchy_distribution<double> (location + location_shift, scale);
}

template<class Engine>
std::function<double (Engine&)> dispatch_laplace(const std::vector<double> &params,
                                                 double location_shift){
    double location = params[0];
    double scale = params[1];
    return  boost::random::laplace_distribution<double> (location + location_shift, scale);
}

template<class Engine>
std::function<double (Engine&)> dispatch_exponential(const std::vector<double> &params,
                                                     double location_shift){
    double old_rate = params[0];
    double old_mean = 1.0/old_rate;
    double new_mean = old_mean + location_shift;
    double new_rate = 1.0/new_mean;
    return boost::random::exponential_distribution<double> (new_rate);
}

//template<class Engine>
//std::function<double (Engine&)> dispatch_half_cauchy(const std::vector<double> &params,
//                                                     double location_shift){
//    double scale = params[0];
//    boost::random::cauchy_distribution<double> cauchy_distribution(0.0 + location_shift, scale);
//    return [location, scale, cauchy_distribution](Engine& rng) { return std::abs(cauchy_distribution(rng)); };
//}

template<class Engine>
std::function<double (Engine&)> dispatch_sampling_function(const std::string &dist,
                                                           const std::vector<double> &params,
                                                           double location_shift){
    if (dist == "norm"){
        return dispatch_norm<Engine>(params, location_shift);
    } else if (dist == "cauchy"){
        return dispatch_cauchy<Engine>(params, location_shift);
    } else if (dist == "laplace"){
        return dispatch_laplace<Engine>(params, location_shift);
    } else {
        throw std::invalid_argument( "Invalid argument" );
    }
}


#endif //RACE_DISTRRIBUTION_DISPATCHING_H
