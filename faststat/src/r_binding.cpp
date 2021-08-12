//
// Created by Filippo Maganza on 05/11/2020.
//

#include <string>
#include <vector>
#include <iostream>

#include <Rcpp.h>

#include "cucconi_multisample_test.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
std::string hello() {
    return "Hello world";
}

// [[Rcpp::export]]
double bigSum(List x) {
    double sum = 0;
    int i = 0;
    for (int j = 0; j < x.size(); j++) {
        NumericVector v = as<NumericVector>(x[j]);
        for (int k = 0; k < v.size(); ++k) {
            sum = sum + v[k];
        }
    }
    return sum;
}

// [[Rcpp::export]]
NumericVector multisampleCucconiTest(List samples, int B) {
    vector<vector<double>> samples_c(0);
    for (int i = 0; i < samples.size(); ++i) {
        NumericVector sample = as<NumericVector>(samples[i]);
        vector<double> sample_c(sample.size());
        for (int j = 0; j < sample.size(); ++j) {
            sample_c[j] = sample[j];
        }
        samples_c.push_back(sample_c);
    }
    pair<double, double> pair = multisample_cucconi_test(samples_c, B);
    return NumericVector::create(pair.second ,pair.first);
}


