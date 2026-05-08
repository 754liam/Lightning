#include <queue>
#include "orderbook.h"

OrderBook::OrderBook() {}

void OrderBook::pushBids(const LimitOrder& limit_order){
    bids[limit_order.getPrice()].push(limit_order);
}
void OrderBook::pushAsks(const LimitOrder& limit_order){
    asks[limit_order.getPrice()].push(limit_order);
}
bool OrderBook::bidsEmpty(){
    return (OrderBook::bids.size() == 0);
}
bool OrderBook::asksEmpty(){
    return (OrderBook::asks.size() == 0);
}
uint64_t OrderBook::bestBid(){
    return OrderBook::bids.begin()->first;
}
uint64_t OrderBook::bestAsk(){
    return OrderBook::asks.begin()->first;
}