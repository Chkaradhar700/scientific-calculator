# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Iinclude
LDFLAGS = -lm

# Directories
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = obj

# Sources
SRC = $(wildcard $(SRC_DIR)/*.c)
SRC_NO_MAIN = $(filter-out $(SRC_DIR)/main.c, $(SRC))

TEST_SRC = $(TEST_DIR)/tests.c

# Objects
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_NO_MAIN = $(SRC_NO_MAIN:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

# Targets
BIN = calculator
TEST_BIN = calculator_tests   # IMPORTANT: not "tests"

# Default target
all: $(BIN)

# Main program
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Test program
tests: $(OBJ_NO_MAIN) $(TEST_OBJ)
	$(CC) $^ -o $(TEST_BIN) $(LDFLAGS)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test file
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(BIN)
	rm -f $(TEST_BIN)

# Run helpers
run: $(BIN)
	./$(BIN)

run-tests: tests
	./$(TEST_BIN)

.PHONY: all clean run run-tests tests
