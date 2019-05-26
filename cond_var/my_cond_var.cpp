//
// Created by YuraYeliseev on 2019-05-26.
//

#include "my_cond_var.h"

myCondVar::myCondVar(){
    _cond = PTHREAD_COND_INITIALIZER;
}

myCondVar::~myCondVar(){
    pthread_cond_destroy(&_cond);
}

void myCondVar::wait(pthread_mutex_t mtx){
    pthread_cond_wait(&_cond, &mtx);
}

void myCondVar::notify_one(){
    pthread_cond_signal(&_cond);
}

void myCondVar::notify_all(){
    pthread_cond_broadcast(&_cond);
}

void test_cond_var(){

    std::queue<int> produced_nums;
    pthread_mutex_t m;
    myCondVar cond_var = myCondVar();
    bool done = false;
    bool notified = false;

    std::thread producer([&]() {
        for (int i = 0; i < 5; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            pthread_mutex_lock(&m);
            std::cout << "producing " << i << '\n';
            produced_nums.push(i);
            notified = true;
            cond_var.notify_one();
            pthread_mutex_unlock(&m);
        }

        done = true;
        cond_var.notify_one();
    });

    std::thread consumer([&]() {
        pthread_mutex_lock(&m);
        while (!done) {
            while (!notified) {  // loop to avoid spurious wakeups
                cond_var.wait(m);
            }
            while (!produced_nums.empty()) {
                std::cout << "consuming " << produced_nums.front() << '\n';
                produced_nums.pop();
            }
            notified = false;
        }
        pthread_mutex_unlock(&m);

    });

    producer.join();
    consumer.join();
}