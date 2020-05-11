#pragma once
#include <future>
#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <pthread.h>

class ThreadPool {
    std::vector<std::thread> pool;
    std::queue<std::function<void()>> tasks;
    std::atomic<bool> exist;
    std::condition_variable sleep;
    std::mutex mutex;
public:
    explicit ThreadPool(size_t poolsize);
    ~ThreadPool();
    void perform();
    
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>(std::bind(func, args...));
        auto res = task->get_future();
        std::lock_guard<std::mutex> lock(mutex);
        tasks.push(  [task](){ (*task)();}  );
        sleep.notify_one();
        return res;
    }
};