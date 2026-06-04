#include "ledger.h"

Account::Account(uint64_t user_id, uint64_t current_currency, uint64_t current_shares, uint64_t held_currency, uint64_t held_shares){
    this->user_id = user_id;
    this->current_currency = current_currency;
    this->current_shares = current_shares;
    this->held_currency = held_currency;
    this->held_shares = held_shares;
}

uint64_t Account::get_currency(){
    return Account::current_currency;
}

uint64_t Account::get_shares(){
    return Account::current_shares;
}

uint64_t Account::get_held_currency(){
    return Account::held_currency;
}

uint64_t Account::get_held_shares(){
    return Account::held_shares;
}

void Account::update_currency(uint64_t new_currency){
    Account::current_currency = new_currency;
}

void Account::update_shares(uint64_t new_shares){
    Account::current_shares = new_shares;
}

void Account::hold_currency(uint64_t currency){
    Account::held_currency += currency;
}

void Account::hold_shares(uint64_t shares){
    Account::held_shares += shares;
}

Ledger::Ledger(){};

void Ledger::create_account(uint64_t user_id, uint64_t current_currency, uint64_t current_shares, uint64_t held_currency, uint64_t held_shares){
    Account a(user_id, current_currency, current_shares, held_currency, held_shares);
    Ledger::user_map[user_id] = a;
}

void Ledger::update_account_currency(uint64_t user_id, uint64_t new_currency){
    if (Ledger::user_map.find(user_id) != Ledger::user_map.end()){
        Account & a = Ledger::user_map[user_id];
        a.update_currency(new_currency);
    }
}

void Ledger::update_account_shares(uint64_t user_id, uint64_t new_shares){
    if (Ledger::user_map.find(user_id) != Ledger::user_map.end()){
        Account & a = Ledger::user_map[user_id];
        a.update_shares(new_shares);
    }
}

uint64_t Ledger::get_current_currency(uint64_t user_id){
    if (Ledger::user_map.find(user_id) != Ledger::user_map.end()){
        Account a = Ledger::user_map[user_id];
        return a.get_currency();
    } 
    return 0;
}

uint64_t Ledger::get_current_shares(uint64_t user_id){
    if (Ledger::user_map.find(user_id) != Ledger::user_map.end()){
        Account a = Ledger::user_map[user_id];
        return a.get_shares();
    } 
    return 0;
}

bool Ledger::LimitBuyRequest(LimitOrder & limit_order, Account & account){
    uint64_t proposed_price = limit_order.getPrice();
    uint64_t proposed_share_count = limit_order.getShareCount();
    if (!(account.get_currency() >= account.get_held_currency() + proposed_price && account.get_shares() >= account.get_held_shares() + proposed_share_count)){
        return false;
    }
    m.matchBidLimit(ob, limit_order);
    // idea: let the matcher return a vector of fill events such that we can rectify the account objs for all user_id's in a transaction. 
}






