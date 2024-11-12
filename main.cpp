// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Cache.h"
#include "ReplacementPolicyTypes.h"

int main(int argc, char* argv[]) {
    if(argc < 5) {
        std::cerr << "Usage: " << argv[0] << " <cache_size> <block_size> <associativity> <replacement_policy> <trace_file>\n";
        std::cerr << "Replacement policies: LRU, FIFO, Random\n";
        return 1;
    }
    
    // Parse command-line arguments
    size_t cacheSize = std::stoul(argv[1]);       // in bytes
    size_t blockSize = std::stoul(argv[2]);       // in bytes
    int associativity = std::stoi(argv[3]);
    std::string policyStr = argv[4];
    std::string traceFile = argv[5];
    
    ReplacementPolicyType policyType;
    if(policyStr == "LRU") {
        policyType = ReplacementPolicyType::LRU;
    }
    else if(policyStr == "FIFO") {
        policyType = ReplacementPolicyType::FIFO;
    }
    else if(policyStr == "Random") {
        policyType = ReplacementPolicyType::Random;
    }
    else {
        std::cerr << "Unknown replacement policy: " << policyStr << "\n";
        return 1;
    }
    
    // Configure cache
    CacheConfig config;
    config.cacheSize = cacheSize;
    config.blockSize = blockSize;
    config.associativity = associativity;
    config.policyType = policyType;
    
    Cache cache(config);
    
    // Open trace file
    std::ifstream infile(traceFile);
    if(!infile.is_open()) {
        std::cerr << "Failed to open trace file: " << traceFile << "\n";
        return 1;
    }
    
    std::string line;
    size_t totalAccesses = 0;
    size_t hitCount = 0;
    size_t missCount = 0;
    
    while(std::getline(infile, line)) {
        if(line.empty()) continue;
        std::stringstream ss(line);
        std::string addrStr;
        ss >> addrStr;
        // Assuming the address is in hexadecimal
        uint64_t address = std::stoull(addrStr, nullptr, 16);
        bool hit = cache.access(address);
        totalAccesses++;
    }
    
    infile.close();
    
    // Output results
    std::cout << "Cache Configuration:\n";
    std::cout << "Cache Size: " << cacheSize << " bytes\n";
    std::cout << "Block Size: " << blockSize << " bytes\n";
    std::cout << "Associativity: " << associativity << "\n";
    std::cout << "Replacement Policy: " << policyStr << "\n\n";
    
    std::cout << "Simulation Results:\n";
    std::cout << "Total Accesses: " << (cache.getHits() + cache.getMisses()) << "\n";
    std::cout << "Hits: " << cache.getHits() << " (" << cache.getHitRate() << "%)\n";
    std::cout << "Misses: " << cache.getMisses() << " (" << cache.getMissRate() << "%)\n";
    
    return 0;
}
