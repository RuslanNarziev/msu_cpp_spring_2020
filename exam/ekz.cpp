#include <iostream>
#include <thread>
#include <pthread.h>
#include <fstream>
#include <vector>
#include <queue>
#include <mutex>
#include <string>
#include <sstream>

std::ifstream file;
std::queue<std::string> queue;
bool read = false;
unsigned int sum = 0;
std::mutex mutex_q;
std::mutex mutex_s;

void sumator(){
    std::string str;
    unsigned int num;
    while(!read || !queue.empty()) {
        
        mutex_q.lock();
        if(queue.empty()) {
            mutex_q.unlock();
            continue;
        }
        str = queue.front();
        queue.pop();
        mutex_q.unlock();
        
        std::stringstream ss(str);
        num = 0;
        for(int number; ss >> number; num += number);
        mutex_s.lock();
        sum += num;
        mutex_s.unlock();
    }
    return;
}

void read_file(){
    while (!file.eof()){
        std::string str;
        std::getline(file, str);
        if (!str.empty()){
            mutex_q.lock();
            queue.push(str);
            mutex_q.unlock();
        }
    }
    read = true;
}

int main(){
    std::string name;
    name = "test.txt";
    file.open(name);
    std::thread thread(read_file);
    std::thread thread_1(sumator);
    std::thread thread_2(sumator); 
    thread.join();
    thread_1.join();
    thread_2.join();
    std::cout << sum << '\n';
    return 0;
}
