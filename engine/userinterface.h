#pragma once
#include "../manager/ledger.h"

class UserInterface{
    public:
        UserInterface();
        void createAccount(uint64_t user_id, uint64_t starting_shares, uint64_t starting_currency);
        void createLimitBuy(uint64_t user_id, uint64_t price, uint64_t shares);
        void createLimitSell(uint64_t user_id, uint64_t price, uint64_t shares);
        void createMarketSell(uint64_t user_id, uint64_t shares);
        void createMarketBuy(uint64_t user_id, uint64_t shares);
        Account checkAccount(uint64_t user_id);
    private:
        Ledger l;
        
};