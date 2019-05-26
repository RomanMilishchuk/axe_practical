cmake_minimum_required(VERSION 3.14)
project(atomic_double)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)
add_library(atomic_double STATIC atomic_double.cpp atomic_double.hpp)
add_executable(atomic_double_tests main.cpp)
target_link_libraries(atomic_double_tests atomic_double Threads::Threads)
