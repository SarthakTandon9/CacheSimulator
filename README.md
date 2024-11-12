# HFT Cache Simulator

![License](https://img.shields.io/github/license/yourusername/HFT-Cache-Simulator)
![Build Status](https://img.shields.io/github/actions/workflow/status/yourusername/HFT-Cache-Simulator/build.yml?branch=main)
![Stars](https://img.shields.io/github/stars/yourusername/HFT-Cache-Simulator?style=social)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
  - [Building the Project](#building-the-project)
  - [Generating a Memory Access Trace](#generating-a-memory-access-trace)
  - [Running the Cache Simulator](#running-the-cache-simulator)
  - [Benchmarking](#benchmarking)
  - [Analyzing Results](#analyzing-results)
- [Example](#example)
- [Customization](#customization)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Introduction

The **HFT Cache Simulator** is a high-performance simulation tool designed to model and analyze cache behavior in High-Frequency Trading (HFT) applications. It integrates a cache simulator with a synthetic HFT order book processing algorithm to generate realistic memory access patterns. The tool allows users to benchmark different cache configurations and replacement policies, facilitating the optimization of cache strategies tailored to HFT workloads.

## Features

- **Modular Design**: Separate components for cache simulation and HFT order book processing.
- **Multiple Replacement Policies**: Supports LRU, FIFO, Random, and an Optimized custom policy.
- **Benchmarking Scripts**: Automate simulations across various cache configurations.
- **Comprehensive Analysis**: Tools to parse and summarize simulation results.
- **Extensible**: Easily add new replacement policies or enhance the HFT simulation.

## Project Structure

```
HFT-Cache-Simulator/
├── include/
│   ├── Cache.h
│   ├── CacheLine.h
│   ├── CacheSet.h
│   ├── ReplacementPolicy.h
│   └── ReplacementPolicyTypes.h
├── src/
│   ├── Cache.cpp
│   ├── CacheSet.cpp
│   ├── ReplacementPolicy.cpp
│   └── CacheLine.cpp
├── hft/
│   ├── include/
│   │   └── OrderBook.h
│   ├── src/
│   │   └── OrderBook.cpp
│   └── main.cpp
├── tests/
│   └── test_cache.cpp
├── data/
│   ├── trace.txt
│   └── results.txt
├── build/
├── scripts/
│   ├── generate_trace.py
│   ├── benchmark.sh
│   └── analyze_results.py
├── Makefile
├── README.md
└── LICENSE
```

- **include/**: Header files for cache simulation components.
- **src/**: Source files implementing the cache simulation.
- **hft/**: HFT order book processing module.
  - **include/**: Header files for the HFT module.
  - **src/**: Source files for the HFT module.
  - **main.cpp**: Entry point for the HFT simulation.
- **tests/**: Unit tests for the cache simulator.
- **data/**: Stores memory access traces and simulation results.
- **build/**: Compiled binaries and object files.
- **scripts/**: Utility scripts for trace generation, benchmarking, and result analysis.
- **Makefile**: Build instructions.
- **README.md**: Project documentation.
- **LICENSE**: Licensing information.

## Installation

### Prerequisites

- **C++ Compiler**: `g++` with C++11 support.
- **Make**: For building the project.
- **Python 3**: For trace generation and analysis scripts.

### Clone the Repository

```bash
git clone https://github.com/yourusername/HFT-Cache-Simulator.git
cd HFT-Cache-Simulator
```

## Usage

### Building the Project

Use the provided `Makefile` to compile the project.

```bash
make
```

This command will:

- Compile the cache simulator.
- Compile the HFT order book simulation.
- Generate the executables in the `build/` directory:
  - `build/cache_simulator`
  - `build/hft_order_book`

### Generating a Memory Access Trace

The HFT simulation generates a memory access trace representing how an HFT order book interacts with the cache.

#### Run the HFT Simulation

```bash
./build/hft_order_book [num_operations] [trace_file]
```

- **`num_operations`**: (Optional) Number of operations to simulate. Default: `1000000`.
- **`trace_file`**: (Optional) Path to the output trace file. Default: `data/trace.txt`.

**Example:**

```bash
./build/hft_order_book 1000000 data/trace.txt
```

This command simulates 1,000,000 operations and logs memory accesses to `data/trace.txt`.

### Running the Cache Simulator

The cache simulator processes the generated memory access trace to evaluate cache performance.

#### Command Structure

```bash
./build/cache_simulator <cache_size> <block_size> <associativity> <replacement_policy> <trace_file>
```

- **`cache_size`**: Total cache size in bytes (e.g., `32768` for 32KB).
- **`block_size`**: Size of each cache block in bytes (e.g., `64`).
- **`associativity`**: Number of cache lines per set (e.g., `8` for 8-way set associative).
- **`replacement_policy`**: Cache replacement policy (`LRU`, `FIFO`, `Random`, `OPTIMIZED`).
- **`trace_file`**: Path to the memory access trace file (e.g., `data/trace.txt`).

**Example:**

```bash
./build/cache_simulator 32768 64 8 LRU data/trace.txt
```

#### Output

The simulator outputs the cache configuration and simulation results, including total accesses, hits, misses, and hit/miss rates. Results are also appended to `data/results.txt`.

**Sample Output:**

```
Cache Configuration:
Cache Size: 32768 bytes
Block Size: 64 bytes
Associativity: 8
Replacement Policy: LRU

Simulation Results:
Total Accesses: 1000000
Hits: 850000 (85.0000%)
Misses: 150000 (15.0000%)
----------------------------------------
```

### Benchmarking

Automate running multiple simulations with varying cache configurations using the provided `benchmark.sh` script.

#### Setup

Ensure the script is executable:

```bash
chmod +x scripts/benchmark.sh
```

#### Run the Benchmark

```bash
./scripts/benchmark.sh
```

This script runs simulations across different cache sizes, associativities, and replacement policies, appending results to `data/results.txt`.

**Sample Output:**

```
Running simulation with Cache Size: 16384 bytes, Associativity: 4-way, Policy: LRU
Cache Configuration:
Cache Size: 16384 bytes
Block Size: 64 bytes
Associativity: 4
Replacement Policy: LRU

Simulation Results:
Total Accesses: 1000000
Hits: 800000 (80.0000%)
Misses: 200000 (20.0000%)
----------------------------------------
...
Benchmarking complete. Results stored in data/results.txt
```

### Analyzing Results

Use the `analyze_results.py` script to parse and summarize benchmarking results.


#### Run the Analysis

```bash
python3 analyze_results.py data/results.txt
```

**Sample Output:**

```
Best Configuration:
Cache Size (bytes): 65536
Block Size (bytes): 64
Associativity: 16
Replacement Policy: OPTIMIZED
Total Accesses: 1000000
Hits: 900000
Hit Rate (%): 90.0
Misses: 100000
Miss Rate (%): 10.0

All Results:
----------------------------------------
Cache Size (bytes): 16384
Block Size (bytes): 64
Associativity: 4
Replacement Policy: LRU
Total Accesses: 1000000
Hits: 800000
Hit Rate (%): 80.0
Misses: 200000
Miss Rate (%): 20.0
----------------------------------------
...
----------------------------------------
Cache Size (bytes): 65536
Block Size (bytes): 64
Associativity: 16
Replacement Policy: OPTIMIZED
Total Accesses: 1000000
Hits: 900000
Hit Rate (%): 90.0
Misses: 100000
Miss Rate (%): 10.0
----------------------------------------
```

This script identifies the best-performing cache configuration based on the highest hit rate and lists all simulation results for comprehensive analysis.

## Example

1. **Generate a Trace:**

   ```bash
   ./build/hft_order_book 1000000 data/trace.txt
   ```

2. **Run the Cache Simulator with LRU Policy:**

   ```bash
   ./build/cache_simulator 32768 64 8 LRU data/trace.txt
   ```

3. **Run Benchmarking:**

   ```bash
   ./scripts/benchmark.sh
   ```

4. **Analyze Results:**

   ```bash
   python3 scripts/analyze_results.py data/results.txt
   ```

## Customization

### Adding New Replacement Policies

1. **Define the Policy:**

   - Extend `ReplacementPolicyTypes.h` with a new enum value.
   - Implement the policy by inheriting from the `ReplacementPolicy` base class in `ReplacementPolicy.cpp`.

2. **Update the Factory Function:**

   - Modify `createReplacementPolicy` to handle the new policy type.

3. **Rebuild the Project:**

   ```bash
   make clean
   make
   ```

4. **Run Simulations with the New Policy:**

   ```bash
   ./build/cache_simulator <cache_size> <block_size> <associativity> <new_policy> data/trace.txt
   ```

### Modifying the HFT Simulation

- **Adjust Operation Ratios:**

  Modify `hft/src/main.cpp` to change the probability distribution of limit and market orders.

- **Enhance Order Book Features:**

  Implement additional order types or more sophisticated matching algorithms.

- **Increase Complexity:**

  Introduce multithreading or simulate more realistic trading scenarios.

## Contributing

Contributions are welcome! Please follow these steps:

1. **Fork the Repository**

2. **Create a Feature Branch**

   ```bash
   git checkout -b feature/YourFeature
   ```

3. **Commit Your Changes**

   ```bash
   git commit -m "Add your message here"
   ```

4. **Push to the Branch**

   ```bash
   git push origin feature/YourFeature
   ```

5. **Open a Pull Request**

## License

This project is licensed under the [MIT License](LICENSE).

## Contact

For questions, suggestions, or feedback, please contact [tandon33@purdue.edu](mailto:tandon33@purdue.edu).

---

