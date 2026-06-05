#include <cstdint>
#include "../engine/orderbook.h"
#include "../engine/ordertypes.h"
#include "../engine/matcher.h"
#include <unordered_map>
#include <vector>
class Account{
    public:
        Account(uint64_t user_id, uint64_t current_currency, uint64_t current_shares, uint64_t held_currency, uint64_t held_shares);
        void update_currency(uint64_t new_currency);
        void update_shares(uint64_t new_currency);
        void hold_currency(uint64_t amount);
        void release_currency(uint64_t amount);
        void hold_shares(uint64_t amount);
        void release_shares(uint64_t amount);
        uint64_t get_currency();
        uint64_t get_shares();
        uint64_t get_held_currency();
        uint64_t get_held_shares();
    private:
        uint64_t user_id;
        uint64_t current_currency;
        uint64_t current_shares;
        uint64_t held_currency;
        uint64_t held_shares;
};

class Ledger{
    public:
        Ledger();
        void rectify_fillevents(const std::vector<FillEvent> & fill_events);
        void create_account(uint64_t user_id, uint64_t current_currency, uint64_t current_shares, uint64_t held_currency, uint64_t held_shares);
        void update_account_currency(uint64_t user_id, uint64_t new_currency);
        void update_account_shares(uint64_t user_id, uint64_t new_shares);
        uint64_t get_current_currency(uint64_t user_id);
        uint64_t get_current_shares(uint64_t user_id);
        bool LimitBuyRequest(LimitOrder & limit_order, Account & account);
        bool LimitSellRequest(LimitOrder & limit_order, Account & account);
        bool MarketBuyRequest(MarketOrder & market_order, Account & account);
        bool MarketSellRequest(MarketOrder & market_order, Account & account);
    private:
        std::unordered_map<uint64_t, Account> user_map; // map id's to accounts
        Matcher m;
        OrderBook ob;
};