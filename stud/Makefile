BIN_DIR := ./bin
SRC_DIR := .
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
BIN_FILES := $(patsubst $(SRC_DIR)/%.c,%,$(SRC_FILES))
COMPILE_OPTS = -DDEBUG

CC = gcc
CFLAGS = -pg -g  -ggdb -std=c11 -fms-extensions  -Wall -Wpedantic `pkg-config --cflags sdl2 SDL2_image SDL2_gfx`
LDFLAGS = `pkg-config --libs sdl2 SDL2_image SDL2_gfx` -lm

all: $(BIN_FILES)

.PHONY: clean all

%: %.c
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $(BIN_DIR)/$@ 

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS) $(COMPILE_OPTS) -c -o $@ $< 

clean:
	rm -rf  $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRC_FILES))
