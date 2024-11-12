# generate_trace.py

import random
import argparse

def generate_trace(num_accesses, address_space_size, locality_factor, output_file):
    """
    Generates a mock memory access trace file.

    Parameters:
    - num_accesses (int): Number of memory accesses to generate.
    - address_space_size (int): Size of the address space in bytes.
    - locality_factor (float): Probability of accessing a recently accessed address.
                               Range: 0.0 (no locality) to 1.0 (high locality).
    - output_file (str): Path to the output trace file.
    """
    with open(output_file, 'w') as f:
        # Initialize a pool of 'hot' addresses to simulate temporal locality
        hot_pool_size = max(1, num_accesses // 1000)  # Adjust based on num_accesses
        hot_addresses = [random.randint(0, address_space_size - 1) for _ in range(hot_pool_size)]
        
        for i in range(num_accesses):
            if random.random() < locality_factor and hot_addresses:
                # High locality: Reuse a hot address
                addr = random.choice(hot_addresses)
            else:
                # Low locality: Access a random address
                addr = random.randint(0, address_space_size - 1)
                # Optionally, add to hot pool with some probability
                if len(hot_addresses) < hot_pool_size and random.random() < 0.01:
                    hot_addresses.append(addr)
            
            # Simulate spatial locality by accessing nearby addresses
            # For example, access addresses within +/- 32 bytes
            spatial_offset = random.randint(-32, 32)
            addr = max(0, min(addr + spatial_offset, address_space_size - 1))
            
            # Write the address in hexadecimal format
            f.write(f"0x{addr:08X}\n")
            
            # Optionally, periodically print progress
            if (i+1) % (num_accesses // 10) == 0:
                print(f"Generated {i+1} / {num_accesses} accesses")

    print(f"Trace generation complete. Output file: {output_file}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate a large mock memory access trace file.")
    parser.add_argument("-n", "--num_accesses", type=int, default=1000000,
                        help="Total number of memory accesses to generate (default: 1,000,000)")
    parser.add_argument("-s", "--address_space_size", type=int, default=4*1024*1024*1024,
                        help="Address space size in bytes (default: 4,294,967,296 for 4 GB)")
    parser.add_argument("-l", "--locality_factor", type=float, default=0.8,
                        help="Locality factor between 0.0 and 1.0 (default: 0.8)")
    parser.add_argument("-o", "--output_file", type=str, default="trace.txt",
                        help="Output trace file name (default: trace.txt)")
    
    args = parser.parse_args()
    
    # Validate locality_factor
    if not (0.0 <= args.locality_factor <= 1.0):
        raise ValueError("locality_factor must be between 0.0 and 1.0")
    
    generate_trace(args.num_accesses, args.address_space_size, args.locality_factor, args.output_file)
