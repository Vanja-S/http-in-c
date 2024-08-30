CC=clang
CFLAGS=-c -Wall
SRC_DIR=src
OBJ_DIR=obj
LIB_DIR=$(SRC_DIR)/lib
LOG_DIR=$(SRC_DIR)/log

# List all source files
SRCS=$(SRC_DIR)/main.c $(LIB_DIR)/lib.c $(LIB_DIR)/string.c $(LOG_DIR)/log.c
# Generate object file names
OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: dirs server

# Create necessary directories
dirs:
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/lib $(OBJ_DIR)/log

# Main program (now named 'server')
server: $(OBJS)
	$(CC) $^ -o $@

# Pattern rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Library targets
lib: $(OBJ_DIR)/lib/lib.o $(OBJ_DIR)/lib/string.o

log: $(OBJ_DIR)/log/log.o

# Clean target
clean:
	rm -rf $(OBJ_DIR) server

.PHONY: all clean dirs lib log
