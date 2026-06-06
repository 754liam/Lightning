#pragma once
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
    LimitOrder & frontAsk();
    LimitOrder & frontBid();
    void popAsk();
    void popBid();
    void askCleanup();
    void bidCleanup();
private:
    std::map<uint64_t, std::queue<LimitOrder>, std::greater<uint64_t>> bids;
    std::map<uint64_t, std::queue<LimitOrder>> asks;
    // asks: people wanting to sell; bids: people want to buy

    // a seller always wants the highest bid and a buyer always wants the lowest ask - hence the ordering in our keys
};

// TODO: rebuild the entire selling and buying logic along with the corresponding matcher support system. perhaps enable the selling/buying API through the matcher, not the order book. USE REFERENCES