cmake_minimum_required(VERSION 3.12)
project(async)

find_package(Threads)
set(CMAKE_CXX_STANDARD 17)

add_executable(async main.cpp)

target_link_libraries(async Threads::Threads)