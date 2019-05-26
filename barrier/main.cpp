#include <iostream>
#include <thread>
#include <vector>
#include "barrier.h"

void do_something(barrier *barr) {
    std::cout << "Hello" << std::endl;
    barr->wait(4);
    std::cout << "world" << std::endl;
    barr->wait(4);
    std::cout << " Guy " << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    auto st = new barrier();
    for(size_t i = 0; i < 4; i++) {
        threads.emplace_back(do_something, st);
    }
    for(auto& t: threads) {
        t.join();
    }
    return 0;
}