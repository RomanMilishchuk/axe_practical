cmake_minimum_required(VERSION 3.12)
project(peterson)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)
add_executable(peterson main.cpp)
target_link_libraries(peterson Threads::Threads)
