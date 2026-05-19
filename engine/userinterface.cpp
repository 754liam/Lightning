#include "userinterface.h"

UserInterface::UserInterface(){};

OrderBook UserInterface::createOrderBook(){
    OrderBook order_book;
    return order_book;
}

LimitOrder UserInterface::createLimitSell(uint64_t share_count, uint64_t price){
    return LimitOrder(share_count, Side::Sell, price);
}

LimitOrder UserInterface::createLimitBuy(uint64_t share_count, uint64_t price){
    return LimitOrder(share_count, Side::Buy, price);
}

MarketOrder UserInterface::createMarketSell(uint64_t share_count){
    return MarketOrder(share_count, Side::Sell);
}

MarketOrder UserInterface::createMarketBuy(uint64_t share_count){
    return MarketOrder(share_count, Side::Buy);
}

void UserInterface::createLimitAsk(OrderBook & order_book, LimitOrder & limit_order){
    Matcher m;
    m.matchAskLimit(order_book, limit_order);
}

void UserInterface::createLimitBid(OrderBook & order_book, LimitOrder & limit_order){
    Matcher m;
    m.matchBidLimit(order_book, limit_order);
}

void UserInterface::createMarketAsk(OrderBook & order_book, MarketOrder & market_order){
    Matcher m;
    m.matchAskMarket(order_book, market_order);
}

void UserInterface::createMarketBid(OrderBook & order_book, MarketOrder & market_order){
    Matcher m;
    m.matchBidMarket(order_book, market_order);
}

