#ifndef CACHE_SET_H
#define CACHE_SET_H

#include <vector>
#include "CacheLine.h"
#include "ReplacementPolicy.h"
#include "ReplacementPolicyTypes.h" // Ensure this is included

class CacheSet 
{
    private:
        std::vector<CacheLine> lines;
        ReplacementPolicy* policy;
        int associativity;
    public:
        CacheSet(int associativity_, ReplacementPolicyType policyType);
        ~CacheSet();
        
        // Access the cache set with a given tag
        bool access(uint64_t tag);
        
        // For testing and debugging
        int getValidLines() const;
};

#endif // CACHE_SET_H
