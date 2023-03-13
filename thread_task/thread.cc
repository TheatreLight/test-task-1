#include "thread.h"

ThreadPool::ThreadPool(uint num) {
  for (int i = 0; i < num; ++i) {
    pool_.emplace_back(&Go, this);
  }
}

ThreadPool::~ThreadPool() {
  quit_ = true;
}

void ThreadPool::Go() {
  while (!quit_) {
    std::unique_lock<std::mutex> ul(mtx1_);
    cv_.wait(ul, wake_up_);
    if (!f_queue_.empty()) {
      auto task = f_queue_.front();
      f_queue_.pop();
      ul.unlock();
      task.first();
      std::lock_guard<std::mutex> guard(mtx2_);
      done_tasks_ids_.push_back(task.second);
    }
    if (f_queue_.empty()) wake_up_ = false;
  }
}

uint64_t ThreadPool::AddTask(const std::function<void()>& foo) {
  id_++;
  f_queue_.emplace(foo, id_);
  wake_up_ = true;
  cv_.notify_one();
  return id_;
}

void ThreadPool::Wait(uint64_t task_id) {
  while (done_tasks_ids_.back() != task_id) {
    std::this_thread::yield();
  }
}

void ThreadPool::WaitAll() {
  while (!f_queue_.empty()) {
    std::this_thread::yield();
  }
}