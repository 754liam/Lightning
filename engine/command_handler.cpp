#include "command_handler.h"

Response CommandHandler::execute(const Command& command) {
    Response response = {false, "ERR unknown command"};

    try {
        if (command.type == CommandType::CreateAccount) {
            ledger_.create_account(command.user_id, command.currency, command.shares, 0, 0);
            response.ok = true;
            response.text = "OK";
            return response;
        }

        if (command.type == CommandType::LimitBuy) {
            LimitOrder order(command.user_id, command.shares, Side::Buy, command.price);
            if (!ledger_.LimitBuyRequest(order, ledger_.get_account(command.user_id))) {
                response.text = "ERR insufficient funds";
                return response;
            }
            response.ok = true;
            response.text = "OK";
            return response;
        }

        if (command.type == CommandType::LimitSell) {
            LimitOrder order(command.user_id, command.shares, Side::Sell, command.price);
            if (!ledger_.LimitSellRequest(order, ledger_.get_account(command.user_id))) {
                response.text = "ERR insufficient shares";
                return response;
            }
            response.ok = true;
            response.text = "OK";
            return response;
        }

        if (command.type == CommandType::MarketBuy) {
            Account& account = ledger_.get_account(command.user_id);
            uint64_t available = account.get_currency() - account.get_held_currency();
            MarketOrder order(command.user_id, command.shares, Side::Buy, available);
            if (!ledger_.MarketBuyRequest(order, account)) {
                response.text = "ERR order rejected";
                return response;
            }
            response.ok = true;
            response.text = "OK";
            return response;
        }

        if (command.type == CommandType::MarketSell) {
            Account& account = ledger_.get_account(command.user_id);
            uint64_t available = account.get_currency() - account.get_held_currency();
            MarketOrder order(command.user_id, command.shares, Side::Sell, available);
            if (!ledger_.MarketSellRequest(order, account)) {
                response.text = "ERR insufficient shares";
                return response;
            }
            response.ok = true;
            response.text = "OK";
            return response;
        }

        if (command.type == CommandType::GetAccount) {
            Account account = ledger_.get_account(command.user_id);
            response.ok = true;
            response.text = "OK currency=" + std::to_string(account.get_currency()) +
                            " shares=" + std::to_string(account.get_shares());
            return response;
        }
    } catch (...) {
        response.ok = false;
        response.text = "ERR unknown user";
        return response;
    }

    return response;
}
