// hft/src/OrderBook.cpp
#include "OrderBook.h"
#include <iomanip>

OrderBook::OrderBook(std::ofstream& traceFile) : trace(traceFile) {}

void OrderBook::addLimitOrder(bool isBuy, double price, int quantity) 
{
    if(isBuy) {
        // Assign a synthetic address based on the price
        uint64_t address = BUY_ORDER_BASE_ADDR + static_cast<uint64_t>(price * 100);
        logAccess(address);
        
        // Access the buyOrders map
        auto it = buyOrders.find(price);
        if(it != buyOrders.end()) {
            it->second += quantity;
        }
        else {
            buyOrders[price] = quantity;
        }
    }
    else {
        // Assign a synthetic address based on the price
        uint64_t address = SELL_ORDER_BASE_ADDR + static_cast<uint64_t>(price * 100);
        logAccess(address);
        
        // Access the sellOrders map
        auto it = sellOrders.find(price);
        if(it != sellOrders.end()) {
            it->second += quantity;
        }
        else {
            sellOrders[price] = quantity;
        }
    }
}

void OrderBook::processMarketOrder(bool isBuy, int quantity) {
    if(isBuy) {
        // Assign a synthetic address for the best sell price
        uint64_t address = SELL_ORDER_BASE_ADDR; // Best sell is the lowest price
        logAccess(address);
        
        auto it = sellOrders.begin();
        while(it != sellOrders.end() && quantity > 0) {
            int executed = std::min(it->second, quantity);
            it->second -= executed;
            quantity -= executed;
            if(it->second == 0) {
                it = sellOrders.erase(it);
            }
            else {
                ++it;
            }
        }
    }
    else {
        // Assign a synthetic address for the best buy price
        uint64_t address = BUY_ORDER_BASE_ADDR; // Best buy is the highest price
        logAccess(address);
        
        auto it = buyOrders.begin();
        while(it != buyOrders.end() && quantity > 0) {
            int executed = std::min(it->second, quantity);
            it->second -= executed;
            quantity -= executed;
            if(it->second == 0) {
                it = buyOrders.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}

void OrderBook::printOrderBook() {
    // Optional: Implement if you want to visualize the order book
}

void OrderBook::logAccess(uint64_t address) {
    trace << "0x" << std::hex << std::uppercase << address << "\n";
}
