//
// Created by filip on 19/08/2021.
//

#include <iostream>
#include <vector>
#include <chrono>

#include "../stat/Ta.h"
int main() {

    vector<double> x1 = {495, 477, 425};
    vector<double> x2 = {458, 506, 473};
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    Ta ta (1000, 43);
    double obs_value1= ta.compute_stat(x1, x2);
    pair<double,double> pair = ta.compute_test(x1, x2);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[milliseconds]" << std::endl;
    std::cout << "P-value:"<< pair.first << " Observed MC compute_stat:" << pair.second<< " Observed MC compute_stat 2:" << obs_value1 << std::endl;
    return 0;
}
