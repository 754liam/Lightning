#include "matcher.h"

Matcher::Matcher() {};

void Matcher::matchBidOrWait(OrderBook& order_book, LimitOrder limit_order){
    uint64_t price = limit_order.getPrice();
    if (!order_book.bidsEmpty() && order_book.bestBid() >= price){
        // to-do: when a bid exists that satisfies this limit sell, take it.
    }
}



