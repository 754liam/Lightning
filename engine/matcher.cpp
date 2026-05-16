#include "matcher.h"

Matcher::Matcher() {};

void Matcher::matchBidMarket(OrderBook & order_book, LimitOrder & limit_order){
    if (order_book.asksEmpty()){
        return;
    }
    uint64_t share_count = limit_order.getShareCount();
    while (share_count > 0 && !order_book.asksEmpty()){
        LimitOrder & ask = order_book.frontAsk();
        if (ask.getShareCount() > share_count){
            ask.lowerShares(share_count);
            order_book.askCleanup();
            break;
        }
        else if (ask.getShareCount() == share_count){
            order_book.popAsk();
            order_book.askCleanup();
            break;
        }
        else if (ask.getShareCount() < share_count){
            share_count -= ask.getShareCount();
            order_book.popAsk();
        }
        order_book.askCleanup();
    }
    // cases: either you went all the way through, or, you did a partial fill. in either way, this market order could be considered complete

}



