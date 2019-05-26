#include "concurrent_queue.h"


template<class T>
void ConcurrentQueue<T>::push(const T &element) {
    std::unique_lock<std::mutex> locker(deque_mutex);
    data.push_back(element);
    locker.unlock();
    queue_check.notify_one();
}

template<class T>
void ConcurrentQueue<T>::push(T &&element) {
    std::unique_lock<std::mutex> locker(deque_mutex);
    data.push_back(std::move(element));
    locker.unlock();
    queue_check.notify_one();
}

template<class T>
bool ConcurrentQueue<T>::pop(T &value) {
    std::unique_lock<std::mutex> locker(deque_mutex);
    if (data.empty())
        return false;
    queue_check.wait(locker, [this] { return !data.empty(); });
    value = std::move(data.front());
    data.pop_front();
    return true;
}

template<class T>
size_t ConcurrentQueue<T>::size() {
    std::unique_lock<std::mutex> locker(deque_mutex);
    return data.size();
}
