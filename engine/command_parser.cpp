#include "command_parser.h"

#include <sstream>
#include <vector>

static bool read_u64(const std::string& token, uint64_t& out) {
    try {
        size_t pos = 0;
        unsigned long long value = std::stoull(token, &pos);
        if (pos != token.size()) {
            return false;
        }
        out = value;
        return true;
    } catch (...) {
        return false;
    }
}

bool parse_command(const std::string& line, Command& command) {
    command.type = CommandType::Invalid;

    std::istringstream stream(line);
    std::vector<std::string> parts;
    std::string token;
    while (stream >> token) {
        parts.push_back(token);
    }
    if (parts.empty()) {
        return false;
    }

    uint64_t a = 0;
    uint64_t b = 0;
    uint64_t c = 0;

    if (parts[0] == "CREATE_ACCOUNT" && parts.size() == 4 &&
        read_u64(parts[1], a) && read_u64(parts[2], b) && read_u64(parts[3], c)) {
        command.type = CommandType::CreateAccount;
        command.user_id = a;
        command.shares = b;
        command.currency = c;
        return true;
    }

    if (parts[0] == "LIMIT_BUY" && parts.size() == 4 &&
        read_u64(parts[1], a) && read_u64(parts[2], b) && read_u64(parts[3], c)) {
        command.type = CommandType::LimitBuy;
        command.user_id = a;
        command.price = b;
        command.shares = c;
        return true;
    }

    if (parts[0] == "LIMIT_SELL" && parts.size() == 4 &&
        read_u64(parts[1], a) && read_u64(parts[2], b) && read_u64(parts[3], c)) {
        command.type = CommandType::LimitSell;
        command.user_id = a;
        command.price = b;
        command.shares = c;
        return true;
    }

    if (parts[0] == "MARKET_BUY" && parts.size() == 3 &&
        read_u64(parts[1], a) && read_u64(parts[2], b)) {
        command.type = CommandType::MarketBuy;
        command.user_id = a;
        command.shares = b;
        return true;
    }

    if (parts[0] == "MARKET_SELL" && parts.size() == 3 &&
        read_u64(parts[1], a) && read_u64(parts[2], b)) {
        command.type = CommandType::MarketSell;
        command.user_id = a;
        command.shares = b;
        return true;
    }

    if (parts[0] == "GET_ACCOUNT" && parts.size() == 2 && read_u64(parts[1], a)) {
        command.type = CommandType::GetAccount;
        command.user_id = a;
        return true;
    }

    return false;
}
