#ifndef ACS_EXAM_MYSEMAPHORE_H
#define ACS_EXAM_MYSEMAPHORE_H

#include <iostream>
#include <thread>
#include <vector>


class Semaphore {
    const size_t permissions_number;
    size_t available;
    std::mutex m;
    std::condition_variable aqu_cond, rel_cond;
public:
    Semaphore(const size_t per_value = 1);

    void aquire();

    void release();

    size_t available_number();
};

void sem_func(Semaphore& a);

void test_semaphore();


#endif //ACS_EXAM_MYSEMAPHORE_H
