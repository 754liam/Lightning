#include "userinterface.h"

UserInterface::UserInterface(){};

void UserInterface::createAccount(uint64_t user_id, uint64_t starting_shares, uint64_t starting_currency){
    l.create_account(user_id, starting_currency, starting_shares, 0, 0);
}

void UserInterface::createLimitBuy(uint64_t user_id, uint64_t price, uint64_t shares){
    LimitOrder limit_order(user_id, shares, Side::Buy, price);
    l.LimitBuyRequest(limit_order, l.get_account(user_id));
}

void UserInterface::createLimitSell(uint64_t user_id, uint64_t price, uint64_t shares){
    LimitOrder limit_order(user_id, shares, Side::Sell, price);
    l.LimitSellRequest(limit_order, l.get_account(user_id));
}

void UserInterface::createMarketSell(uint64_t user_id, uint64_t shares){
    MarketOrder market_order(user_id, shares, Side::Sell, l.get_account(user_id).get_currency() - l.get_account(user_id).get_held_currency());
    l.MarketSellRequest(market_order, l.get_account(user_id));
}

void UserInterface::createMarketBuy(uint64_t user_id, uint64_t shares){
    MarketOrder market_order(user_id, shares, Side::Buy, l.get_account(user_id).get_currency() - l.get_account(user_id).get_held_currency());
    l.MarketBuyRequest(market_order, l.get_account(user_id));  
}

Account UserInterface::checkAccount(uint64_t user_id){
    return l.get_account(user_id);
}


