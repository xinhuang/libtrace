#include <libtrace/libtrace_c.h>

#include <libtrace/libtrace.h>

#include <sstream>
#include <cstring>

extern "C" {

PerfModule *perf_module(const char *Name) {
  return reinterpret_cast<PerfModule *>(perf::module(Name));
}

PerfModule *perf_task(const char *Name) {
  return reinterpret_cast<PerfTask *>(perf::task(Name));
}

void perf_start(PerfModule *M, PerfTask *T) {
  perf::start(reinterpret_cast<perf::Module *>(M),
              reinterpret_cast<perf::Task *>(T));
}

void perf_stop(PerfModule *M) {
  perf::stop(reinterpret_cast<perf::Module *>(M));
}

void perf_report(char *Buf, size_t N) {
  std::stringstream SS;
  perf::report(SS);
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4996) // Disable warning for unsafe call to strncpy.
#endif                          // _MSC_VER
  std::strncpy(Buf, SS.str().c_str(), N - 1);
#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER
  Buf[N - 1] = 0;
}

void perf_reset() { perf::reset(); }

} // extern "C"
