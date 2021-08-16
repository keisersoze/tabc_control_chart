//
// Created by filip on 16/08/2021.
//

#include <iostream>
#include <vector>
#include <chrono>

#include "../faststat.h"

int main() {

    vector<double> x1 = {495, 477, 425};
    vector<double> x2 = {458, 506, 473};
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    pair<double,double> pair = test_A(x1, x2, 1000);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[milliseconds]" << std::endl;
    std::cout << "P-value:"<< pair.first << " Observed MC stat:" << pair.second << std::endl;
    return 0;
}
