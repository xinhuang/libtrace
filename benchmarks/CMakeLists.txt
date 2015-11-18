project(libtrace_benchmarks)

add_subdirectory(benchmark)

include_directories(benchmark/include ../include)

add_executable(libtrace_benchmarks libtrace_benchmarks.cpp)

target_link_libraries(libtrace_benchmarks benchmark libtrace)

add_test(NAME libtrace_benchmarks COMMAND libtrace_benchmarks)
