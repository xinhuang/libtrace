project(perflib_benchmarks)

add_subdirectory(benchmark)

include_directories(benchmark/include ../include)

add_executable(perflib_benchmarks perflib_benchmark.cpp)

target_link_libraries(perflib_benchmarks benchmark perflib)

add_test(NAME perflib_benchmarks COMMAND perflib_benchmarks)
