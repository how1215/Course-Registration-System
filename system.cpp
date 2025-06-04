#include <thread>
#include <iostream>
#include <vector>


void thread_function(int i){
    std::cout << "I am thread" << i  << std::endl;
}

int main(){
    std::vector<std::thread> threads;

    for(int i = 0; i < 3; i++){
        threads.push_back(std::thread(thread_function, i));
    }
    for(auto& thread : threads){
        thread.join();
    }

    std::cout << "I am master thread and I am about to finish"<< std::endl;
    return 0;
}