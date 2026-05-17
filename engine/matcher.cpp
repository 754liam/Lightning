#include "matcher.h"

Matcher::Matcher() {};

void Matcher::matchBidMarket(OrderBook & order_book, MarketOrder & market_order){
    if (order_book.asksEmpty()){
        return;
    }
    uint64_t share_count = market_order.getShareCount();
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

void Matcher::matchAskMarket(OrderBook & order_book, MarketOrder & market_order){
    if (order_book.bidsEmpty()){
        return;
    }
    uint64_t share_count = market_order.getShareCount();
    while (share_count > 0 && !order_book.bidsEmpty()){
        LimitOrder & bid = order_book.frontBid();
        if (bid.getShareCount() > share_count){
            bid.lowerShares(share_count);
            order_book.bidCleanup();
            break;
        }
        else if (bid.getShareCount() == share_count){
            order_book.popBid();
            order_book.bidCleanup();
            break;
        }
        else if (bid.getShareCount() < share_count){
            share_count -= bid.getShareCount();
            order_book.popBid();
        }
    }
}

void Matcher::matchAskLimit(OrderBook & order_book, LimitOrder & limit_order){
    // to-do: if ask can not be fulfilled fully, it must wait. thoughts: condition variables + threads?

}

void Matcher::matchBidLimit(OrderBook & order_book, LimitOrder & limit_order){
    
}


