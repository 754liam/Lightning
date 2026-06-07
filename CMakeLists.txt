cmake_minimum_required(VERSION 3.20)
project(lightning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    engine/*.cpp
    manager/*.cpp
)

add_executable(lightning
    ${SOURCES}
    test/main.cpp
)

target_include_directories(lightning PRIVATE engine/ manager/)
target_compile_options(lightning PRIVATE -Wall -Wextra)

# Google Test and Benchmark
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_Declare(
    googlebenchmark
    URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
)

FetchContent_MakeAvailable(googletest googlebenchmark)