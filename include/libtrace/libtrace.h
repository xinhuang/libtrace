#pragma once

#include "common.h"

#include <string>
#include <iosfwd>

namespace trace {

#ifndef NO_LIBTRACE

#ifndef ITT_NOIFY

class Task;
class Module;

#else

using Module = __itt_domain;
using Task = __itt_string_handle;

#endif // ITT_NOTIFY

LIBTRACE_API Module *module(std::string Name);
LIBTRACE_API Task *task(std::string Name);

LIBTRACE_API void start(Module *M, Task *T);
LIBTRACE_API void stop(Module *M);

LIBTRACE_API void report(std::ostream &Out);
LIBTRACE_API void reset();

#else // NO_LIBTRACE

inline Module *module(std::string) { return nullptr; }
inline Task *task(std::string) { return nullptr; }

inline void start(Module *, Task *) { return nullptr; }
inline void stop(Module *) { return nullptr; }

inline void report(std::ostream &Out) {}

#endif // NO_LIBTRACE
}
