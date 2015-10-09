project(perfTest)

include_directories(../perf/include)

add_executable(perfTest
  main.cpp
	perfTests.cpp
)

target_link_libraries(perfTest perfLib)

find_package(TBB REQUIRED)
include_directories(${TBB_INCLUDE_DIR})
target_link_libraries(perfTest optimized ${TBB_LIBRARIES})
target_link_libraries(perfTest debug ${TBB_DEBUG_LIBRARIES})

add_test(NAME perfTest COMMAND perfTest)
