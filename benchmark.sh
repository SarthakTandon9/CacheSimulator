#!/bin/bash

# benchmark.sh
# Automates running cache simulations with different configurations

# Create/clear the results file
echo "Cache Simulation Results" > data/results.txt
echo "======================" >> data/results.txt
echo "" >> data/results.txt

# Define arrays of parameters
cache_sizes=(16384 32768 65536) # 16KB, 32KB, 64KB
associativities=(4 8 16)        # 4-way, 8-way, 16-way
policies=("LRU" "FIFO" "Random")

# Loop over all combinations
for size in "${cache_sizes[@]}"; do
    for assoc in "${associativities[@]}"; do
        for policy in "${policies[@]}"; do
            echo "Running simulation with Cache Size: ${size} bytes, Associativity: ${assoc}-way, Policy: ${policy}"
            
            # Add a separator line to results file
            echo "----------------------------------------" >> data/results.txt
            
            # Run simulation and append output to results file
            echo "Cache Size: ${size} bytes, Associativity: ${assoc}-way, Policy: ${policy}" >> data/results.txt
            ./build/cache_simulator $size 64 $assoc $policy data/trace.txt >> data/results.txt 2>&1
            
            # Add a blank line after each result
            echo "" >> data/results.txt
        done
    done
done

echo "Benchmarking complete. Results stored in data/results.txt"