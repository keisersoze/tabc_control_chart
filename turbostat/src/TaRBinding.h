//
// Created by filip on 20/08/2021.
//

#ifndef RACE_TARBINDING_H
#define RACE_TARBINDING_H

#include "stat/Ta.h"

class TaRBinding {
private:
    Ta ta;
public:
    explicit TaRBinding(unsigned B, unsigned seed);
    double stat(const std::vector<double>& x1, const std::vector<double>& x2) const;
};


#endif //RACE_TARBINDING_H
