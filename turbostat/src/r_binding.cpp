//
// Created by Filippo Maganza on 05/11/2020.
//

#include <string>
#include <vector>
#include <iostream>

#include <Rcpp.h>

#include "faststat.h"
#include "TestClass.h"
#include "TaRBinding.h"
#include "chart/runlength.h"


using namespace Rcpp;

std::string hello() {
    return "Hello world";
}

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

double sumcpp(const std::vector<double>& x) {
    return accumulate(x.begin() , x.end(), 0.0);
}

NumericVector rnormcpp(int i) {
    return Rcpp::rnorm(i);
}


//vector<double> toStdDoubleVector (NumericVector x){
//    std::vector<double> x_c(x.size());
//    for (int j = 0; j < x.size(); ++j) {
//        x_c[j] = x[j];
//    }
//    return x;
//}


RCPP_MODULE(test_module) {
        class_<TestClass>( "TestClass" )
                .constructor<int>()
                .method( "returnA", &TestClass::returnA )
        ;
        class_<TaRBinding>( "TaRBinding" )
                .constructor<unsigned ,unsigned >()
                .method( "stat", &TaRBinding::stat )
        ;
        Rcpp::function("hello" , &hello);
        Rcpp::function("testC", &testC);
        Rcpp::function("sumcpp", &sumcpp);
        Rcpp::function("rnormcpp", &rnormcpp);
        Rcpp::function("uncoditional_run_length", &unconditional_run_length_distribution);
        Rcpp::function("testCrcpp", &testCRcpp);




}

/*
RCPP_MODULE(hello) {
        function("hello" , &hello);
}
*/


