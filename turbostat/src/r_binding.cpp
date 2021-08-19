//
// Created by Filippo Maganza on 05/11/2020.
//

#include <string>
#include <vector>
#include <iostream>

#include <Rcpp.h>

#include "faststat.h"
#include "stat/Ta.h"
#include "TestClass.h"


using namespace Rcpp;

std::string hello() {
    return "Hello world";
}

// [[Rcpp::export]]
NumericVector testA(NumericVector x1, NumericVector x2, int B) {
    std::vector<double> x1_c(x1.size());
    for (int j = 0; j < x1.size(); ++j) {
        x1_c[j] = x1[j];
    }
    std::vector<double> x2_c(x2.size());
    for (int j = 0; j < x2.size(); ++j) {
        x2_c[j] = x2[j];
    }
    std::pair<double, double> pair = test_A(x1_c, x2_c, B);
    return NumericVector::create(pair.second ,pair.first);
}

// [[Rcpp::export]]
NumericVector testC(NumericVector x1, NumericVector x2, int B) {
    std::vector<double> x1_c(x1.size());
    for (int j = 0; j < x1.size(); ++j) {
        x1_c[j] = x1[j];
    }
    std::vector<double> x2_c(x2.size());
    for (int j = 0; j < x2.size(); ++j) {
        x2_c[j] = x2[j];
    }
    std::pair<double, double> pair = test_C(x1_c, x2_c, B);
    return NumericVector::create(pair.second ,pair.first);
}

RCPP_MODULE(test_module) {
        class_<TestClass>( "TestClass" )
                .constructor<int>()
                .method( "returnA", &TestClass::returnA )
        ;
}

/*
RCPP_MODULE(hello) {
        function("hello" , &hello);
}
*/


