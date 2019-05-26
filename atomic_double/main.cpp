#include <iostream>
#include <thread>
#include <vector>
#include "atomic_double.hpp"

int main() {
    constexpr size_t numthreads = 5;
    std::vector<std::thread> vector_threds;
    vector_threds.reserve(numthreads);
    std::atomic<double> atm_dbl{};
    for (int i = 1; i <= numthreads; ++i) {
        vector_threds.emplace_back([i, &atm_dbl] {
            atm_dbl+=i*100;
        });
    }
    for(auto &th:vector_threds)
        th.join();
    std::cout<<atm_dbl<<std::endl;
    return 0;
}