cmake_minimum_required(VERSION 3.14)
project(concurrent_map)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)
add_executable(concurrent_map thread_safe_map.cpp thread_safe_map.h main.cpp)
target_link_libraries(concurrent_map Threads::Threads)
