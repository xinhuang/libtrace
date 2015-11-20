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

PERFLIB_API PerfModule *trace_module(const char *Name);
PERFLIB_API PerfTask *trace_task(const char *Name);

PERFLIB_API void trace_start(PerfModule *M, PerfTask *T);
PERFLIB_API void trace_stop(PerfModule *M);

PERFLIB_API void trace_report(char *Buf, size_t N);
PERFLIB_API void trace_reset();

#else // NO_PERF

inline Module *trace_module(const char * /*Name*/) { return nullptr; }
inline Task *trace_task(const char * /*Name*/) { return nullptr; }

inline void trace_start(PerfModule *, PerfTask *) { return nullptr; }
inline void trace_stop(PerfModule *) { return nullptr; }

inline void trace_report(char *& /*Buf*/, size_t /*N*/) {}
inline void trace_reset() {}

#endif // NOPERF

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
