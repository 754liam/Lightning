#include <iostream>
#include "../engine/userinterface.h"

int main(){
    UserInterface u;
    u.createAccount(1, 5, 500);
    u.createLimitBuy(1, 4, 3);
    u.createAccount(2, 10, 1000);
    u.createLimitSell(2, 2, 10);
    Account user_two = u.checkAccount(2);
    if (user_two.get_currency() == 1006){
        std::cout << "Limit Sell across user_id's worked as expected." << std::endl;
    }
    return 0;
}