#include "ReplacementPolicy.h"
#include <algorithm>
#include <random>
#include <chrono>

// LRU Replacement Policy
class LRUPolicy : public ReplacementPolicy 
{
private:
    std::vector<int> usageOrder;

public:
    void initialize(int associativity) override 
    {
        usageOrder.clear();
        usageOrder.reserve(associativity);
        for(int i = 0; i < associativity; ++i) 
        {
            usageOrder.push_back(i);
        }
    }
    
    void access(int lineIndex) override 
    {
        // Move the accessed line to the back to denote recent use
        usageOrder.erase(std::remove(usageOrder.begin(), usageOrder.end(), lineIndex), usageOrder.end());
        usageOrder.push_back(lineIndex);
    }
    
    int selectVictim() override 
    {
        // The front of the list is the least recently used
        return usageOrder.front();
    }
};

// FIFO Replacement Policy
class FIFOPolicy : public ReplacementPolicy 
{
private:
    std::vector<int> insertionOrder;

public:
    void initialize(int associativity) override 
    {
        insertionOrder.clear();
        insertionOrder.reserve(associativity);
        for(int i = 0; i < associativity; ++i) 
        {
            insertionOrder.push_back(i);
        }
    }
    
    void access(int lineIndex) override 
    {
        // FIFO does not change on access
    }
    
    int selectVictim() override 
    {
        // The front of the queue is the first inserted
        return insertionOrder.front();
    }
};

// Random Replacement Policy
class RandomPolicy : public ReplacementPolicy 
{
private:
    int associativity;
    std::mt19937 rng;

public:
    void initialize(int associativity_) override 
    {
        associativity = associativity_;
        // Seed RNG with high-resolution clock
        rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    }
    
    void access(int lineIndex) override 
    {
        // Random policy does not need to track usage
    }
    
    int selectVictim() override 
    {
        std::uniform_int_distribution<int> dist(0, associativity - 1);
        return dist(rng);
    }
};

// Factory function implementation
ReplacementPolicy* createReplacementPolicy(ReplacementPolicyType type, int associativity) 
{
    ReplacementPolicy* policy = nullptr;
    switch(type) 
    {
        case ReplacementPolicyType::LRU:
            policy = new LRUPolicy();
            break;
        case ReplacementPolicyType::FIFO:
            policy = new FIFOPolicy();
            break;
        case ReplacementPolicyType::Random:
            policy = new RandomPolicy();
            break;
        default:
            // Default to Random if unknown
            policy = new RandomPolicy();
            break;
    }
    policy->initialize(associativity);
    return policy;
}