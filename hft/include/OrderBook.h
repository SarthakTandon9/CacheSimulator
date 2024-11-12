// hft/include/OrderBook.h
#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <map>
#include <string>
#include <fstream>
#include <cstdint> 

class OrderBook 
{
public:
    OrderBook(std::ofstream& traceFile);
    
    // Adds a limit order to the order book
    void addLimitOrder(bool isBuy, double price, int quantity);
    
    // Processes a market order, matching against existing orders
    void processMarketOrder(bool isBuy, int quantity);
    
    // (Optional) Prints the current state of the order book
    void printOrderBook();

private:
    // Buy orders: Price descending
    std::map<double, int, std::greater<double>> buyOrders;
    
    // Sell orders: Price ascending
    std::map<double, int, std::less<double>> sellOrders;
    
    // Reference to the trace file for logging memory accesses
    std::ofstream& trace;
    
    // Synthetic base addresses for data structures
    const uint64_t BUY_ORDER_BASE_ADDR = 0x10000000;
    const uint64_t SELL_ORDER_BASE_ADDR = 0x20000000;
    
    // Logs a memory access to the trace file
    void logAccess(uint64_t address);
};

#endif // ORDER_BOOK_H
