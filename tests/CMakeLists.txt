project(libtrace_tests)

include_directories(include)

add_executable(libtrace_tests
  main.cpp
	libtrace_tests.cpp
)

target_link_libraries(libtrace_tests libtrace)

find_package(TBB REQUIRED)
include_directories(${TBB_INCLUDE_DIR})
target_link_libraries(libtrace_tests optimized ${TBB_LIBRARIES})
target_link_libraries(libtrace_tests debug ${TBB_DEBUG_LIBRARIES})

add_test(NAME libtrace_tests COMMAND libtrace_tests)
