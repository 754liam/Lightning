#include <queue>
#include <iostream>
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
LimitOrder & OrderBook::frontAsk(){
    return OrderBook::asks.begin()->second.front();
}
LimitOrder & OrderBook::frontBid(){
    return OrderBook::bids.begin()->second.front();
}
void OrderBook::popAsk(){
    OrderBook::asks.begin()->second.pop();
}
void OrderBook::popBid(){
    OrderBook::bids.begin()->second.pop();
}
void OrderBook::askCleanup(){
    if (OrderBook::asksEmpty()){
        return;
    }
    while (!OrderBook::asksEmpty() && OrderBook::asks.begin()->second.empty()){
        OrderBook::asks.erase(asks.begin()->first);
    }
}
void OrderBook::bidCleanup(){
    if (OrderBook::bidsEmpty()){
        return;
    }
    while (!OrderBook::bidsEmpty() && OrderBook::bids.begin()->second.empty()){
        OrderBook::bids.erase(bids.begin()->first);
    }
}
