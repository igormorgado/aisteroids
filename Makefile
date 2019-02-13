SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
BIN := aisteroids
COMPILE_OPTS = -DDEBUG
OPTMIZATIONS = -Os -O2 2

CC = gcc
# -Wstrict-overflow -fno-strict-aliasing 
# -Wextra -Werror -Wshadow  -Wno-missing-field-initializers
#-march=native -msse4.2 -ggdb -flto 
PURISTFLAGS=-Wall -Wpedantic 
CFLAGS=-g -std=c11 `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS= -lm `pkg-config --libs sdl2 SDL2_image`

$(BIN): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(PURISTFLAGS) $(CFLAGS) $(COMPILE_OPTS) -c -o $@ $< 

test:
	make -C test_code

test_clean:
	make -C test_code clean

clean: test_clean
	rm -rf $(BIN) $(OBJ_FILES)

scan: clean
	scan-build-3.8 make 

leak: clean $(BIN)
	valgrind --leak-check=full ./$(BIN)

track: clean $(BIN)
	valgrind  -v --track-origins=yes ./$(BIN)
	
