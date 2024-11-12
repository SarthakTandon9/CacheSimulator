// src/CacheSet.cpp
#include "CacheSet.h"
#include <cstdint>

CacheSet::CacheSet(int associativity_, ReplacementPolicyType policyType)
    : associativity(associativity_) 
{
    lines.resize(associativity);
    for(auto &line : lines) 
    {
        line.valid = false;
        line.tag = 0;
    }
    policy = createReplacementPolicy(policyType, associativity);
}

CacheSet::~CacheSet() 
{
    delete policy;
}

bool CacheSet::access(uint64_t tag) 
{
    // Check for hit
    for(int i = 0; i < associativity; ++i) 
    {
        if(lines[i].valid && lines[i].tag == tag) 
        {
            policy->access(i);
            return true; // Hit
        }
    }
    
    // Miss: need to replace a line
    int victim = policy->selectVictim();
    lines[victim].valid = true;
    lines[victim].tag = tag;
    policy->access(victim); // Update policy after insertion
    return false; // Miss
}

int CacheSet::getValidLines() const 
{
    int count = 0;
    for(const auto &line : lines) 
    {
        if(line.valid) count++;
    }
    return count;
}