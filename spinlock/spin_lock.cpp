#include <thread>
#include "spin_lock.hpp"

spin_lock::spin_lock() {
    flag.clear();
}

bool spin_lock::is_locked() {
    return flag.test_and_set(std::memory_order::memory_order_acquire);
}

void spin_lock::lock() {
    while(is_locked()){
        std::this_thread::yield();
    }
}

void spin_lock::unlock() {
    flag.clear();
}