project(libtrace)

option(BUILD_SHARED_PERFLIB "Build Shared libtrace" ON)

set(LIB_TYPE SHARED)
if (NOT BUILD_SHARED_PERFLIB)
  set(LIB_TYPE STATIC)
endif()

add_definitions(-DPERFLIB_EXPORTS)

if (USE_ITTNOTIFY)

add_library(libtrace STATIC
  ../include/libtrace/common.h
  ../include/libtrace/libtrace.h
  src/ittPerf.cpp
)

else ()

add_library(libtrace ${LIB_TYPE}
  ../include/libtrace/common.h
  ../include/libtrace/libtrace.h
  ../include/libtrace/libtrace_c.h
  src/libtrace.cpp
  src/libtrace_c.cpp
  src/Module.h
  src/Module.cpp
  src/Task.h
  src/types.h
  src/enumerable_thread_specific.h
)

endif ()

find_package(TBB REQUIRED)
include_directories(${TBB_INCLUDE_DIR})
target_link_libraries(libtrace optimized ${TBB_LIBRARIES})
target_link_libraries(libtrace debug ${TBB_DEBUG_LIBRARIES})
