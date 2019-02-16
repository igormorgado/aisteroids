SRC_DIR := ./src
OBJ_DIR := ./obj
TEST_DIR := ./tests
UTIL_DIR := ./utils
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
SUP_FILES = $(wildcard $(UTIL_DIR)/*.supp)
PERF_FILES := aisteroids.gprof gmon.out perf.data perf.data.old report

## Removes main.o to avoid conflicts with main() already referenced
## How to better handle TEST_BIN_FILES and TEST_TARGETS to avoid
## two very similar variables contents and keeping the usage in the 
## `tests` target
TEST_OBJ_FILES := $(filter-out $(OBJ_DIR)/main.o,$(OBJ_FILES))
TEST_SRC_FILES := $(wildcard $(TEST_DIR)/*.c)
TEST_TARGETS := $(patsubst $(TEST_DIR)/%.c,%,$(TEST_SRC_FILES))
TEST_BIN_FILES := $(foreach file,$(TEST_TARGETS), $(TEST_DIR)/bin/$(file))
TEST_INCLUDES := -I./tests

BIN := aisteroids

CC = gcc
COMPILE_OPTS = -DDEBUG
OPTMIZATIONS = -Os 

INCLUDES := -I./src

# Libraries Flags
SDL_CFLAGS = `pkg-config --cflags sdl2 SDL2_image`
SDL_LDFLAGS = `pkg-config --libs sdl2 SDL2_image`

CFLAGS := -pg -g -ggdb -std=c11 -Wall -Wshadow -Wpedantic  # -Wextra
CFLAGS += $(SDL_CFLAGS)

LDFLAGS := -pg -lm 
LDFLAGS += $(SDL_LDFLAGS)

TEST_CFLAGS = 
TEST_LDFLAGS = -lcunit

SUPFLAGS = $(foreach file,$(SUP_FILES), --suppressions=$(file))

$(BIN): $(OBJ_FILES)
	$(CC) $(INCLUDES) -o $@ $^ $(LDFLAGS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(INCLUDES) $(CFLAGS) $(COMPILE_OPTS) -c -o $@ $< 

run_tests: tests
	@echo Exec the tests: $(TEST_BIN_FILESP)

tests: $(TEST_TARGETS) 

tests_clean:
	rm -rf $(TEST_BIN_FILES)

## Why those keep rebuilding even with binaries updated?
$(TEST_TARGETS): $(TEST_OBJ_FILES)
	$(CC) $(INCLUDES) $(TEST_INCLUDES) $(CFLAGS) $(TEST_CFLAGS) -o $(TEST_DIR)/bin/$@ $(TEST_DIR)/$@.c  $(TEST_OBJ_FILES) $(LDFLAGS) $(TEST_LDFLAGS)

check_static: clean
	scan-build-3.8 make 

check_leaks: clean $(BIN)
	valgrind $(SUPFLAGS) --leak-check=full --track-origins=yes ./$(BIN)

valg_gen_supp:
	valgrind --leak-check=full $(SUPFLAGS) --gen-suppressions=all --error-limit=no ./$(BIN) > $(UTIL_DIR)/new.supp

valg_supp_merge:
	$(UTIL_DIR)/parse_supress.sh $(UTIL_DIR)/new.supp > $(UTIL_DIR)/new_proc.supp
	valgrind $(SUPFLAGS) --leak-check=full --track-origins=yes ./$(BIN) | \
	$(UTIL_DIR)/grindmerge.pl -f $(UTIL_DIR)/new_proc.supp > $(UTIL_DIR)/new_merged.supp
	rm -rf $(UTIL_DIR)/new.supp $(UTIL_DIR)/new_proc.supp

profile_perf: $(BIN)
	perf_4.19 record -g ./$(BIN)
	perf_4.19 report

profile_gprof: $(BIN)
	gprof ./aisteroids  > $(BIN).gprof


stud:
	make -C stud

stud_clean:
	make -C stud clean

clean: 
	rm -rf $(BIN) $(OBJ_FILES)  $(PERF_FILES)

distclean: stud_clean clean tests_clean

install:
	@echo "There is no install..." 

.PHONY: stud stud_clean clean distclean install tests
