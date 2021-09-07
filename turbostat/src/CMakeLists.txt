cmake_minimum_required(VERSION 3.9)
project(race)

set (CMAKE_CXX_STANDARD 11)

find_package(OpenMP REQUIRED)

# add_executable(test_T_a tests/test_Ta.cpp old/faststat.h old/faststat.cpp)
# add_executable(test_T_a_class stat/Ta.cpp stat/Ta.h tests/test_Ta_class.cpp stat/shared.h )
# add_executable(test_Test_class old/TestClass.cpp old/TestClass.h)
# add_executable(test TaRBinding.cpp TaRBinding.h )

add_executable(data_aspects data_aspects.h data_aspects.cpp utils.h utils.cpp test_result.h test_result.cpp)
add_executable(single_aspect_tests data_aspects.h data_aspects.cpp utils.h utils.cpp test_result.h test_result.cpp single_aspect.cpp single_aspect.h)


# target_link_libraries(test_omp PRIVATE OpenMP::OpenMP_CXX)
# target_link_libraries(race PRIVATE OpenMP::OpenMP_CXX)

