SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
BIN := aisteroids
COMPILE_OPTS = -DDEBUG

CC = gcc
CFLAGS=-g  -ggdb -std=c11 -Wall -Wpedantic `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS=-lm `pkg-config --libs sdl2 SDL2_image`

$(BIN): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(COMPILE_OPTS) -c -o $@ $< 

test:
	make -C test_code

test_clean:
	make -C test_code clean

clean: test_clean
	rm -rf $(BIN) $(OBJ_FILES)
