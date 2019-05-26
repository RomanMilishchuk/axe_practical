#include <iostream>
#include <chrono>
#include "async.h"

int add(int x, int y) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    return x + y;
}

int main() {
    int x = 1, y = 4;
    std::cout << async(launch::async, add, x, y).get() << std::endl;
    return 0;
}