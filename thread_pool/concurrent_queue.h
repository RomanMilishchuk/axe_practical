#ifndef PARALLEL_READING_CONCURENT_QUEUE_H
#define PARALLEL_READING_CONCURENT_QUEUE_H

#include<deque>
#include<condition_variable>
#include<mutex>

template<class T>
class ConcurrentQueue {
private:
    std::deque<T> data;
    std::condition_variable queue_check;
    std::mutex deque_mutex;
public:
    ConcurrentQueue() = default;

    void push(const T &element);

    void push(T &&element);

    bool pop(T& value);

    size_t size();

};

#include "concurrent_queue.cpp"

#endif //PARALLEL_READING_CONCURENT_QUEUE_H
