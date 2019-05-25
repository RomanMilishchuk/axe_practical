cmake_minimum_required(VERSION 3.12)

project(thread_pool)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)
add_executable(thread_pool main.cpp thread_pool.cpp)

target_link_libraries(thread_pool Threads::Threads)
