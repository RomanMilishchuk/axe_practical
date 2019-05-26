//
// Created by YuraYeliseev on 2019-05-26.
//

#ifndef ACS_EXAM_MYMUTEX_H
#define ACS_EXAM_MYMUTEX_H

#include <iostream>
#include <pthread.h>
#include <thread>
#include <vector>

class myMutex {
protected:
    pthread_mutex_t _mutex;
public:
    myMutex();

    ~myMutex();

    void lock();

    void unlock();

    int try_lock();
};

void worker(int &var, int value, myMutex &mtx, std::vector<int>& check_vec);

void test_mutex();

#endif //ACS_EXAM_MYMUTEX_H
