//
// Created by Andriy on 2019-05-26.
//

#include "thread_safe_map.h"

template<class K, class V>
V &ConcurrentMap<K, V>::operator[](const K &key) {
    std::unique_lock<std::mutex> lock(mt);
    V value;
    if (map.find(key) != map.end()) {
        value = map.find(key);
    } else {
        value = V{};
    }
    map.try_emplace(key, value);
    lock.unlock();
    return value;
}

template<class K, class V>
V &ConcurrentMap<K, V>::operator[](K &&key) {
    std::unique_lock<std::mutex> lock(mt);
    V value;
    if (map.find(key) != map.end()) {
        value = map.find(key);
    } else {
        value = V{};
    }
    map.try_emplace(std::move(key), value);
    lock.unlock();
    return value;
}

template<class K, class V>
size_t ConcurrentMap<K, V>::size() {
    std::unique_lock<std::mutex> lock(mt);
    return map.size();
}

template<class K, class V>
bool ConcurrentMap<K, V>::empty() {
    return map.size() == 0;
}