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

// to do: increase shares of buyer and do the same when buying
void OrderBook::sell(uint64_t quantity){
    uint64_t temp = quantity;
    uint64_t made = 0;
    while (temp > 0){
        if (OrderBook::bidsEmpty()){
            return;
        }
        if (OrderBook::bids.begin()->second.empty()){
            OrderBook::bids.erase(OrderBook::bids.begin());
            break;
        }
        auto in_question = OrderBook::bids.begin()->second.front();
        if (in_question.getShareCount() < temp){
            temp -= in_question.getShareCount();
            made += in_question.getPrice() * in_question.getShareCount();
            OrderBook::bids.begin()->second.pop();
        }
        else if (in_question.getShareCount() > temp){
            made += in_question.getPrice() * temp;
            in_question.increaseShares(temp);
            temp = 0;
        }
        else if (in_question.getShareCount() == temp){
            made += in_question.getPrice() * temp;
            OrderBook::bids.begin()->second.pop();
            temp = 0;
        }
    }
    std::cout << "You sold: " << (quantity - temp) << " shares and made: " << made << " dollars." << std::endl; // placeholder for now. note that in implementation (matcher), this'll have to be a loop over bestBid and bidsEmpty
}
void OrderBook::buy(uint64_t quantity){
    // to do: implement buy via similar queue traversal logic
    uint64_t temp = 0;
    uint64_t bought = 0;
    while (temp < quantity){
        if (OrderBook::asksEmpty()){
            return;
        }
        if (OrderBook::asks.begin()->second.empty()){
                OrderBook::asks.erase(OrderBook::asks.begin());
                continue;
        }
        auto in_question = OrderBook::asks.begin()->second.front();
        if (in_question.getShareCount() > quantity){
            temp = quantity;
            bought += temp * in_question.getPrice();
            in_question.lowerShares(temp);
        }
        else if (in_question.getShareCount() == quantity){
            temp = quantity;
            bought += temp * in_question.getPrice();
            OrderBook::asks.begin()->second.pop();
        }
        else if (in_question.getShareCount() < quantity){
            temp += in_question.getShareCount();
            bought += temp * in_question.getPrice();
            OrderBook::asks.begin()->second.pop();
        }
    }
    std::cout << "You bought: " << temp << " shares and spent: " << bought << " dollars." << std::endl;
}
bool OrderBook::bidsEmpty(){
    return (OrderBook::bids.size() == 0);
}
bool OrderBook::asksEmpty(){
    return (OrderBook::asks.size() == 0);
}
uint64_t OrderBook::bestBid(){
    return OrderBook::bids.begin()->first; // use to see if you're able to make the purchase with a limit sell - loop in implementation
}
uint64_t OrderBook::bestAsk(){
    return OrderBook::asks.begin()->first;
}