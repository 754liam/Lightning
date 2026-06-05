#include "matcher.h"



Matcher::Matcher() {};

void Matcher::matchBidMarket(OrderBook & order_book, MarketOrder & market_order){
    if (order_book.asksEmpty()){
        return;
    }
    while (!order_book.asksEmpty() && market_order.getShareCount() > 0){
        if (order_book.frontAsk().getShareCount() > market_order.getShareCount()){
            order_book.frontAsk().lowerShares(market_order.getShareCount());
            market_order.lowerShares(market_order.getShareCount());
        }
        else if (order_book.frontAsk().getShareCount() == market_order.getShareCount()){
            order_book.frontAsk().lowerShares(market_order.getShareCount());
            order_book.popAsk();
            market_order.lowerShares(market_order.getShareCount());
        }
        else if (order_book.frontAsk().getShareCount() < market_order.getShareCount()){
            market_order.lowerShares(order_book.frontAsk().getShareCount());
            order_book.frontAsk().lowerShares(order_book.frontAsk().getShareCount());
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
    while (!order_book.bidsEmpty() && market_order.getShareCount() > 0){
        if (order_book.frontBid().getShareCount() > market_order.getShareCount()){
            order_book.frontBid().lowerShares(market_order.getShareCount());
            market_order.lowerShares(market_order.getShareCount());
        }
        else if (market_order.getShareCount() == order_book.frontBid().getShareCount()){
            order_book.frontBid().lowerShares(order_book.frontBid().getShareCount());
            market_order.lowerShares(market_order.getShareCount());
            order_book.popBid();
        }
        else {
            market_order.lowerShares(order_book.frontBid().getShareCount());
            order_book.frontBid().lowerShares(order_book.frontBid().getShareCount());
            order_book.popBid();
        }
        order_book.bidCleanup();
    }
}

std::vector<FillEvent> Matcher::matchAskLimit(OrderBook & order_book, LimitOrder & limit_order){
    std::vector<FillEvent> fill_events;
    // to-do: if ask can not be fulfilled fully, it must wait.
    if (order_book.bidsEmpty()){
        order_book.pushAsks(limit_order);
        return;
    }
    while (!order_book.bidsEmpty() && order_book.frontBid().getPrice() >= limit_order.getPrice() && limit_order.getShareCount() > 0){
        uint64_t share_count = order_book.frontBid().getShareCount();
        if (share_count > limit_order.getShareCount()){
            order_book.frontBid().lowerShares(limit_order.getShareCount());
            limit_order.lowerShares(limit_order.getShareCount());
        }
        else if (share_count == limit_order.getShareCount()){
            order_book.frontBid().lowerShares(limit_order.getShareCount());
            order_book.popBid();
            limit_order.lowerShares(limit_order.getShareCount());
        }
        else {
            limit_order.lowerShares(order_book.frontBid().getShareCount());
            order_book.frontBid().lowerShares(share_count);
            order_book.popBid();
        }
        order_book.bidCleanup();
    }
    if (limit_order.getShareCount() > 0){
        order_book.pushAsks(limit_order);
    }

}

std::vector<FillEvent> Matcher::matchBidLimit(OrderBook & order_book, LimitOrder & limit_order){
    std::vector<FillEvent> fill_events;
    if (order_book.asksEmpty()){
        order_book.pushBids(limit_order);
        return fill_events;
    }
    while (!order_book.asksEmpty() && order_book.frontAsk().getPrice() <= limit_order.getPrice() && limit_order.getShareCount() > 0){
        uint64_t share_count = order_book.frontAsk().getShareCount();
        if (share_count > limit_order.getShareCount()){
            FillEvent fe = {.user_id_initiater = limit_order.getId(), .user_id_receiver = order_book.frontAsk().getId(), .side = Side::Buy, .exchanged_shares = limit_order.getShareCount(), .exchanged_currency = order_book.frontAsk().getPrice() * limit_order.getShareCount()};
            fill_events.push_back(fe);
            order_book.frontAsk().lowerShares(limit_order.getShareCount());
            limit_order.lowerShares(limit_order.getShareCount());
        }
        else if (share_count == limit_order.getShareCount()){
            FillEvent fe = {.user_id_initiater = limit_order.getId(), .user_id_receiver = order_book.frontAsk().getId(), .side = Side::Buy, .exchanged_shares = limit_order.getShareCount(), .exchanged_currency = order_book.frontAsk().getPrice() * limit_order.getShareCount()};
            fill_events.push_back(fe);
            order_book.frontAsk().lowerShares(share_count);
            order_book.popAsk();
            limit_order.lowerShares(share_count);
        }
        else{
            FillEvent fe = {.user_id_initiater = limit_order.getId(), .user_id_receiver = order_book.frontAsk().getId(), .side = Side::Buy, .exchanged_shares = order_book.frontAsk().getShareCount(), .exchanged_currency = order_book.frontAsk().getPrice() * order_book.frontAsk().getShareCount()};
            fill_events.push_back(fe);
            limit_order.lowerShares(share_count);
            order_book.frontAsk().lowerShares(share_count);
            order_book.popAsk();
        }
        order_book.askCleanup();
    }
    if (limit_order.getShareCount() > 0){
        order_book.pushBids(limit_order);
    }
    return fill_events;
}


