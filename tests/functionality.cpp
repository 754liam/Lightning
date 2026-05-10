#include <iostream>
#include <chrono>
#include "matcher.h"


int main(){
    OrderBook my_order_book;
    uint64_t time = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    Matcher matcher;
    LimitOrder my_limit_sell(10, Side::Sell, 10, 2, time);
    matcher.matchBidOrWait(my_order_book, my_limit_sell);
    LimitOrder my_limit_order(10, Side::Buy, 10, 1, time);
    matcher.matchAskOrWait(my_order_book, my_limit_order);
    
    return EXIT_SUCCESS;
}