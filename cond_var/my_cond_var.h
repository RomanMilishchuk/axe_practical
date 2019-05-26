//
// Created by YuraYeliseev on 2019-05-26.
//

#ifndef ACS_EXAM_MY_COND_VAR_H
#define ACS_EXAM_MY_COND_VAR_H

#include <iostream>
#include <pthread.h>
#include <queue>
#include <thread>

class myCondVar{
protected:
    pthread_cond_t _cond;
public:
    myCondVar();

    ~myCondVar();

    void wait(pthread_mutex_t mtx);

    void notify_one();

    void notify_all();
};

//Ukral na cpp ref
void test_cond_var();


#endif //ACS_EXAM_MY_COND_VAR_H
