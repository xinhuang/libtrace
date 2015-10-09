#pragma once

#include "common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef NO_PERF

#ifndef ITT_NOIFY

typedef void *PerfTask;
typedef void *PerfModule;

#else

typedef __itt_domain Module;
typedef __itt_string_handle Task;

#endif // ITT_NOTIFY

PERFLIB_API PerfModule *perf_module(const char *Name);
PERFLIB_API PerfTask *perf_task(const char *Name);

PERFLIB_API void perf_start(PerfModule *M, PerfTask *T);
PERFLIB_API void perf_stop(PerfModule *M);

PERFLIB_API void perf_report(char *Buf, size_t N);
PERFLIB_API void perf_reset();

#else // NO_PERF

inline Module *perf_module(const char * /*Name*/) { return nullptr; }
inline Task *perf_task(const char * /*Name*/) { return nullptr; }

inline void perf_start(PerfModule *, PerfTask *) { return nullptr; }
inline void perf_stop(PerfModule *) { return nullptr; }

inline void perf_report(char *& /*Buf*/, size_t /*N*/) {}
inline void perf_reset() {}

#endif // NOPERF

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
