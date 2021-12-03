//
// Created by filip on 03/12/2021.
//

#include <xoshiro.h>
#include <convert_seed.h>

#include "rng/global_rng.h"

#include <Rcpp.h>

//' Set the seed used by this R packet
//'
//' @param s The seed. Either an integer scalar or an integer vector of length 2 representing a 64-bit seed.
//' @export
// [[Rcpp::export(turbostat.setseed)]]
void set_seed(Rcpp::IntegerVector seed) {
    uint64_t _s = dqrng::convert_seed<uint64_t>(seed);
    global_rng::instance.seed(_s);
}

