#include "thread_pool.h"

Thread_pool::Thread_pool(size_t thread_count) : done(false), queue() {
    try {
        for (size_t i = 0; i < thread_count; i++) {
            threads.emplace_back(&Thread_pool::worker, this);
        }
    } catch (std::exception &e) {
        done = true;
        throw;
    }
}

Thread_pool::~Thread_pool() {
    done = true;
    for (auto &t: threads)
        t.join();
}

void Thread_pool::submit(const std::function<void()> &func) {
    queue.push(func);
}

void Thread_pool::worker() {
    while (!done || queue.size()) {
        std::function<void()> task;
        auto is_work = queue.pop(task);
        if (is_work)
            task();
    }
}
