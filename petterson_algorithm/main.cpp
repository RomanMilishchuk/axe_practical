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

void first_process(int &counter, const int max_number, std::string &text) {
    flag[0] = 1;
    turn = 1;
    std::cout << "First_process start" << std::endl;
    if (text == "def") {
        text = "ghi";
        counter++;
    }
    while (flag[1] == 1 && turn == 1) {}
    for (int i = 0; i < max_number; ++i) {
        ++counter;
    }
    std::cout << "First_process end" << std::endl;
    flag[0] = 0;
}

void second_process(int &counter, const int max_number, std::string &text) {
    flag[1] = 1;
    turn = 0;
    while (flag[0] == 1 && turn == 0) {}
    std::cout << "Second_process start" << std::endl;
    if (text == "abc") {
        text = "def";
        counter++;
    }
    for (int i = 0; i < max_number; ++i) {
        ++counter;
    }
    std::cout << "Second_process end" << std::endl;
    flag[1] = 0;
}

int main() {

    int max = 100;
    int counter = 0;

    std::string test = "abc";

    std::thread first(first_process, std::ref(counter), max, std::ref(test));
    std::thread second(second_process, std::ref(counter), max, std::ref(test));

//    while (flag[0] && flag[1]) {}

    first.join();
    second.join();

    std::cout << counter << std::endl;
    std::cout << test << std::endl;

    return 0;

}