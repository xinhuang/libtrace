# libtrace

libtrace provides fast instrumentation and tracing API to generate trace data during execution for C/C++.

[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/xinhuang/libtrace?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
Travis CI: [![Build Status](https://travis-ci.org/xinhuang/libtrace.svg)](https://travis-ci.org/xinhuang/libtrace)
AppVeyor CI: [![Build Status](https://ci.appveyor.com/api/projects/status/qa62sqkufd5fey0y?svg=true)](https://ci.appveyor.com/project/xinhuang/libtrace)

## Example

```
auto *M = trace::module("Module A");
auto *A = trace::task("Task A");
auto *B = trace::task("Task B");

using namespace tbb;
task_scheduler_init TSI(1);

task_group Group;

trace::start(M, A);
Group.run_and_wait([]() {
  task_group Group;
  Group.run_and_wait([]() {
    trace::start(M, B);
    // Busy processing data
    trace::stop(M);
  });
});
trace::stop(M);

std::ofstream PerfReport("./PerfReport.txt");
trace::report(PerfReport);
```

*Output*
```
Total Time: 1.00055 seconds.
	Module Module A: 1.00054 seconds.
		Task Task A : 1.00054 seconds.
		Task Task B : 1.00019 seconds.
```

*libtrace also provides equivalent C interfaces.*

## Performance of libtrace

Measured by google/benchmark  

```
Run on (1 X 3292 MHz CPU )
11/18/15 12:21:43
Benchmark                          Time(ns)    CPU(ns) Iterations
-----------------------------------------------------------------
BM_libtrace_start_stop/threads:1         172        171    3739292
BM_libtrace_start_stop/threads:2         102        200    3205108
BM_libtrace_start_stop/threads:3          78        234    3000000
BM_libtrace_start_stop/threads:4          82        299    2243576
BM_libtrace_start_stop/threads:5          70        298    1725825
BM_libtrace_start_stop/threads:6          54        313    2243574
BM_libtrace_start_stop/threads:7          49        322    2710421
BM_libtrace_start_stop/threads:8          45        382    2243576
BM_libtrace_start_stop/threads:9          55        322    2516796
BM_libtrace_start_stop/threads:10         98        419    1602550
BM_libtrace_start_stop/threads:11         64        435    1542453
BM_libtrace_start_stop/threads:12         64        347    2341128
BM_libtrace_start_stop/threads:13         66        368    1822899
BM_libtrace_start_stop/threads:14         56        379    2512804
BM_libtrace_start_stop/threads:15         58        441    1875885
BM_libtrace_start_stop/threads:16         57        361    2334448
BM_libtrace_start_stop/threads:17         52        321    1700000
BM_libtrace_start_stop/threads:18         53        321    1800000
BM_libtrace_start_stop/threads:19         58        302    1705117
BM_libtrace_start_stop/threads:20         52        344    2130640
BM_increment_by_one                       2          2  407922793
```

## How to Build

### Set Up Dependencies

* TBB  

1. Download TBB distribution from https://www.threadingbuildingblocks.org/  
2. Build TBB from source the distribution doesn't target to your compiler  

### Build

* Linux

```  
git clone git@github.com/xinhuang/libtrace.git
cd libtrace
mkdir build
cd build
cmake ..
make
make test                             # Run tests
```

* Windows

```
git clone git@github.com/xinhuang/libtrace.git
cd libtrace
mkdir build
cd build
cmake .. -G "Visual Studio 14 2015 Win64"
msbuild libtrace.sln /m
msbuild RUN_TESTS.vcxproj                  # Run tests
```

* x86-64

If you prefer x86-64,
*For Windows*, use -G "Visual Studio 14 2015".


### Toubleshooting

*If TBB is not found*,  
Add `-DTBBROOT=<your TBB root path` and set environment variable `TBB_ARCH_PLATFORM`
match your platform and compiler. For example, `ia32/vc14` is for VC14 on x86, `intel64/gcc4.8` for gcc 4.8 on x86-64.
You can also get these variables set by running `<TBBROOT>/tbbvars.bat <platform> <compiler>`.

## Coding Style

This project follows the [LLVM Coding Standards](http://llvm.org/docs/CodingStandards.html).
