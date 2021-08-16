//
// Created by Filippo Maganza on 05/11/2020.
//

#include <string>
#include <vector>
#include <iostream>

#include <Rcpp.h>

#include "cucconi_multisample_test.h"
#include "faststat.h"


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

// [[Rcpp::export]]
double sumOfRanks(NumericVector sample_R) {
    vector<double> sample_c(sample_R.size());
    for (int j = 0; j < sample_R.size(); ++j) {
        sample_c[j] = sample_R[j];
    }
    return sum_of_ranks(sample_c);
}

// [[Rcpp::export]]
NumericVector testA(NumericVector x1, NumericVector x2, int B) {
    vector<double> x1_c(x1.size());
    for (int j = 0; j < x1.size(); ++j) {
        x1_c[j] = x1[j];
    }
    vector<double> x2_c(x2.size());
    for (int j = 0; j < x2.size(); ++j) {
        x2_c[j] = x2[j];
    }
    pair<double, double> pair = test_A(x1_c, x2_c, B);
    return NumericVector::create(pair.second ,pair.first);
}

// [[Rcpp::export]]
NumericVector testC(NumericVector x1, NumericVector x2, int B) {
    vector<double> x1_c(x1.size());
    for (int j = 0; j < x1.size(); ++j) {
        x1_c[j] = x1[j];
    }
    vector<double> x2_c(x2.size());
    for (int j = 0; j < x2.size(); ++j) {
        x2_c[j] = x2[j];
    }
    pair<double, double> pair = test_C(x1_c, x2_c, B);
    return NumericVector::create(pair.second ,pair.first);
}


