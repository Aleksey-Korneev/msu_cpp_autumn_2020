void ThreadPool::exec_task()
{
    //one thread can execute numerous tasks
    while (true) {
        std::unique_lock<std::mutex> lock(task_mutex);
        if (tasks.empty()) {
            //waiting for a new task
            condition.wait(lock, [this]() { return finished || !tasks.empty(); });
        }
        //all tasks are performed
        if (tasks.empty() && finished) {
            return;
        }
        //getting a task from a queue
        std::packaged_task<void()> task = std::move(tasks.front());
        tasks.pop();
        //finally performing a task
        task();
    }
}

ThreadPool::ThreadPool(size_t poolSize)
        : size(poolSize), finished(false)
{
    //fulfill a pool with threads
    for (size_t i = 0; i < poolSize; ++i) {
        threads.emplace_back([this](){ exec_task(); });
    }
}

ThreadPool::~ThreadPool()
{
    { //parantheses are required for using std::unique_lock
        std::unique_lock<std::mutex> lock(task_mutex);
        finished = true;
    }
    condition.notify_all();
    for (std::thread& thread : threads) {
        thread.join();
    }
}

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))>
{
    std::packaged_task<decltype(func(args...))()>
            pack_task(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
     std::future<decltype(func(args...))> res(pack_task.get_future());
     {
         std::unique_lock<std::mutex> lock(task_mutex);
         tasks.emplace(std::move(pack_task)); //push vs emplace - ?
     }
     //Notify one thread of a new task
     condition.notify_one();
     return res;
}