#ifndef BARRIER_BARRIER_H
#define BARRIER_BARRIER_H

#include <mutex>
#include <condition_variable>
#include <iostream>
#include <atomic>
#include <thread>

class barrier {
public:
    barrier() : is_waiting(false), entered(0) {};

    void wait(size_t thread_number) {
        while (!(!entered || is_waiting)) {
            std::this_thread::yield();
        }
        std::unique_lock<std::mutex> lg(lock);
        ++entered;
        if (entered == 1)
            is_waiting = true;
        if (entered == thread_number) {
            is_waiting = false;
            --entered;
            lg.unlock();
            cv.notify_all();
            return;
        }
        cv.wait(lg, [&flag = is_waiting] { return !flag; });
        --entered;
    }

private:
    std::atomic<int> entered;
    std::atomic_bool is_waiting;
    std::condition_variable cv;
    std::mutex lock;
};


#endif //BARRIER_BARRIER_H
