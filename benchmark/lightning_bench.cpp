#include <benchmark/benchmark.h>

#include "../engine/command.h"
#include "../engine/command_handler.h"

static void BM_LimitMatch(benchmark::State& state) {
    for (auto _ : state) {
        CommandHandler handler;
        Command command;

        command.type = CommandType::CreateAccount;
        command.user_id = 1;
        command.shares = 5;
        command.currency = 500;
        handler.execute(command);

        command.type = CommandType::LimitBuy;
        command.user_id = 1;
        command.price = 4;
        command.shares = 3;
        handler.execute(command);

        command.type = CommandType::CreateAccount;
        command.user_id = 2;
        command.shares = 10;
        command.currency = 1000;
        handler.execute(command);

        command.type = CommandType::LimitSell;
        command.user_id = 2;
        command.price = 2;
        command.shares = 10;
        handler.execute(command);

        command.type = CommandType::GetAccount;
        command.user_id = 2;
        Response account = handler.execute(command);
        benchmark::DoNotOptimize(account.text);
    }
}
BENCHMARK(BM_LimitMatch);
