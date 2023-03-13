#ifndef THREAD_TASK_THREAD_H_
#define THREAD_TASK_THREAD_H_

#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>

class ThreadPool {
 public:
  explicit ThreadPool(uint num = std::thread::hardware_concurrency());
  ThreadPool(const ThreadPool& other);
  ThreadPool(ThreadPool&& other) = delete;
  ~ThreadPool();
  ThreadPool operator=(const ThreadPool& other);
  ThreadPool operator=(ThreadPool&& other) = delete;
  void Go();
  uint64_t AddTask(const std::function<void()>& foo);
  void Wait(uint64_t task_id);
  void WaitAll();

 private:
  std::vector<std::thread> pool_;
  std::queue<std::pair<std::function<void()>, uint64_t>> f_queue_;
  std::vector<int> v;
  uint64_t id_ = 0;
  std::mutex mtx1_;
  std::mutex mtx2_;
  std::condition_variable cv_;
  std::vector<uint64_t> done_tasks_ids_;
  bool wake_up_ = false;
  bool quit_ = false;
};

#endif  // THREAD_TASK_THREAD_H_