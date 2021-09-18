//
// Created by filip on 07/09/2021.
//

#include "../multiple_aspects.h"

#include <iostream>


int main() {

    std::vector<double> x1 = {495, 477, 425};
    std::vector<double> x2 = {458, 506, 473};
    std::mt19937 gen32(32);
    perm_test_result res = t_abc(x1, x2, 10, gen32);
    std::cout << "P-value:"<< res.p_value << std::endl;
    return 0;

}
