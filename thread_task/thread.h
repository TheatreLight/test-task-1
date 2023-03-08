#ifndef THREAD_TASK_THREAD_H_
#define THREAD_TASK_THREAD_H_

#include <thread>
#include <functional>
#include <vector>

class ThreadPool {
 public:
  ThreadPool();
  ThreadPool(const ThreadPool& other);
  ThreadPool(ThreadPool&& other) = delete;
  ~ThreadPool() = default;
  ThreadPool operator=(const ThreadPool& other);
  ThreadPool operator=(ThreadPool&& other) = delete;

  uint64_t AddTask(std::function<void(int)> foo);
  void Wait(uint64_t task_id);
  void WaitAll();

 private:
  std::vector<std::thread> pool_;
};

#endif  // THREAD_TASK_THREAD_H_