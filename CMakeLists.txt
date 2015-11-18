cmake_minimum_required(VERSION 3.1)

project(perflib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

set(Boost_USE_STATIC_LIBS ON)

include(CTest)
include_directories(include)

if (UNIX)
elseif (MSVC)
  add_definitions(-DNOMINMAX)
endif ()

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(perf)
add_subdirectory(tests)
add_subdirectory(benchmarks)
