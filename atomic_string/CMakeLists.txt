cmake_minimum_required(VERSION 3.14)
project(atomic_string)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)
add_library(atomic_string STATIC atomic_string.cpp atomic_string.hpp)
add_executable(atomic_string_tests main.cpp)
target_link_libraries(atomic_string_tests atomic_string Threads::Threads)
