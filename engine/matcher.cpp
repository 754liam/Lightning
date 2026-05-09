#include "matcher.h"

Matcher::Matcher() {};

void Matcher::matchBidOrWait(OrderBook& order_book, LimitOrder limit_order){
    uint64_t price = limit_order.getPrice();
    while (!order_book.bidsEmpty() && order_book.bestBid() >= price){
        // to-do: when a bid exists that satisfies this limit sell, take it.
        order_book.sell(limit_order.getShareCount());
    }
    // if not found, just add to to the order book.
    order_book.pushAsks(limit_order);
}
void Matcher::matchAskOrWait(OrderBook& order_book, LimitOrder limit_order){
    uint64_t price = limit_order.getPrice();
    uint64_t share_count = limit_order.getShareCount();
    while (!order_book.asksEmpty() && order_book.bestAsk() <= price){
        order_book.buy(limit_order.getShareCount());
    }
    order_book.pushBids(limit_order);
}



