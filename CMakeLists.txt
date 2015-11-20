cmake_minimum_required(VERSION 3.1)

project(libtrace)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

set(Boost_USE_STATIC_LIBS ON)

include(CTest)

if (UNIX)
elseif (MSVC)
  add_definitions(-DNOMINMAX)
endif ()

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmarks)
