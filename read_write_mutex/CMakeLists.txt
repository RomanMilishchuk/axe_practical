cmake_minimum_required(VERSION 3.14)
project(rwmutex)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)
add_executable(rwmutex read_write_mutex.cpp read_write_mutex.h main.cpp)
target_link_libraries(rwmutex Threads::Threads)
