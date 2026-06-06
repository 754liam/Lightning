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

void Account::release_currency(uint64_t currency){
    Account::held_currency -= currency;
}


void Account::hold_shares(uint64_t shares){
    Account::held_shares += shares;
}

void Account::release_shares(uint64_t shares){
    Account::held_shares -= shares;
}

Ledger::Ledger(){};

void Ledger::rectify_fillevents(const std::vector<FillEvent> & fill_events){
    for (const auto & event : fill_events){
        if (event.side == Side::Buy){
            uint64_t initiater_id = event.user_id_initiater;
            Ledger::user_map.at(initiater_id).update_currency(Ledger::user_map.at(initiater_id).get_currency() - event.exchanged_currency);
            Ledger::user_map.at(initiater_id).release_currency(event.exchanged_currency);
            Ledger::user_map.at(initiater_id).update_shares(Ledger::user_map.at(initiater_id).get_shares() + event.exchanged_shares);
            
            uint64_t receiver_id = event.user_id_receiver;
            Ledger::user_map.at(receiver_id).release_shares(event.exchanged_shares);
            Ledger::user_map.at(receiver_id).update_shares(Ledger::user_map.at(receiver_id).get_shares() - event.exchanged_shares);
            Ledger::user_map.at(receiver_id).update_currency(Ledger::user_map.at(receiver_id).get_currency() + event.exchanged_currency);
        }
        else if (event.side == Side::Sell){
            uint64_t receiver_id = event.user_id_receiver;
            Ledger::user_map.at(receiver_id).update_currency(Ledger::user_map.at(receiver_id).get_currency() - event.exchanged_currency);
            Ledger::user_map.at(receiver_id).release_currency(event.exchanged_currency);
            Ledger::user_map.at(receiver_id).update_shares(Ledger::user_map.at(receiver_id).get_shares() + event.exchanged_shares);

            uint64_t initiater_id = event.user_id_initiater;
            Ledger::user_map.at(initiater_id).release_shares(event.exchanged_shares);
            Ledger::user_map.at(initiater_id).update_shares(Ledger::user_map.at(initiater_id).get_shares() - event.exchanged_shares);
            Ledger::user_map.at(initiater_id).update_currency(Ledger::user_map.at(initiater_id).get_currency() + event.exchanged_currency);
        }

    // idea: let the matcher return a vector of fill events such that we can rectify the account objs for all user_id's in a transaction. 
}
}

void Ledger::create_account(uint64_t user_id, uint64_t current_currency, uint64_t current_shares, uint64_t held_currency, uint64_t held_shares){
    Ledger::user_map.emplace(user_id, Account(user_id, current_currency, current_shares, held_currency, held_shares));
}

Account & Ledger::get_account(uint64_t user_id){
    return user_map.at(user_id);
    
}

void Ledger::update_account_currency(uint64_t user_id, uint64_t new_currency){
    Account & a = Ledger::user_map.at(user_id);
    a.update_currency(new_currency);
}

void Ledger::update_account_shares(uint64_t user_id, uint64_t new_shares){
    Account & a = Ledger::user_map.at(user_id);
    a.update_shares(new_shares);
}

uint64_t Ledger::get_current_currency(uint64_t user_id){
    Account a = Ledger::user_map.at(user_id);
    return a.get_currency(); 
}

uint64_t Ledger::get_current_shares(uint64_t user_id){
    Account a = Ledger::user_map.at(user_id);
    return a.get_shares();
}

bool Ledger::LimitBuyRequest(LimitOrder & limit_order, Account & account){
    uint64_t proposed_price = limit_order.getPrice() * limit_order.getShareCount();
    if (!(account.get_currency() >= account.get_held_currency() + proposed_price)){
        return false;
    }
    account.hold_currency(proposed_price);
    std::vector<FillEvent> fill_events = m.matchBidLimit(ob, limit_order);
    rectify_fillevents(fill_events);
    return true;
}

bool Ledger::LimitSellRequest(LimitOrder & limit_order, Account & account){
    uint64_t proposed_shares = limit_order.getShareCount();
    if (!(account.get_shares() >= account.get_held_shares() + proposed_shares)){
        return false;
    }
    account.hold_shares(proposed_shares);
    std::vector<FillEvent> fill_events = m.matchAskLimit(ob, limit_order);
    rectify_fillevents(fill_events);
    return true;
}

bool Ledger::MarketBuyRequest(MarketOrder & market_order, Account & account){
    if (!(account.get_currency() == account.get_held_currency() + market_order.getTotalCurrency())){
        return false;
    }
    std::vector<FillEvent> fill_events = m.matchBidMarket(ob, market_order);
    rectify_fillevents(fill_events);
    return true;
}

bool Ledger::MarketSellRequest(MarketOrder & market_order, Account & account){
    if (!(account.get_shares() >= account.get_held_shares() + market_order.getShareCount())){
        return false;
    }
    std::vector<FillEvent> fill_events = m.matchAskMarket(ob, market_order);
    rectify_fillevents(fill_events);
    return true;
}







