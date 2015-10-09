project(perfLib)

option(BUILD_SHARED_PERFLIB "Build Shared PerfLib" ON)

set(LIB_TYPE SHARED)
if (NOT BUILD_SHARED_PERFLIB)
  set(LIB_TYPE STATIC)
endif()

add_definitions(-DPERFLIB_EXPORTS)

if (USE_ITTNOTIFY)

add_library(perfLib STATIC
  include/perf/common.h
  include/perf/perf.h
  src/ittPerf.cpp
)

else ()

add_library(perfLib ${LIB_TYPE}
  include/perf/common.h
  include/perf/perf.h
  include/perf/perf_c.h
  src/perf.cpp
  src/perf_c.cpp
  src/Module.h
  src/Module.cpp
  src/Task.h
  src/types.h
  src/enumerable_thread_specific.h
)

endif ()

find_package(TBB REQUIRED)
include_directories(${TBB_INCLUDE_DIR})
target_link_libraries(perfLib optimized ${TBB_LIBRARIES})
target_link_libraries(perfLib debug ${TBB_DEBUG_LIBRARIES})
