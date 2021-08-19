//
// Created by filip on 19/08/2021.
//

#ifndef RACE_TA_H
#define RACE_TA_H

#include <vector>
#include "ITest.h"
#include "IStat.h"

using namespace std;

class Ta : public IStat, ITest{

private:
    unsigned seed;
    unsigned B;
    double stat_iter (vector<double>::const_iterator start, vector<double>::const_iterator end);
public:
    explicit Ta(unsigned B, unsigned seed);
    double compute_stat(const vector<double> &pooled_sample, unsigned n1) const override;
    pair<double,double> compute_test(const vector<double> &x1, const vector<double> &x2) const override;
    double compute_stat(const vector<double> &x1, const vector<double> &x2) const override;
};


#endif //RACE_TA_H
