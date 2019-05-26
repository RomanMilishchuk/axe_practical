cmake_minimum_required(VERSION 3.12)
project(barrier)

find_package(Threads)
set(CMAKE_CXX_STANDARD 14)

add_executable(barrier main.cpp)

target_link_libraries(barrier Threads::Threads)