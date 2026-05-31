#include <iostream>
#include "../engine/userinterface.h"

int main(){
    UserInterface u;
    OrderBook order_book = u.createOrderBook();
    LimitOrder limit_buy = u.createLimitBuy(16, 250);
    LimitOrder limit_sell = u.createLimitSell(20, 230);
    LimitOrder limit_buy_two = u.createLimitBuy(1, 232);
    u.createLimitBid(order_book, limit_buy);
    u.createLimitBid(order_book, limit_buy_two);
    u.createLimitAsk(order_book, limit_sell);

    if (limit_sell.getShareCount() == 3){
        std::cout << "Multi-level sell worked properly." << std::endl;
        return 0;
    }
    return 1;
}