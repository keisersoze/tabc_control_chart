//
// Created by filip on 13/08/2021.
//

#ifndef RACE_FASTSTAT_H
#define RACE_FASTSTAT_H

#include <vector>

using namespace std;

double sum_of_ranks (const vector<double> &sample);

pair<double, double> test_A (const vector<double> &x1, const vector<double> &x2, unsigned B);

pair<double, double> test_C (const vector<double> &x1, const vector<double> &x2, unsigned B);

#endif //RACE_FASTSTAT_H
