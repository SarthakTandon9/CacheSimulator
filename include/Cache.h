// include/Cache.h
#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cstdint>
#include <cstddef>
#include "CacheSet.h"
#include "ReplacementPolicyTypes.h"

struct CacheConfig {
    size_t cacheSize;          // Total cache size in bytes
    size_t blockSize;          // Block size in bytes
    int associativity;         // Number of lines per set
    ReplacementPolicyType policyType; // Replacement policy
};

class Cache {
private:
    CacheConfig config;
    size_t numSets;
    std::vector<CacheSet*> sets;
    
    // Metrics
    size_t hits;
    size_t misses;
public:
    Cache(const CacheConfig& cfg);
    ~Cache();
    
    // Access the cache with a memory address
    bool access(uint64_t address);
    
    // Getters for metrics
    size_t getHits() const { return hits; }
    size_t getMisses() const { return misses; }
    
    double getHitRate() const;
    double getMissRate() const;
};

#endif // CACHE_H
