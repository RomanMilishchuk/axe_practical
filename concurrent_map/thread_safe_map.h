//
// Created by Andriy on 2019-05-26.
//

#ifndef CONCURRENT_QUEUE_THREAD_SAFE_MAP_H
#define CONCURRENT_QUEUE_THREAD_SAFE_MAP_H

#include <map>
#include <mutex>
#include <condition_variable>

template<class K, class V>
class ConcurrentMap {
    std::map<K, V> map;
    std::condition_variable cv;
    std::mutex mt;
public:
    V &operator[](const K &key);

    V &operator[](K &&key);

    size_t size();

    bool empty();
};

#endif //CONCURRENT_QUEUE_THREAD_SAFE_MAP_H
