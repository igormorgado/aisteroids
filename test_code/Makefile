SRC_DIR := .
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
BIN_FILES := $(patsubst $(SRC_DIR)/%.c,%,$(SRC_FILES))
COMPILE_OPTS = -DDEBUG

CC = gcc
CFLAGS=-g  -ggdb -std=c11 -fms-extensions  -Wall -Wpedantic
LDFLAGS=-lm

all: $(BIN_FILES)

.PHONY: clean all

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) 

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS) $(COMPILE_OPTS) -c -o $@ $< 

clean:
	rm -rf $(BIN_FILES)
