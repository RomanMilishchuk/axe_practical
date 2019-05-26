#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

void func_with_critical_region(std::vector<std::string> &very_useful_vector,const int my_number,std::atomic<int> &cur_thread){
// Random section
    int a = 1;
    std::string out{};
    out+= std::to_string(my_number) + ") Thread_task";
    // Start of critical
    while(cur_thread.load()!=my_number){}
    very_useful_vector.emplace_back(out);
    //end of it
    cur_thread=0;
}

int main() {
    constexpr int num_threads= 2;
    std::vector<std::string> vec{};
    std::vector<std::thread> thrds{};
    std::atomic<int> cur{1};
    thrds.reserve(num_threads);
    for (int i = 0; i < num_threads; ++i) {
        thrds.emplace_back(func_with_critical_region,std::ref(vec),i,std::ref(cur));
    }
    for(auto &th:thrds){
        th.join();
    }
    for(auto &st:vec){
        std::cout<<st<<std::endl;
    }
    return 0;
}