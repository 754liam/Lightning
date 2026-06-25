#pragma once

#include <cstdint>
#include <string>

enum class CommandType {
    CreateAccount,
    LimitBuy,
    LimitSell,
    MarketBuy,
    MarketSell,
    GetAccount,
    Invalid
};

struct Command {
    CommandType type = CommandType::Invalid;
    uint64_t user_id = 0;
    uint64_t price = 0;
    uint64_t shares = 0;
    uint64_t currency = 0;
};

struct Response {
    bool ok;
    std::string text;
};
