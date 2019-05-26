//
// Created by Andriy on 2019-05-26.
//

#include "thread_safe_map.h"
#include <iostream>

int main() {

    ConcurrentMap<std::string, int> map;
    std::map<std::string, int> norm_map;
    const int test = 12;
    map["key"] = test;

//    std::cout << map["key"] << std::endl;

    return 0;
}


