//
// Created by Andriy on 2019-05-26.
//

#include "thread_safe_queue.h"

template<class T>
void ConcurrentQueue<T>::push(T &&str) {
    std::unique_lock<std::mutex> lock(mt);
    deque.push(str);
    lock.unlock();
    cv.notify_one();
}

template<class T>
void ConcurrentQueue<T>::push(const T &str) {
    std::unique_lock<std::mutex> lock(mt);
    deque.push(std::move(str));
    lock.unlock();
    cv.notify_one();
}

template<class T>
T ConcurrentQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(mt);
    cv.wait(lock, [this] { return !deque.empty(); });
    T elem = deque.front();
    deque.pop();
    lock.unlock();
    cv.notify_one();
    return elem;
}

template<class T>
size_t ConcurrentQueue<T>::size() {
    std::unique_lock<std::mutex> lock(mt);
    return deque.size();
}

template<class T>
bool ConcurrentQueue<T>::empty() {
    return size() == 0;
}