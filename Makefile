SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
BIN := aisteroids
COMPILE_OPTS = -DDEBUG

CC = gcc
CFLAGS=-g -fms-extensions 
LDFLAGS=-lm

$(BIN): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(COMPILE_OPTS) -c -o $@ $< 

clean:
	rm -rf $(BIN) $(OBJ_FILES)
