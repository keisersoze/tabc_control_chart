//
// Created by Filippo Maganza on 12/11/2020.
//

#include <iostream>
#include <vector>
#include "../utils.h"


int main() {
    std::cout << "Hello, World!" << std::endl;
    std::vector<int> v1;
    v1.push_back(4);
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(3);
    v1.push_back(5);
    std::vector<double> out = ranks_with_mean_strategy_for_tides(v1);
    for (unsigned const i : v1)
        std::cout << i << ' ';
    std::cout << "\n";
    for (auto &i : out)
        std::cout << i << ' ';
    return 0;
}