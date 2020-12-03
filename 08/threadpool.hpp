#pragma once
#include <thread>
#include <mutex>
#include <future>
#include <vector>
#include <queue>
#include <functional>

class ThreadPool
{
    size_t size;
    bool finished;
    std::mutex task_mutex;
    std::condition_variable condition;
    std::vector<std::thread> threads;
    std::queue<std::packaged_task<void()>> tasks;
    
    void exec_task();
public:
    explicit ThreadPool(size_t);
    ~ThreadPool();
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};

#include "impl/threadpool.tpp"