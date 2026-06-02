#include "ledger.h"

Account::Account(uint64_t user_id, uint64_t current_currency, uint64_t current_shares, uint64_t held_currency, uint64_t held_shares){
    this->user_id = user_id;
    this->current_currency = current_currency;
    this->current_shares = current_shares;
    this->held_currency = held_currency;
    this->held_shares = held_shares;
}


