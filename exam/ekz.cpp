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
std::queue<int> queue;
bool read = false;
unsigned int sum = 0;
std::mutex mutex_q;
std::mutex mutex_s;

void sumator(){
    unsigned int num;
    while(!read || !queue.empty()) {
        mutex_q.lock();
        if(queue.empty()) {
            mutex_q.unlock();
            continue;
        }
        num = queue.front();
        queue.pop();
        mutex_q.unlock();
        mutex_s.lock();
        sum += num;
        mutex_s.unlock();
    }
    return;
}

void read_file(){
    unsigned int num;
    while (!file.eof()){
        file >> num;
        if(!file.eof()) {
            mutex_q.lock();
            queue.push(num);
            mutex_q.unlock();
        }
    }
    read = true;
}

int main(){
    std::string name;
    std::cin >> name;
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