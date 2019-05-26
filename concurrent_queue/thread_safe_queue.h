#ifndef AXE_PRACTICAL_THREAD_SAFE_QUEUE_H
#define AXE_PRACTICAL_THREAD_SAFE_QUEUE_H

#include <deque>
#include <mutex>
#include <condition_variable>

template<typename T>
class ConcurrentQueue {
    std::deque<T> deque;
    std::condition_variable cv;
    std::mutex mt;
public:
    ConcurrentQueue() = default;

    size_t size();

    void push(T &&str);

    void push(const T &str);

    T pop();

    bool empty();
};

#endif //AXE_PRACTICAL_THREAD_SAFE_QUEUE_H
