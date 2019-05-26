//
// Created by YuraYeliseev on 2019-05-26.
//

#ifndef ACS_EXAM_UNIQUELOCK_H
#define ACS_EXAM_UNIQUELOCK_H

#include <iostream>
#include <vector>
#include <thread>

template<class MutexType>
class m_unique_lock {
private:
    MutexType *_mutex;
    bool is_owning;
public:
    explicit m_unique_lock(MutexType& _m);

    m_unique_lock(MutexType &_m, std::defer_lock_t t);

    void unlock();

    void lock();

    ~m_unique_lock();

    bool try_lock();
};

std::mutex m_a, m_b, m_c;
int a, b, c = 1;
void update()
{
    {   // Note: std::lock_guard or atomic<int> can be used instead
        m_unique_lock<std::mutex> lk = m_unique_lock<std::mutex>(m_a);
        a++;
    }

    { // Note: see std::lock and std::scoped_lock for details and alternatives
        m_unique_lock<std::mutex> lk_b = m_unique_lock<std::mutex>(m_b, std::defer_lock);
        m_unique_lock<std::mutex> lk_c = m_unique_lock<std::mutex>(m_c, std::defer_lock);
        std::lock(lk_b, lk_c);
        b = std::exchange(c, b+c);
    }
}

void test_unique_lock()
{
    std::vector<std::thread> threads;
    for (unsigned i = 0; i < 12; ++i)
        threads.emplace_back(update);

    for (auto& i: threads)
        i.join();

    std::cout << a << "'th and " << a+1 << "'th Fibonacci numbers: "
              << b << " and " << c << '\n';
}


#endif //ACS_EXAM_UNIQUELOCK_H
