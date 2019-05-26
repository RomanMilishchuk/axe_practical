#include "myMutex.h"

myMutex::myMutex(){
    _mutex = PTHREAD_MUTEX_INITIALIZER;
}

myMutex::~myMutex(){
    pthread_mutex_destroy(&_mutex);
}
void myMutex::lock(){
    int rv = pthread_mutex_lock(&_mutex);
    if(rv != 0){
        throw std::runtime_error("Error while lock happened!");
    }
}
void myMutex::unlock(){
    int rv = pthread_mutex_unlock(&_mutex);
    if(rv != 0){
        throw std::runtime_error("Error while unlock happened!");
    }
}
int myMutex::try_lock(){
    int rv = pthread_mutex_trylock(&_mutex);
    if(rv == 0) {return 1}
	else if(rv == 16) {
return 0;}
    else {
	throw std::runtime_error("Error while lock happened!");
}
}

void worker(int &var, int value, myMutex &mtx, std::vector<int>& check_vec){
    mtx.lock();
    var = value;
    check_vec.push_back(var);
    mtx.unlock();
}

void test_mutex(){
    size_t temp, size;
    int a = 0;
    myMutex mtx = myMutex();
    std::vector<std::thread> threads;
    std::vector<int> check_vec;
    for (int i = 0; i < 1000; i++)
        threads.push_back(std::thread(worker, std::ref(a), i, std::ref(mtx), std::ref(check_vec)));

    for(auto &thread: threads)
        thread.join();

    temp = check_vec.size();
    auto last = std::unique(check_vec.begin(), check_vec.end());
    check_vec.erase(last, check_vec.end());
    if(temp != check_vec.size())
        std::cout << "GG WP!" << std::endl;
    std::cout << "You woN!" << std::endl;
}
