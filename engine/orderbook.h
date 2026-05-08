#include <map>
#include <queue>
#include "ordertypes.h"

class OrderBook {
public:
    OrderBook();
    void pushBids(const LimitOrder& limit_order);
    void pushAsks(const LimitOrder& limit_order);
    uint64_t bestBid();
    uint64_t bestAsk();
    bool bidsEmpty();
    bool asksEmpty();

private:
    std::map<uint64_t, std::queue<LimitOrder>, std::greater<uint64_t>> bids;
    std::map<uint64_t, std::queue<LimitOrder>> asks;
};