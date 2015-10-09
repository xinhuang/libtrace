#pragma once

#include "common.h"

#include <string>
#include <iosfwd>

namespace perf {

#ifndef NO_PERF

#ifndef ITT_NOIFY

class Task;
class Module;

#else

using Module = __itt_domain;
using Task = __itt_string_handle;

#endif // ITT_NOTIFY

PERFLIB_API Module *module(std::string Name);
PERFLIB_API Task *task(std::string Name);

PERFLIB_API void start(Module *M, Task *T);
PERFLIB_API void stop(Module *M);

PERFLIB_API void report(std::ostream &Out);
PERFLIB_API void reset();

#else // NO_PERF

inline Module *module(std::string) { return nullptr; }
inline Task *task(std::string) { return nullptr; }

inline void start(Module *, Task *) { return nullptr; }
inline void stop(Module *) { return nullptr; }

inline void report(std::ostream &Out) {}

#endif // NOPERF
}
