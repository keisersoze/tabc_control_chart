//
// Created by filip on 12/09/2021.
//

#ifndef RACE_DISTRRIBUTION_DISPATCHING_H
#define RACE_DISTRRIBUTION_DISPATCHING_H

#include <boost/random/normal_distribution.hpp>
#include <boost/random/cauchy_distribution.hpp>

#include <stdexcept>

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
std::function<double (Engine&)> dispatch_sampling_function(const std::string &dist,
                                                           const std::vector<double> &params,
                                                           double location_shift){
    if (dist == "norm"){
        return dispatch_norm<Engine>(params, location_shift);
    } else if (dist == "cauchy"){
        return dispatch_norm<Engine>(params, location_shift);
    } else {
        throw std::invalid_argument( "Invalid argument" );
    }
}


#endif //RACE_DISTRRIBUTION_DISPATCHING_H
