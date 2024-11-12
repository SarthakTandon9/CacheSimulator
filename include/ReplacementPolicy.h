// include/ReplacementPolicy.h
#ifndef REPLACEMENT_POLICY_H
#define REPLACEMENT_POLICY_H

#include <vector>
#include "ReplacementPolicyTypes.h"

class ReplacementPolicy 
{
public:
    virtual ~ReplacementPolicy() {}
    
    virtual void initialize(int associativity) = 0;
    
    virtual void access(int lineIndex) = 0;
    
    virtual int selectVictim() = 0;
};

ReplacementPolicy* createReplacementPolicy(ReplacementPolicyType type, int associativity);

#endif 
