#include "matcher.h"

class UserInterface{
    public:
        UserInterface();
        OrderBook createOrderBook();
        LimitOrder createLimitSell(uint64_t share_count, uint64_t price);
        LimitOrder createLimitBuy(uint64_t share_count, uint64_t price);
        MarketOrder createMarketSell(uint64_t share_count);
        MarketOrder createMarketBuy(uint64_t share_count);
        void createLimitBid(OrderBook & order_book, LimitOrder & limit_order);
        void createLimitAsk(OrderBook & order_book, LimitOrder & limit_order);
        void createMarketAsk(OrderBook & order_book, MarketOrder & limit_order);
        void createMarketBid(OrderBook & order_book, MarketOrder & limit_order);
};