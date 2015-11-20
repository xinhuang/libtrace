#include <yaffut.h>
using namespace yaffut;

#include <libtrace/libtrace_c.h>
#include <libtrace/libtrace.h>

#include <iostream>
using namespace std;

#include <tbb/tbb.h>
using namespace tbb;

LTModule *M = trace_module("Module A");
LTTask *A = trace_task("Task A");
LTTask *B = trace_task("Task B");

void sleep_1_sec() { this_tbb_thread::sleep(tick_count::interval_t(1.)); }

struct LibtraceTest {
  LibtraceTest() { trace_reset(); }
};

struct NestedStart : Test<LibtraceTest, NestedStart> {
  NestedStart() {
    task_scheduler_init TSI(1);

    task_group Group;
    trace_start(M, A);
    Group.run_and_wait([]() {
      task_group Group;
      Group.run_and_wait([]() {
        trace_start(M, B);
        sleep_1_sec();
        trace_stop(M);
      });
    });
    trace_stop(M);

    char Buf[1024];
    trace_report(Buf, sizeof(Buf) / sizeof(Buf[0]));
  }
};

struct ReportForNothing : Test<LibtraceTest, ReportForNothing> {
  ReportForNothing() {
    std::stringstream SS;
	trace::report(SS);

    const auto &S = SS.str();
    check(S.find("libtrace: No data collected.\n") != std::string::npos);
  }
};
