//
// Created by filip on 13/08/2021.
//

#include <iostream>
#include <vector>
#include <chrono>
#include "../faststat.h"


int main() {

    vector<double> x1 = {495, 477, 425, 322, 482, 587, 370, 322, 479, 375, 330, 300, 386, 401, 645, 440, 317, 319, 298,
                         253};

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    double sum = sum_of_ranks(x1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[milliseconds]" << std::endl;
    std::cout << "Result = "<< sum << std::endl;
    return 0;
}


