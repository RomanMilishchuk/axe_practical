#include "mySemaphore.h"

Semaphore::Semaphore(const size_t per_value) : permissions_number(per_value), available(per_value) {}

void Semaphore::aquire() {
    std::unique_lock<std::mutex> lck(m);
    aqu_cond.wait(lck, [this](){return available > 0;});
    available--;
    m.unlock();
    rel_cond.notify_one();
}

void Semaphore::release() {
    std::unique_lock<std::mutex> lck(m);
    rel_cond.wait(lck, [this](){ return available < permissions_number;});
    available++;
    m.unlock();
    aqu_cond.notify_one();
}

size_t Semaphore::available_number() {
    return available;
}

void sem_func(Semaphore &a) {
    a.aquire();
    std::cout << "Entered!" << std::endl;
    for (int roman = 100; roman > 0; roman--)
    {}
    std::cout << "Leaved!" << std::endl;
    a.release();
}

void test_semaphore() {
    Semaphore b(1);
    std::thread a(sem_func, std::ref(b));
    std::thread c(sem_func, std::ref(b));
    a.join();
    c.join();
}
