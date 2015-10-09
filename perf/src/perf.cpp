#include "../include/perf/perf.h"

#include "Task.h"
#include "Module.h"
#include "types.h"

#include <tbb/concurrent_unordered_set.h>

#include <utility>
#include <cassert>
#include <set>
#include <sstream>

namespace perf {

class Perf {
  mutable bool Reporting = false;
  time_point LastStop = time_point::min();
  time_point FirstStart = time_point::max();
  tbb::concurrent_unordered_set<Module *> Modules;

  Perf(){};

public:
  static Perf *getInstance() {
    static Perf Instance;
    return &Instance;
  }

  void start(Module &M, Task &T) {
    assert(!Reporting);
    assert(Modules.find(&M) != Modules.end());
    const auto &Now = clock::now();
    if (FirstStart > Now)
      FirstStart = Now;
    M.start(T, Now);
  }
  void stop(Module &M) {
    assert(!Reporting);
    M.stop();
    LastStop = clock::now();
  }

  void report(std::ostream &Out) const {
    Reporting = true;
    Out << "Total Time: "
        << std::chrono::duration<double>(LastStop - FirstStart).count()
        << " seconds.\n";
    if (LastStop < FirstStart)
      Out << "Warning: You have dangling perf::start() calls.\n";
    for (auto M : Modules) {
      M->report(Out);
    }
    Reporting = false;
  }

  Module *createModule(std::string &&Name) {
    assert(!Reporting);
    auto M = new Module(std::move(Name));
    Modules.insert(M);
    return M;
  }

  void reset() {
    assert(!Reporting);
    LastStop = time_point::min();
    FirstStart = time_point::max();
    for_each(std::begin(Modules), std::end(Modules),
             [](Module *M) { M->reset(); });
  }
};

Module *module(std::string Name) {
  return Perf::getInstance()->createModule(std::move(Name));
}
void destroy(Module *M) { delete M; }

Task *task(std::string Name) { return new Task(std::move(Name)); }
void destroy(Task *T) { delete T; }

void start(Module *M, Task *T) { Perf::getInstance()->start(*M, *T); }
void stop(Module *M) { Perf::getInstance()->stop(*M); }

void report(std::ostream &Out) { Perf::getInstance()->report(Out); }

void reset() { Perf::getInstance()->reset(); }
}
