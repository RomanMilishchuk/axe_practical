//
// Created by hermann on 26.05.19.
//

#ifndef SPINLOCK_SPIN_LOCK_HPP
#define SPINLOCK_SPIN_LOCK_HPP

#include <atomic>
#include <condition_variable>

class spin_lock {
    std::atomic_flag flag;

    bool is_locked();

public:
    spin_lock();

    void lock();

    void unlock();
};

#endif //SPINLOCK_SPIN_LOCK_HPP
