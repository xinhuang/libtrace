#include <yaffut.h>
using namespace yaffut;

#include <libtrace/libtrace_c.h>
#include <libtrace/libtrace.h>

#include <iostream>
using namespace std;

#include <tbb/tbb.h>
using namespace tbb;

PerfModule *M = perf_module("Module A");
PerfTask *A = perf_task("Task A");
PerfTask *B = perf_task("Task B");

void sleep_1_sec() { this_tbb_thread::sleep(tick_count::interval_t(1.)); }

struct LibtraceTest {
  LibtraceTest() { perf_reset(); }
};

struct NestedStart : Test<LibtraceTest, NestedStart> {
  NestedStart() {
    task_scheduler_init TSI(1);

    task_group Group;
    perf_start(M, A);
    Group.run_and_wait([]() {
      task_group Group;
      Group.run_and_wait([]() {
        perf_start(M, B);
        sleep_1_sec();
        perf_stop(M);
      });
    });
    perf_stop(M);

    char Buf[1024];
    perf_report(Buf, sizeof(Buf) / sizeof(Buf[0]));
    perf::report(std::cout);
  }
};

struct ReportForNothing : Test<LibtraceTest, ReportForNothing> {
  ReportForNothing() {
    std::stringstream SS;
    perf::report(SS);

    const auto &S = SS.str();
    check(S.find("Perf: No data collected.\n") != std::string::npos);
  }
};
