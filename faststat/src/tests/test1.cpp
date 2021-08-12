//
// Created by Filippo Maganza on 06/11/2020.
//

#include <iostream>
#include <vector>
#include <chrono>
#include "../cucconi_multisample_test.h"


int main() {

    vector<double> x1 = {495, 477, 425, 322, 482, 587, 370, 322, 479, 375, 330, 300, 386, 401, 645, 440, 317, 319, 298,
                         253};
    vector<double> x2 = {458, 506, 473, 545, 496, 360, 387, 386, 507, 393, 405, 372, 144, 511, 405, 428, 339};
    vector<double> x3 = {430, 375, 396, 383, 387, 542, 359, 357, 528, 513, 426, 513, 358, 581, 588, 522, 545};
    vector<vector<double>> groups = {x1, x2, x3};
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    pair<double,double> pair = multisample_cucconi_test(groups, 100000);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[milliseconds]" << std::endl;
    std::cout << "P-value:"<< pair.first << " Observed MC stat:" << pair.second << std::endl;
    return 0;
}
