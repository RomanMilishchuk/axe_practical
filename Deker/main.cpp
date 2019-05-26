#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <array>

void func_with_critical_region(std::vector<std::string> &very_useful_vector, const int thread_id,
                               std::array<std::atomic_bool, 2> &flags,
                               std::atomic<int> &turn) {
    // Random section
    std::string out{std::to_string(thread_id) + ") Thread_task"};
    // Start of critical
    flags[thread_id] = true;
    while (flags[thread_id ^ 1]) {
        if (turn != thread_id) {
            flags[thread_id] = false;
            while (turn != thread_id) {
                std::this_thread::yield();
            }
            flags[thread_id] = true;
        }
        std::this_thread::yield();
    }
    very_useful_vector.emplace_back(out);
    //end of it
    turn = 1 ^ thread_id;
    flags[thread_id] = false;
}

int main() {
    constexpr int num_threads = 2;
    std::vector<std::string> vec{};
    std::vector<std::thread> threads{};
    threads.reserve(num_threads);
    std::array<std::atomic_bool, 2> flags{};
    std::atomic<int> turn{1};

    for (int i = 0; i < num_threads; ++i)
        threads.emplace_back(func_with_critical_region, std::ref(vec), i, std::ref(flags), std::ref(turn));
    for (auto &t:threads)
        t.join();

    for (auto &st:vec) {
        std::cout << st << std::endl;
    }
    return 0;
}
