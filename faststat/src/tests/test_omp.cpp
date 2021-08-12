//
// Created by filip on 12/08/2021.
//

#include <omp.h>
#include <iostream>
#include <chrono>

int main()
{
//    int id;
//
//    #pragma omp for
//    for (int i = 0; i < 5 ; ++i) {
//        std::cout << "Hello World!" << std::endl;
//    }

    int a[100000];

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    #pragma omp parallel for default(none) shared(a)
    for (int i = 0; i < 100000; i++) {
        a[i] = 2 * i;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[milliseconds]" << std::endl;

    return 0;

    return 0;
}

