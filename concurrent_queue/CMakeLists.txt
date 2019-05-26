cmake_minimum_required(VERSION 3.14)
project(concurrent_queue)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)
add_executable(concurrent_queue thread_safe_queue.h thread_safe_queue.cpp main.cpp)
target_link_libraries(concurrent_queue Threads::Threads)
