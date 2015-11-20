#pragma once

#include "common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef NO_LIBTRACE

#ifndef ITT_NOIFY

typedef void *LTTask;
typedef void *PerfModule;

#else

typedef __itt_domain Module;
typedef __itt_string_handle Task;

#endif // ITT_NOTIFY

LIBTRACE_API PerfModule *trace_module(const char *Name);
LIBTRACE_API LTTask *trace_task(const char *Name);

LIBTRACE_API void trace_start(PerfModule *M, LTTask *T);
LIBTRACE_API void trace_stop(PerfModule *M);

LIBTRACE_API void trace_report(char *Buf, size_t N);
LIBTRACE_API void trace_reset();

#else // NO_LIBTRACE

inline Module *trace_module(const char * /*Name*/) { return nullptr; }
inline Task *trace_task(const char * /*Name*/) { return nullptr; }

inline void trace_start(PerfModule *, LTTask *) { return nullptr; }
inline void trace_stop(PerfModule *) { return nullptr; }

inline void trace_report(char *& /*Buf*/, size_t /*N*/) {}
inline void trace_reset() {}

#endif // NO_LIBTRACE

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
