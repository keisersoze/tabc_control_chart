//
// Created by filip on 19/08/2021.
//

#ifndef RACE_ISTAT_H
#define RACE_ISTAT_H

using namespace std;

class IStat
{
public:
    virtual ~IStat() {}
    virtual double compute_stat(const vector<double> &pooled_sample, unsigned n1) const = 0;
    virtual double compute_stat(const vector<double> &x1, const vector<double> &x2) const = 0;
};

#endif //RACE_ISTAT_H
