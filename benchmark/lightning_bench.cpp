#include <benchmark/benchmark.h>
#include "../engine/userinterface.h"

static void BM_LimitMatch(benchmark::State& state) {
    for (auto _ : state) {
        UserInterface u;
        u.createAccount(1, 5, 500);
        u.createLimitBuy(1, 4, 3);
        u.createAccount(2, 10, 1000);
        u.createLimitSell(2, 2, 10);
        benchmark::DoNotOptimize(u.checkAccount(2).get_currency());
    }
}
BENCHMARK(BM_LimitMatch);