#include <gtest/gtest.h>

#include "../engine/command.h"
#include "../engine/command_handler.h"
#include "../engine/command_parser.h"

TEST(Lightning, LimitSellAcrossUsers) {
    CommandHandler handler;
    Command command;

    command.type = CommandType::CreateAccount;
    command.user_id = 1;
    command.shares = 5;
    command.currency = 500;
    EXPECT_TRUE(handler.execute(command).ok);

    command.type = CommandType::LimitBuy;
    command.user_id = 1;
    command.price = 4;
    command.shares = 3;
    EXPECT_TRUE(handler.execute(command).ok);

    command.type = CommandType::CreateAccount;
    command.user_id = 2;
    command.shares = 10;
    command.currency = 1000;
    EXPECT_TRUE(handler.execute(command).ok);

    command.type = CommandType::LimitSell;
    command.user_id = 2;
    command.price = 2;
    command.shares = 10;
    EXPECT_TRUE(handler.execute(command).ok);

    command.type = CommandType::GetAccount;
    command.user_id = 2;
    Response account = handler.execute(command);
    ASSERT_TRUE(account.ok);
    EXPECT_EQ(account.text, "OK currency=1006 shares=7");
}

TEST(Lightning, ParseAndExecute) {
    CommandHandler handler;
    Command command;

    ASSERT_TRUE(parse_command("CREATE_ACCOUNT 1 5 500", command));
    EXPECT_TRUE(handler.execute(command).ok);

    ASSERT_TRUE(parse_command("GET_ACCOUNT 1", command));
    Response account = handler.execute(command);
    EXPECT_EQ(account.text, "OK currency=500 shares=5");
}
