//
// Created by filip on 13/08/2021.
//

#ifndef RACE_FASTSTAT_H
#define RACE_FASTSTAT_H

#include <vector>

double sum_of_ranks (const std::vector<double> &sample);

std::pair<double, double> test_A (const std::vector<double> &x1, const std::vector<double> &x2, unsigned B);

std::pair<double, double> test_C (const std::vector<double> &x1, const std::vector<double> &x2, unsigned B);

/*vector<double> uncoditional_RL (unsigned n,
                                unsigned m,
                                const vector<double> &shift_seq,
                                unsigned nsim,
                                double LCL,
                                double UCL)*/

#endif //RACE_FASTSTAT_H
