//
// Created by filip on 22/08/2021.
//

#ifndef RACE_MULTIPLE_ASPECTS_H
#define RACE_MULTIPLE_ASPECTS_H

#include <numeric>
#include <algorithm>

# include "test_interface.h"
# include "data_aspects.h"
# include "utils.h"

struct phase_1_result {
    std::vector<std::vector<double>> aspects_perm_stats;
    unsigned min_pos;

    phase_1_result(const std::vector<std::vector<double>>  &aspects_perm_stats,
                   unsigned min_pos);
};

template<class RNG>
phase_1_result multiple_aspect_phase_1(const std::vector<double> &x1,
                                       const std::vector<double> &x2,
                                       unsigned n_perm,
                                       RNG &rng,
                                       const std::vector<aspect_ptr> &aspects){
    unsigned n1 = x1.size();
    unsigned n2 = x2.size();
    std::vector<double> pooled_sample(x1);
    pooled_sample.insert(pooled_sample.end(), x2.begin(), x2.end());

    std::vector<std::vector<double>> aspects_data(aspects.size());
    for (unsigned i = 0; i < aspects.size(); ++i) {
        aspects_data[i] = aspects[i](pooled_sample);
    }

    std::vector<double> aspects_obs(aspects.size());
    for (unsigned i = 0; i < aspects.size(); ++i) {
        aspects_obs[i] = std::accumulate(aspects_data[i].begin() + n1, aspects_data[i].end(), 0.0);
    }

//    Rcpp::Rcout << "Ta_obs " << ta_obs << std::endl;
//    Rcpp::Rcout << "Tb_obs " << tb_obs << std::endl;
//    Rcpp::Rcout << "Tc_obs " << tc_obs << std::endl;

    std::vector<std::vector<double> > aspects_perm_stats(
            aspects.size(),
            std::vector<double>(n_perm));

    // Rcpp::Rcout.precision(10);

    std::vector<unsigned> p(pooled_sample.size());
    std::iota(p.begin(), p.end(), 0);
    for (unsigned i = 0; i < n_perm; ++i) {
        std::shuffle(p.begin(), p.end(), rng);

//        ta_perm[i] = T_a(permuted_pooled_sample, n1);
//        tb_perm[i] = T_b(permuted_pooled_sample, n1, median);
//        tc_perm[i] = T_c(permuted_pooled_sample, n1);
        for (unsigned j = 0; j < aspects.size(); ++j) {
            double sum = 0;
            for (unsigned k = n1; k < pooled_sample.size(); ++k) {
                sum = sum + aspects_data[j][p[k]];
            }
            aspects_perm_stats[j][i] = sum;
        }

    }
//    Rcpp::Rcout << "Ta " << ta_perm << std::endl;
//    Rcpp::Rcout << "Tb " << tb_perm << std::endl;
//    Rcpp::Rcout << "Tc " << tc_perm << std::endl;

    std::vector<unsigned> positions(aspects.size());
    for (unsigned i = 0; i < aspects.size(); ++i) {
        //TODO take aspects_obs by reference
        positions[i] = std::count_if(aspects_perm_stats[i].begin(), aspects_perm_stats[i].end(),
                                     [i, &aspects_obs](double x) { return x >= aspects_obs[i]; });
    }
    unsigned min_pos = *min_element(positions.begin(), positions.end());
    return phase_1_result(aspects_perm_stats, min_pos);
}



template<class RNG>
perm_test_result multiple_aspect_phase_2(const std::vector<double> &x1,
                                         const std::vector<double> &x2,
                                         unsigned n_perm,
                                         RNG &rng,
                                         const std::vector<aspect_ptr> &aspects) {
    phase_1_result res = multiple_aspect_phase_1(x1,x2,n_perm,rng,aspects);
    std::vector<std::vector<double>> &aspects_perm_stats = res.aspects_perm_stats;
    unsigned min_pos = res.min_pos;

//    Rcpp::Rcout << "pa " << pa << std::endl;
//    Rcpp::Rcout << "pb " << pb << std::endl;
//    Rcpp::Rcout << "pc " << pc << std::endl;
//    Rcpp::Rcout << "Tabc " << tabc_obs << std::endl;

    std::vector<std::vector<unsigned >> aspects_perm_stats_order(aspects.size());
    for (unsigned i = 0; i < aspects.size(); ++i) {
        aspects_perm_stats_order[i] = sort_permutation(aspects_perm_stats[i], true);
    }

    for (unsigned i = 0; i < aspects.size(); ++i) {
        apply_permutation_in_place(aspects_perm_stats[i], aspects_perm_stats_order[i]);
    }


//    Rcpp::Rcout << "Ta " << ta_perm_sorted << std::endl;
//    Rcpp::Rcout << "Tb " << tb_perm_sorted << std::endl;
//    Rcpp::Rcout << "Tc " << tc_perm_sorted << std::endl;

    std::vector<int> tides(aspects.size(), 0);

    std::vector<int> tabc_perm_stats(n_perm, -1);

    for (unsigned i = 0; i < n_perm; ++i) {

        for (unsigned j = 0; j < aspects.size(); ++j) {
            if (i != n_perm - 1 and aspects_perm_stats[j][i] == aspects_perm_stats[j][i + 1]) {
                tides[j]++;
            } else {
                while (tides[j] > -1) {
                    unsigned k = aspects_perm_stats_order[j][i - tides[j]];
                    if (tabc_perm_stats[k] == -1) {
                        tabc_perm_stats[k] = i;
                    }
                    tides[j]--;
                }
                tides[j] = 0;
            }
        }

    }

    // Rcpp::Rcout << "Tabc perm " << tabc_perm_stats << std::endl;

    unsigned position = std::count_if(tabc_perm_stats.begin(), tabc_perm_stats.end(),
                                      [min_pos](double x) { return x <= min_pos; });

    perm_test_result res2((double)min_pos/(double)n_perm, n_perm, position);

    return res2;
}

template<class RNG>
perm_test_result t_abc(const std::vector<double> &x1,
                       const std::vector<double> &x2,
                       unsigned n_perm,
                       RNG &rng) {
    std::vector<aspect_ptr> aspects({a_aspect, b_aspect, c_aspect});
    return multiple_aspect_phase_2(x1, x2, n_perm, rng, aspects);
}

template<class RNG>
perm_test_result t_ab(const std::vector<double> &x1,
                      const std::vector<double> &x2,
                      unsigned n_perm,
                      RNG &rng) {
    std::vector<aspect_ptr> aspects({a_aspect, b_aspect});
    return multiple_aspect_phase_2(x1, x2, n_perm, rng, aspects);
}

template<class RNG>
perm_test_result t_ac(const std::vector<double> &x1,
                      const std::vector<double> &x2,
                      unsigned n_perm,
                      RNG &rng) {
    std::vector<aspect_ptr> aspects({a_aspect, c_aspect});
    return multiple_aspect_phase_2(x1, x2, n_perm, rng, aspects);
}

template<class RNG>
perm_test_result t_bc(const std::vector<double> &x1,
                      const std::vector<double> &x2,
                      unsigned n_perm,
                      RNG &rng) {
    std::vector<aspect_ptr> aspects({b_aspect, c_aspect});
    return multiple_aspect_phase_2(x1, x2, n_perm, rng, aspects);
}


#endif //RACE_MULTIPLE_ASPECTS_H
