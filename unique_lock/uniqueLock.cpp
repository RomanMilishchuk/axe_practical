//
// Created by YuraYeliseev on 2019-05-26.
//

#include "uniqueLock.h"

template<class MutexType>
m_unique_lock<MutexType>::m_unique_lock(MutexType &_m) : _mutex(&_m), is_owning(true) {}

template<class MutexType>
m_unique_lock<MutexType>::m_unique_lock(MutexType &_m, std::defer_lock_t t) : _mutex(&_m), is_owning(false) {}

template<class MutexType>
void m_unique_lock<MutexType>::unlock() {
    if(!is_owning)
        throw std::runtime_error("Operation is not permitted");
    else if(_mutex){
        _mutex->unlock();
        is_owning = false;
    }
}

template<class MutexType>
void m_unique_lock<MutexType>::lock() {
    if (!_mutex || is_owning)
        throw std::runtime_error("Operation is not permitted");
    _mutex->lock();
    is_owning = true;
}

template<class MutexType>
m_unique_lock<MutexType>::~m_unique_lock() {
    if(is_owning)
        unlock();
}

template<class MutexType>
bool m_unique_lock<MutexType>::try_lock() {
    if (!_mutex || is_owning)
        throw std::runtime_error("Operation is not permitted");
    is_owning = _mutex->try_lock();
    return is_owning;
}