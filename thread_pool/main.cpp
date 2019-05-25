#include<iostream>
#include <algorithm>
#include <future>
#include "thread_pool.h"

int main(int argc, char *argv[]) {
    size_t num = 4;
    std::vector<int> vec(num);
    std::vector<std::promise<int>> promises(num);
    std::vector<std::future<int>> futures;
    futures.reserve(num);
    {
        Thread_pool pool(3);

        for (int i = 0; i < num; i++) {
            futures.push_back(promises[i].get_future());
            pool.submit(std::bind([i](std::promise<int> *p) {
                p->set_value(i);
            }, &promises[i]));
        }
    }
    for (size_t i = 0; i < num; i++) {
        vec[i] = futures[i].get();
    }

    std::sort(vec.begin(), vec.end());
    for (size_t i = 0; i < num; i++) {
        if (i != vec[i])
            std::cout << "Something went wrong!" << std::endl;
    }
    return 0;
}
