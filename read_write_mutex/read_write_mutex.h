//
// Created by Andriy on 2019-05-26.
//

#ifndef CONCURRENT_MAP_READ_WRITE_MUTEX_H
#define CONCURRENT_MAP_READ_WRITE_MUTEX_H

#include <mutex>
#include <condition_variable>

class RWMutex {
    std::mutex mt;
    std::condition_variable cv;
    int readers;
public:

    void reader_lock();

    void reader_unlock();

    void writer_lock();

    void writer_unlock();

};

#endif //CONCURRENT_MAP_READ_WRITE_MUTEX_H
