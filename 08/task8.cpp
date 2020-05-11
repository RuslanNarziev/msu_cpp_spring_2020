#include "task8.h"

ThreadPool::ThreadPool(size_t poolsize) {
    exist = true;
    for (size_t i = 0; i < poolsize; i++)
        pool.emplace_back(std::thread([this]() { this->perform();}));
}

ThreadPool::~ThreadPool() {
    exist = false;
    sleep.notify_all();
    for (size_t i = 0; i < pool.size(); i++) {
        pool[i].join();
    }
}

void ThreadPool::perform(){
    while(exist) {
        std::unique_lock<std::mutex> lock(mutex);
        if (tasks.empty()){
            sleep.wait(lock);
        } 
        auto task(std::move(tasks.front()));
        tasks.pop();
        lock.unlock();
        task();
    }
}