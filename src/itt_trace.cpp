#include "libtrace.h"

#include <stdexcept>

#include <ittnotify.h>

namespace trace {

Module *module(std::string Name) {
  return __itt_domain_create(Name.c_str());
}

Task *task(std::string Name) { return __itt_string_handle_create(Name.c_str()); }

void start(Module *M, Task *T) { __itt_task_begin(M, __itt_null, __itt_null, T); }
void stop(Module *M) { __itt_task_end(M); }

void report(std::ostream& Out) {
  throw std::runtime_error(
      "libtrace using ittnotify doesn't support report generation.");
}
}

#endif // ITT_NOTIFY
