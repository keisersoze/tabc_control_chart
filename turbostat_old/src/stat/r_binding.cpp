//
// Created by filip on 19/08/2021.
//

#include "Ta.h"
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

RCPP_MODULE(test_module) {
        class_<Ta>( "Ta" )
                .constructor<unsigned ,unsigned >()
                .method( "stat", &Ta::compute_stat )
                .method( "test", &Ta::compute_test )
        ;
}

