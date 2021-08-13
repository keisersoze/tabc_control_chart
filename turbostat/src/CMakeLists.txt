cmake_minimum_required(VERSION 3.9)
project(race)

find_package(OpenMP REQUIRED)

add_executable(test_omp tests/test_omp.cpp)
add_executable(test_rank_function utils.h tests/test_rank_function.cpp)
add_executable(race cucconi_multisample_test.cpp cucconi_multisample_test.h utils.h tests/test1.cpp)
add_executable(sum_of_ranks tests/test_sum_of_ranks.cpp faststat.h faststat.cpp  )


target_link_libraries(test_omp PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(race PRIVATE OpenMP::OpenMP_CXX)

