#include <benchmark/benchmark.h>

#include <perf/perf.h>

BENCHMARK_MAIN();

auto* m = perf::module("M");
auto* t = perf::task("T");

static void BM_perflib_start_stop(benchmark::State& state) {
  while (state.KeepRunning()) {
    perf::start(m, t);
    perf::stop(m);
  }
}

BENCHMARK(BM_perflib_start_stop)->Threads(1);
BENCHMARK(BM_perflib_start_stop)->Threads(2);
BENCHMARK(BM_perflib_start_stop)->Threads(3);
BENCHMARK(BM_perflib_start_stop)->Threads(4);
BENCHMARK(BM_perflib_start_stop)->Threads(5);
BENCHMARK(BM_perflib_start_stop)->Threads(6);
BENCHMARK(BM_perflib_start_stop)->Threads(7);
BENCHMARK(BM_perflib_start_stop)->Threads(8);
BENCHMARK(BM_perflib_start_stop)->Threads(9);
BENCHMARK(BM_perflib_start_stop)->Threads(10);
BENCHMARK(BM_perflib_start_stop)->Threads(11);
BENCHMARK(BM_perflib_start_stop)->Threads(12);
BENCHMARK(BM_perflib_start_stop)->Threads(13);
BENCHMARK(BM_perflib_start_stop)->Threads(14);
BENCHMARK(BM_perflib_start_stop)->Threads(15);
BENCHMARK(BM_perflib_start_stop)->Threads(16);
BENCHMARK(BM_perflib_start_stop)->Threads(17);
BENCHMARK(BM_perflib_start_stop)->Threads(18);
BENCHMARK(BM_perflib_start_stop)->Threads(19);
BENCHMARK(BM_perflib_start_stop)->Threads(20);

static void BM_increment_by_one(benchmark::State& state) {
  int i = 0;
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(++i);
  }
}

BENCHMARK(BM_increment_by_one);
