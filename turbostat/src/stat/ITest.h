//
// Created by filip on 19/08/2021.
//

#ifndef RACE_ITEST_H
#define RACE_ITEST_H

using namespace std;

class ITest
{
public:
    virtual ~ITest() {}
    virtual pair<double,double> compute_test(const vector<double> &x1, const vector<double> &x2) const = 0;
};

#endif //RACE_ITEST_H
