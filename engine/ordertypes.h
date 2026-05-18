#pragma once
#include <cstdint>

enum class Side{Buy, Sell};

class LimitOrder{
    public:
        LimitOrder(uint64_t share_count, Side side, uint64_t price, uint64_t id, uint64_t timestamp){
            this->share_count = share_count;
            this->price = price;
            this->side = side;
            this->id = id;
            this->timestamp = timestamp;
        }
        uint64_t getId()        const { return id; }
        Side     getSide()      const { return side; }
        uint64_t getShareCount()  const { return share_count; }
        uint64_t getPrice()     const { return price; }
        uint64_t getTimestamp() const { return timestamp; }
        void lowerShares(uint64_t shares) {this->share_count = this->share_count - shares;}
        void increaseShares(uint64_t shares) {this->share_count = this->share_count + shares;}
    private:
        uint64_t share_count;
        uint64_t price;
        uint64_t timestamp;
        Side side;
        uint64_t id;
};

class MarketOrder{
    public:
        MarketOrder(uint64_t share_count, Side side, uint64_t id, uint64_t timestamp){
            this->share_count = share_count;
            this->side = side;
            this->id = id;
            this->timestamp = timestamp;
        }
        uint64_t getId()        const { return id; }
        Side     getSide()      const { return side; }
        uint64_t getShareCount()  const { return share_count; }
        uint64_t getTimestamp() const { return timestamp; }
        void lowerShares(uint64_t shares) {this->share_count = this->share_count - shares;}
        void increaseShares(uint64_t shares) {this->share_count = this->share_count + shares;}
    private:
        uint64_t share_count;
        uint64_t timestamp;
        Side side;
        uint64_t id;
};