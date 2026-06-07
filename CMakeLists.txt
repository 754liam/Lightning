cmake_minimum_required(VERSION 3.20)
project(lightning LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-O3)

file(GLOB CORE engine/*.cpp manager/*.cpp)
add_library(lightning_core ${CORE})
target_include_directories(lightning_core PUBLIC engine manager)

add_executable(lightning test/lightning.cpp)
target_link_libraries(lightning PRIVATE lightning_core)

include(FetchContent)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
FetchContent_Declare(googlebenchmark URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip)
FetchContent_MakeAvailable(googletest googlebenchmark)

add_executable(lightning_tests test/lightning_test.cpp)
target_link_libraries(lightning_tests PRIVATE lightning_core GTest::gtest_main)

add_executable(lightning_benchmarks benchmark/lightning_bench.cpp)
target_link_libraries(lightning_benchmarks PRIVATE lightning_core benchmark::benchmark_main)