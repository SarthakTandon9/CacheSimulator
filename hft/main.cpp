// hft/main.cpp
#include "OrderBook.h"
#include <fstream>
#include <random>
#include <iostream>

int main(int argc, char* argv[]) {
    // Default parameters
    int num_operations = 1000000; // Number of operations to simulate
    std::string trace_file = "data/trace.txt"; // Output trace file
    
    // Parse command-line arguments (optional)
    if(argc >= 2) {
        num_operations = std::stoi(argv[1]);
    }
    if(argc >= 3) {
        trace_file = argv[2];
    }
    
    // Open the trace file
    std::ofstream trace(trace_file);
    if(!trace.is_open()) {
        std::cerr << "Error: Unable to open trace file: " << trace_file << "\n";
        return 1;
    }
    
    OrderBook orderBook(trace);
    
    // Initialize random number generators
    std::mt19937 rng(42); // Fixed seed for reproducibility
    std::uniform_real_distribution<double> price_dist(1.0, 200000.0); // Prices between $100 and $200
    std::uniform_int_distribution<int> quantity_dist(1, 100000); // Quantities between 1 and 100
    std::uniform_int_distribution<int> operation_dist(1, 100); // For operation selection
    
    for(int i = 0; i < num_operations; ++i) {
        int op = operation_dist(rng);
        if(op <= 60) { // 60% chance to add a limit order
            bool isBuy = (op <= 30); // 30% buy, 30% sell
            double price = std::round(price_dist(rng) * 100.0) / 100.0; // Round to 2 decimal places
            int quantity = quantity_dist(rng);
            orderBook.addLimitOrder(isBuy, price, quantity);
        }
        else { // 40% chance to process a market order
            bool isBuy = (op <= 80); // 40% buy, 60% sell
            int quantity = quantity_dist(rng);
            orderBook.processMarketOrder(isBuy, quantity);
        }
        
        // Optional: Print progress at 10% intervals
        if((i+1) % (num_operations / 10) == 0) {
            std::cout << "Processed " << (i+1) << " / " << num_operations << " operations.\n";
        }
    }
    
    trace.close();
    std::cout << "HFT simulation complete. Trace file generated at: " << trace_file << "\n";
    
    return 0;
}
