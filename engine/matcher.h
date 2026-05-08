
#include "ordertypes.h"
#include "orderbook.h"

class Matcher{
    public:
        Matcher();
        void matchBidOrWait(OrderBook & order_book, LimitOrder limit_order);
        void matchAskOrWait(OrderBook & order_book, LimitOrder limit_order);
};