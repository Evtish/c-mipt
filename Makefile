EXEC_NAME := $(basename $(F))
BUILD_DIR := build
EXEC_FILE := $(BUILD_DIR)/$(EXEC_NAME)

CC := cc
CFLAGS := -Wall -Wextra -std=c99 -pedantic -Og -ggdb
LDFLAGS := -lm

all: $(EXEC_FILE)

$(BUILD_DIR):
	mkdir -pv $(BUILD_DIR)

$(EXEC_FILE): $(F) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(F) -o $(EXEC_FILE)

run: $(EXEC_FILE)
	./$(EXEC_FILE)

clean:
	rm -rf $(EXEC_FILE)

.PHONY: all run clean
