# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -O2 -Iinclude -Ihft/include

# Directories
SRC_DIR = src
INC_DIR = include
HFT_DIR = hft
HFT_SRC_DIR = hft/src
HFT_INC_DIR = hft/include
BUILD_DIR = build

# Source files for Cache Simulator
CACHE_SRC_FILES = $(SRC_DIR)/Cache.cpp \
                  $(SRC_DIR)/CacheSet.cpp \
                  $(SRC_DIR)/ReplacementPolicy.cpp \
                  $(SRC_DIR)/CacheLine.cpp
CACHE_OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CACHE_SRC_FILES))

# Source files for HFT Order Book
HFT_SRC_FILES = $(HFT_SRC_DIR)/OrderBook.cpp \
                $(HFT_DIR)/main.cpp
HFT_OBJ_FILES = $(BUILD_DIR)/hft_OrderBook.o $(BUILD_DIR)/hft_main.o

# Test files
TEST_SRC = tests/test_cache.cpp
TEST_OBJ = $(BUILD_DIR)/test_cache.o
TEST_EXEC = $(BUILD_DIR)/test_cache

# Main executable for Cache Simulator
MAIN_SRC = main.cpp
MAIN_OBJ = $(BUILD_DIR)/main.o
MAIN_EXEC = $(BUILD_DIR)/cache_simulator

# HFT executable
HFT_EXEC = $(BUILD_DIR)/hft_order_book

# All target
all: $(MAIN_EXEC) $(HFT_EXEC)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Object files for Cache Simulator
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Main object
$(BUILD_DIR)/main.o: $(MAIN_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cache Simulator executable
$(MAIN_EXEC): $(CACHE_OBJ_FILES) $(BUILD_DIR)/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Object files for HFT Order Book from src directory
$(BUILD_DIR)/hft_%.o: $(HFT_SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Special rule for HFT main.cpp in hft directory
$(BUILD_DIR)/hft_main.o: $(HFT_DIR)/main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# HFT executable
$(HFT_EXEC): $(HFT_OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Test object
$(BUILD_DIR)/test_cache.o: $(TEST_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test executable
$(TEST_EXEC): $(CACHE_OBJ_FILES) $(BUILD_DIR)/test_cache.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run tests
run_tests: $(TEST_EXEC)
	./$(TEST_EXEC)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run_tests