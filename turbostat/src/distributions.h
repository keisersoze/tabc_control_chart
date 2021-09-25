//
// Created by filip on 24/09/2021.
//

#ifndef RACE_DISTRIBUTIONS_H
#define RACE_DISTRIBUTIONS_H

#include <boost/random/normal_distribution.hpp>
#include <boost/random/cauchy_distribution.hpp>
#include <boost/random/laplace_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>
#include <boost/random/student_t_distribution.hpp>

//class rdist {
//public:
//    virtual ~rdist() {}
//    template<class Engine>
//    virtual std::vector<double> generate(Engine& rng, unsigned n) const = 0;
//};
//
//template<class Engine>
//class rnorm : public rdist<Engine> {
//private:
//    boost::random::normal_distribution<double> dist_boost;
//public:
//    rnorm (double mean, double sd): rnorm_boost(mean, sd);
//    std::vector<double> generate(Engine &rng, std::vector<double> &v) const override {
//        return std::generate(v.begin(), v.end(),
//                             [&dist_boost, &rng]() { return dist_boost(rng); });
//    }
//};


template<class Engine>
void rnorm(double mean,
           double sd,
           std::vector<double> &v,
           Engine &rng) {
    boost::random::normal_distribution<double> dist_boost(mean, sd);
    std::generate(v.begin(), v.end(),
                  [&dist_boost, &rng]() { return dist_boost(rng); });
}


#endif //RACE_DISTRIBUTIONS_H
