#pragma once

#include "types.h"
#include "enumerable_thread_specific.h"

#include <atomic>
#include <string>
#include <unordered_map>
#include <sstream>
#include <iosfwd>
#include <thread>
#include <list>

#include <tbb/concurrent_hash_map.h>

namespace perf {

class Task;

class Module {
  struct TaskFrame {
    const perf::Task *Task;
    time_point StartTime;

    TaskFrame(const perf::Task &T, const time_point &TP) : Task(&T), StartTime(TP) {}
  };

  std::atomic<bool> Started;
  const std::string Name;
  enumerable_thread_specific<std::list<TaskFrame>> Frame;
  using task_duration_t = tbb::concurrent_hash_map<const Task *, duration>;
  enumerable_thread_specific<task_duration_t> TSTaskDuration;
  time_point StartTime;
  enumerable_thread_specific<time_point> StopTime;

public:
  Module(std::string &&Name) : Name(std::move(Name)), Started(false) {}
  void start(Task &Task, const time_point &Time);
  void stop();
  void report(std::ostream &Out) const;
  void reset();
};
}
