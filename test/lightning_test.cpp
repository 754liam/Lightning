#include <gtest/gtest.h>
#include "../engine/userinterface.h"

TEST(Lightning, LimitSellAcrossUsers) {
    UserInterface u;
    u.createAccount(1, 5, 500);
    u.createLimitBuy(1, 4, 3);
    u.createAccount(2, 10, 1000);
    u.createLimitSell(2, 2, 10);
    EXPECT_EQ(u.checkAccount(2).get_currency(), 1006);
}