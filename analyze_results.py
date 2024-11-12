# analyze_results.py

import re

def parse_results(file_path):
    results = []
    current = {}

    with open(file_path, 'r') as f:
        for line in f:
            line = line.strip()
            if line.startswith("Cache Configuration:"):
                current = {}
            elif line.startswith("Cache Size:"):
                current['Cache Size (bytes)'] = int(line.split(":")[1].strip().split()[0])
            elif line.startswith("Block Size:"):
                current['Block Size (bytes)'] = int(line.split(":")[1].strip().split()[0])
            elif line.startswith("Associativity:"):
                current['Associativity'] = int(line.split(":")[1].strip().split("-")[0])
            elif line.startswith("Replacement Policy:"):
                current['Replacement Policy'] = line.split(":")[1].strip()
            elif line.startswith("Total Accesses:"):
                current['Total Accesses'] = int(line.split(":")[1].strip())
            elif line.startswith("Hits:"):
                hits_miss = re.findall(r'(\d+)\s+\(([\d.]+)%\)', line)
                if hits_miss:
                    current['Hits'] = int(hits_miss[0][0])
                    current['Hit Rate (%)'] = float(hits_miss[0][1])
            elif line.startswith("Misses:"):
                hits_miss = re.findall(r'(\d+)\s+\(([\d.]+)%\)', line)
                if hits_miss:
                    current['Misses'] = int(hits_miss[0][0])
                    current['Miss Rate (%)'] = float(hits_miss[0][1])
            elif line.startswith("----------------------------------------"):
                if current:
                    results.append(current)
                    current = {}

    return results

def summarize_results(results):
    # Example: Find the configuration with the highest hit rate
    best = max(results, key=lambda x: x['Hit Rate (%)'])
    print("Best Configuration:")
    for key, value in best.items():
        print(f"{key}: {value}")

    print("\nAll Results:")
    for res in results:
        print("----------------------------------------")
        for key, value in res.items():
            print(f"{key}: {value}")
    print("----------------------------------------")

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <results_file>")
        sys.exit(1)

    results_file = sys.argv[1]
    simulation_results = parse_results(results_file)

    if not simulation_results:
        print("No simulation results found.")
        sys.exit(1)

    summarize_results(simulation_results)
