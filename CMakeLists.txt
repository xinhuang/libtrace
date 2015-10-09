cmake_minimum_required(VERSION 2.8)

project(perflib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

set(Boost_USE_STATIC_LIBS ON)

include(CTest)

if (UNIX)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
elseif (MSVC)
  add_definitions(-DNOMINMAX)
endif ()

include_directories(include)

add_subdirectory(perf)
add_subdirectory(unittest)
