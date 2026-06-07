#pragma once
#include <cstdint>

enum class Side{Buy, Sell};

class LimitOrder{
    public:
        LimitOrder(uint64_t user_id, uint64_t share_count, Side side, uint64_t price){
            this->share_count = share_count;
            this->price = price;
            this->side = side;
            this->user_id = user_id;
        }
        Side     getSide()      const { return side; }
        uint64_t getShareCount()  const { return share_count; }
        uint64_t getPrice()     const { return price; }
        uint64_t getId() const { return user_id;}
        void lowerShares(uint64_t shares) {this->share_count = this->share_count - shares;}
        void increaseShares(uint64_t shares) {this->share_count = this->share_count + shares;}
    private:
        uint64_t share_count;
        uint64_t price;
        Side side;
        uint64_t user_id;
};

class MarketOrder{
    public:
        MarketOrder(uint64_t user_id, uint64_t share_count, Side side, uint64_t total_currency){
            this->share_count = share_count;
            this->side = side;
            this->total_currency = total_currency;
            this->user_id = user_id;
        }
        Side     getSide()      const { return side; }
        uint64_t getShareCount()  const { return share_count; }
        uint64_t getId() const { return user_id;}
        uint64_t getTotalCurrency() const { return total_currency; }
        void lowerTotalCurrency(uint64_t currency) { this->total_currency -= currency; }
        void lowerShares(uint64_t shares) {this->share_count = this->share_count - shares;}
        void increaseShares(uint64_t shares) {this->share_count = this->share_count + shares;}
    private:
        uint64_t share_count;
        Side side;
        uint64_t user_id;
        uint64_t total_currency;
};