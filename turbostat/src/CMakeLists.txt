cmake_minimum_required(VERSION 3.9)
project(race)

find_package(OpenMP REQUIRED)

add_executable(test_T_a tests/test_Ta.cpp faststat.h faststat.cpp  )
add_executable(test_T_a_class stat/Ta.cpp stat/Ta.h tests/test_Ta_class.cpp stat/shared.h )
add_executable(test_Test_class TestClass.cpp TestClass.h )
add_executable(test TaRBinding.cpp TaRBinding.h )




# target_link_libraries(test_omp PRIVATE OpenMP::OpenMP_CXX)
# target_link_libraries(race PRIVATE OpenMP::OpenMP_CXX)

