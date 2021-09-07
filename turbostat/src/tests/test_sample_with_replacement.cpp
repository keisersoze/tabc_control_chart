//
// Created by filip on 07/09/2021.
//

#include "../utils.h"

#include <vector>
#include <iostream>


int main() {
    std::vector<double> x2 = {1, 2, 3, 7};
    std::mt19937 g(32);
    std::vector<double> res = sample_with_replacement(x2, 2, g);
    for (auto elem: res){
        std::cout << elem << ' ';
    }

}
