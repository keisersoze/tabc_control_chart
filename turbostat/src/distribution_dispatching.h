//
// Created by filip on 12/09/2021.
//

#ifndef RACE_DISTRRIBUTION_DISPATCHING_H
#define RACE_DISTRRIBUTION_DISPATCHING_H

#include <boost/random/normal_distribution.hpp>
#include <boost/random/cauchy_distribution.hpp>
#include <boost/random/laplace_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>
#include <boost/random/student_t_distribution.hpp>

#include <xoshiro.h>

#include <stdexcept>
#include <cmath>        // std::abs
#include <vector>

typedef std::function<void (dqrng::xoroshiro128plus &, std::vector<double> &)> generator;

template<class Engine>
class normal_generator{
private:
    boost::random::normal_distribution<double> dist_boost;
public:
    normal_generator(double mean, double sd): dist_boost(mean, sd){}

    void operator () (Engine &rng, std::vector<double> &v) {
        std::generate(v.begin(), v.end(), [this, &rng]() { return dist_boost(rng);});
    }
};

template<class Engine>
class normalized_exponential_generator{
private:
    boost::random::exponential_distribution<double> dist_boost;
public:
    normalized_exponential_generator(): dist_boost(1.0){}

    void operator () (Engine &rng, std::vector<double> &v) {
        std::generate(v.begin(), v.end(), [this, &rng]() { return dist_boost(rng) - 1.0;});
    }
};

generator dispatch_generator_from_string(const std::string &s);


//template<class Engine>
//class normal_generator{
//private:
//    boost::random::normal_distribution<double> dist_boost;
//    Engine &rng;
//public:
//    normal_generator(double mean, double sd, Engine &rng) : dist_boost(mean, sd), rng(rng){}
//
//    void operator () (std::vector<double> &v) const {
//        return std::generate(v.begin(), v.end(), [&dist_boost, &rng]() { return dist_boost(rng);});
//    }
//};
//
//template<class Engine>
//class normalized_exponential_generator{
//private:
//    boost::random::exponential_distribution<double> dist_boost;
//    Engine &rng;
//public:
//    normalized_exponential_generator(Engine &rng) : dist_boost(1.0), rng(rng){}
//
//    void operator () (std::vector<double> &v) const {
//        return std::generate(v.begin(), v.end(), [&dist_boost, &rng]() { return dist_boost(rng) - 1.0;});
//    }
//};
//
//typedef std::function<void (std::vector<double>&)> generator;
//
//generator standard_normal_generator_builder(dqrng::xoroshiro128plus &rng){
//    return normal_generator(0.0, 1.0, rng);
//}
//
//generator normalized_exponential_generator_builder(dqrng::xoroshiro128plus &rng){
//    return normalized_exponential_generator(rng);
//}
//
//typedef generator (*generator_builder)(dqrng::xoroshiro128plus &);
//
//std::map<std::string, generator_builder> m = {{"norm", standard_normal_generator_builder},
//                                              {"normalized_exp", normalized_exponential_generator_builder}
//};



//template<class Engine>
//std::function<double (Engine&)> dispatch_norm(double location_shift){
//    return  boost::random::normal_distribution<double> (location_shift, 1.0);
//}
//
//template<class Engine>
//std::function<double (Engine&)> dispatch_cauchy(double location_shift){
//    return  boost::random::cauchy_distribution<double> (location_shift, 1.0);
//}
//
//template<class Engine>
//std::function<double (Engine&)> dispatch_laplace(double location_shift){
//    return  boost::random::laplace_distribution<double> (location_shift, 1.0);
//}
//
//template<class Engine>
//std::function<double (Engine&)> dispatch_t(double location_shift, unsigned n_degrees){
//    return  boost::random::student_t_distribution<double> (n_degrees, 1.0);
//}

//template<class Engine>
//std::function<double (Engine&)> dispatch_exponential(double location_shift){
//    boost::random::exponential_distribution<double> exp_dist(1.0);
//    return [location_shift](Engine& rng) {
//        return exp_dist(rng) - 1.0 + location_shift;
//    };
//}

//template<class Engine>
//std::function<double (Engine&)> dispatch_half_cauchy(const std::vector<double> &params,
//                                                     double location_shift){
//    double scale = params[0];
//    boost::random::cauchy_distribution<double> cauchy_distribution(0.0 + location_shift, scale);
//    return [location, scale, cauchy_distribution](Engine& rng) { return std::abs(cauchy_distribution(rng)); };
//}

//template<class Engine>
//std::function<double (Engine&)> dispatch_sampling_function(const std::string &dist,
//                                                           const std::vector<double> &params,
//                                                           double location_shift){
//    //TODO this is ugly
//    if (dist == "norm"){
//        return dispatch_norm<Engine>(location_shift);
//    } else if (dist == "cauchy"){
//        return dispatch_cauchy<Engine>(location_shift);
//    } else if (dist == "laplace"){
//        return dispatch_laplace<Engine>(location_shift);
//    } else {
//        throw std::invalid_argument( "Invalid argument" );
//    }
//}


#endif //RACE_DISTRRIBUTION_DISPATCHING_H
