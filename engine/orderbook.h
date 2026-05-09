#include <map>
#include <queue>
#include "ordertypes.h"

class OrderBook {
public:
    OrderBook();
    void pushBids(const LimitOrder& limit_order);
    void pushAsks(const LimitOrder& limit_order);
    void sell(uint64_t quantity);
    void buy(uint64_t quantity);
    uint64_t bestBid();
    uint64_t bestAsk();
    bool bidsEmpty();
    bool asksEmpty();

private:
    std::map<uint64_t, std::queue<LimitOrder>, std::greater<uint64_t>> bids;
    std::map<uint64_t, std::queue<LimitOrder>> asks;
    // asks: people wanting to sell; bids: people want to buy

    // a seller always wants the highest bid and a buyer always wants the lowest ask - hence the ordering in our keys
};