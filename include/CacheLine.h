#ifndef CACHE_LINE_H
#define CACHE_LINE_H

#include <cstdint>

struct CacheLine 
{
    bool valid;
    uint64_t tag;
    // Data can be added if needed
    // For simulation purposes, it's optional
    // uint8_t data[64]; // Example for a 64-byte cache line
};

#endif // CACHE_LINE_H
