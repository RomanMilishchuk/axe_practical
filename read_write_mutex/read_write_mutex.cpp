//
// Created by Andriy on 2019-05-26.
//

#include "read_write_mutex.h"

void RWMutex::reader_lock() {
    mt.lock();
    readers++;
    mt.unlock();

//    std::unique_lock<std::mutex> lock(mt);
//    readers++;
//    lock.unlock();
}

void RWMutex::reader_unlock() {
    mt.lock();
    readers--;
    mt.unlock();

//    std::unique_lock<std::mutex> lock(mt);
//    readers--;
//    if (readers == 0) {
//        cv.notify_one();
//    }
//    lock.unlock();
}

void RWMutex::writer_lock() {
//    std::unique_lock<std::mutex> lock(mt);
//    while (readers > 0) {
//        cv.wait(lock, [] { return; });
//    }

    for (;;) {
        mt.lock();
        if (readers > 0) {
            mt.unlock();
        } else {
            break;
        }
    }
}

void RWMutex::writer_unlock() {
    mt.unlock();
//    cv.notify_one();
}