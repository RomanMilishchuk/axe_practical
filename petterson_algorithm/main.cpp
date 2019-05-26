//
// Created by Andriy on 2019-05-26.
//
#include <atomic>
#include <string>
#include <thread>
#include <iostream>

std::atomic<int> flag[2]{{0},
                         {0}};
std::atomic<int> turn;

void first_process(int &counter, const int max_number) {
    flag[0] = 1;
    turn = 1;
    while (flag[1] == 1 && turn == 1) {}
    for (int i = 0; i < max_number; ++i) {
        counter++;
    }
    flag[0] = 0;
}

void second_process(int &counter, const int max_number) {
    flag[1] = 1;
    turn = 0;
    while (flag[0] == 1 && turn == 0) {}
    for (int i = 0; i < max_number; ++i) {
        counter++;
    }
    flag[1] = 0;
}

int main() {

    int max = 100;
    int counter = 0;
    std::thread first(first_process, std::ref(counter), max);
    std::thread second(second_process, std::ref(counter), max);

    while (flag[0] && flag[1]) {}

    first.join();
    second.join();

    std::cout << counter << std::endl;

    return 0;

}