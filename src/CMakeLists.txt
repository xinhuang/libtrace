include_directories(${PROJECT_SOURCE_DIR}/src)

option(BUILD_SHARED_LIBTRACE "Build Shared libtrace" ON)

set(LIB_TYPE SHARED)
if (NOT BUILD_SHARED_LIBTRACE)
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
  libtrace.cpp
  libtrace_c.cpp
  Module.h
  Module.cpp
  Task.h
  types.h
  enumerable_thread_specific.h
)

endif ()

find_package(TBB REQUIRED)
include_directories(${TBB_INCLUDE_DIR})
target_link_libraries(libtrace optimized ${TBB_LIBRARIES})
target_link_libraries(libtrace debug ${TBB_DEBUG_LIBRARIES})

# Expose public API
target_include_directories(libtrace PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Install target (will install the library to specified CMAKE_INSTALL_PREFIX variable)
install(
  TARGETS libtrace
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  COMPONENT library
)

install(
  DIRECTORY "${PROJECT_SOURCE_DIR}/include/libtrace"
  DESTINATION include
  FILES_MATCHING PATTERN "*.*h"
)
