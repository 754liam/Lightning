
#include "ordertypes.h"
#include "orderbook.h"

class Matcher{
    public:
        Matcher();
        void matchBidLimit(OrderBook & order_book, LimitOrder & limit_order);
        void matchAskLimit(OrderBook & order_book, LimitOrder & limit_order);
        void matchBidMarket(OrderBook & order_book, LimitOrder & limit_order);
        void matchAskMarket(OrderBook & order_book, LimitOrder & limit_order);
};