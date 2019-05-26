#include <iostream>
#include "atomic_string.hpp"
#include <vector>
#include <thread>

int main() {
    constexpr size_t num_th = 11;
    constexpr size_t num_er = 2;
    std::vector<std::string> words{"1234Very ", " meaningful ", " sentence ", " to ", " check ", " my ", " atomic ",
                                   " string ", " for ", " data ", " races "};
    std::vector<std::thread> threads;
    std::vector<std::thread> threads_ereasers;
    std::vector<std::thread> threads_ereasers2;
    std::atomic<std::string> str{};
    threads.reserve(num_th);
    threads_ereasers.reserve(num_er);
    threads_ereasers2.reserve(num_er);
    for (int i = 0; i < num_th; ++i) {
        threads.emplace_back([i, &words, &str] {
            str += words[i];
        });
    }
    for (auto &th:threads)
        th.join();
    std::vector<std::string> er{{"123456789"}, {" 123"}};
    std::atomic<std::string> str2{};
    std::cout << str << std::endl;
    for (int i = 0; i < num_er; ++i) {
        threads_ereasers.emplace_back([i, &er,&str2] {
            str2 += er[i];
        });
    }

    for (auto &th:threads_ereasers) {
        th.join();
    }
    std::cout << str2<< std::endl;
    for (int i = 0; i < num_er; ++i) {
        threads_ereasers2.emplace_back([i, &str2] {
            str2.erase(i*2,1);
        });
    }
    for (auto &th:threads_ereasers2) {
        th.join();
    }
    std::cout << str2<< std::endl;
    return 0;
}
