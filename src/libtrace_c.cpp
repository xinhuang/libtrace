#include <libtrace/libtrace_c.h>

#include <libtrace/libtrace.h>

#include <sstream>
#include <cstring>

extern "C" {

LTModule *trace_module(const char *Name) {
  return reinterpret_cast<LTModule *>(trace::module(Name));
}

LTModule *trace_task(const char *Name) {
  return reinterpret_cast<LTTask *>(trace::task(Name));
}

void trace_start(LTModule *M, LTTask *T) {
  trace::start(reinterpret_cast<trace::Module *>(M),
              reinterpret_cast<trace::Task *>(T));
}

void trace_stop(LTModule *M) {
  trace::stop(reinterpret_cast<trace::Module *>(M));
}

void trace_report(char *Buf, size_t N) {
  std::stringstream SS;
  trace::report(SS);
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

void trace_reset() { trace::reset(); }

} // extern "C"
