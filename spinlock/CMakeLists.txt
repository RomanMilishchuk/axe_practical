cmake_minimum_required(VERSION 3.12)
project(spinlock)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)
add_library(spin_lock STATIC spin_lock.cpp spin_lock.hpp)
target_link_libraries(spin_lock Threads::Threads)
add_executable(test main.cpp)
target_link_libraries(test spin_lock Threads::Threads)
