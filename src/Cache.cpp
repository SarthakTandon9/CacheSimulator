// src/Cache.cpp
#include "Cache.h"
#include <cmath>

Cache::Cache(const CacheConfig& cfg) : config(cfg), hits(0), misses(0) 
{
    numSets = config.cacheSize / (config.blockSize * config.associativity);
    sets.reserve(numSets);
    for(size_t i = 0; i < numSets; ++i) 
    {
        sets.push_back(new CacheSet(config.associativity, config.policyType));
    }
}

Cache::~Cache() 
{
    for(auto set : sets) 
    {
        delete set;
    }
}

bool Cache::access(uint64_t address) 
{
    // Calculate block address
    uint64_t blockAddress = address / config.blockSize;
    uint64_t index = blockAddress % numSets;
    uint64_t tag = blockAddress / numSets;
    
    bool hit = sets[index]->access(tag);
    if(hit) 
    {
        hits++;
    } 
    else 
    {
        misses++;
    }
    return hit;
}

double Cache::getHitRate() const 
{
    size_t total = hits + misses;
    if(total == 0) 
    {
        return 0.0;
    }
    return (static_cast<double>(hits) / total) * 100.0;
}

double Cache::getMissRate() const 
{
    size_t total = hits + misses;
    if(total == 0) 
    {
        return 0.0;
    }
    return (static_cast<double>(misses) / total) * 100.0;
}