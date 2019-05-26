#include <iostream>
#include <vector>
#include <thread>
#include "spin_lock.hpp"

int main() {
    constexpr size_t number_of_threads = 6;
    std::vector<std::thread> thread_vector;
    thread_vector.reserve(number_of_threads);
    spin_lock lock{};
    for (size_t i = 1; i <= number_of_threads; ++i) {
        thread_vector.emplace_back([i, &lock] {
            int k = i * 2;
            lock.lock();
            std::cout << i << ") Vector output: " << k << std::endl;
            lock.unlock();
        });
    }
    for (auto &th:thread_vector) {
        th.join();
    }
    return 0;
}