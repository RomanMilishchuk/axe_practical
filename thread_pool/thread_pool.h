#ifndef THREAD_POOL_THREAD_POOL_H
#define THREAD_POOL_THREAD_POOL_H

#include <vector>
#include <atomic>
#include <thread>
#include <functional>

#include "concurrent_queue.h"

#include <iostream>
#include <sstream>

class Thread_pool {
public:
    explicit Thread_pool(size_t thread_count);

    ~Thread_pool();

    void submit(const std::function<void()> &func);

private:
    void worker();

    std::vector<std::thread> threads;
    std::atomic_bool done;
    ConcurrentQueue<std::function<void()> > queue;
};


#endif //THREAD_POOL_THREAD_POOL_H
