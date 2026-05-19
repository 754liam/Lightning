CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I engine
LDFLAGS  :=

ENGINE_SRCS := engine/matcher.cpp engine/orderbook.cpp

.PHONY: all test benchmark check clean

all: test

test: tests/run_tests
	./tests/run_tests

benchmark: tests/benchmark
	./tests/benchmark

check: test

tests/run_tests: $(ENGINE_SRCS) tests/functionality.cpp tests/test_common.hpp
	$(CXX) $(CXXFLAGS) -O2 $(LDFLAGS) -o $@ $(ENGINE_SRCS) tests/functionality.cpp

tests/benchmark: $(ENGINE_SRCS) tests/benchmark.cpp
	$(CXX) $(CXXFLAGS) -O2 $(LDFLAGS) -o $@ $(ENGINE_SRCS) tests/benchmark.cpp

clean:
	rm -f tests/run_tests tests/benchmark tests/benchmark_results.txt main
