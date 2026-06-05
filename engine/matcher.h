#include <vector>
#include "ordertypes.h"
#include "orderbook.h"

class Matcher{
    public:
        Matcher();
        std::vector<FillEvent> matchBidLimit(OrderBook & order_book, LimitOrder & limit_order);
        std::vector<FillEvent> matchAskLimit(OrderBook & order_book, LimitOrder & limit_order);
        std::vector<FillEvent> matchBidMarket(OrderBook & order_book, MarketOrder & market_order);
        std::vector<FillEvent> matchAskMarket(OrderBook & order_book, MarketOrder & market_order);
};

struct FillEvent{
    uint64_t user_id_initiater;
    uint64_t user_id_receiver;
    Side side;
    uint64_t exchanged_shares;
    uint64_t exchanged_currency;
};