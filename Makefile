SRC_DIR := ./src
OBJ_DIR := ./obj
UTIL_DIR := ./utils
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
SUP_FILES = $(wildcard $(UTIL_DIR)/*.supp)
PERF_FILES := aisteroids.gprof gmon.out perf.data perf.data.old report

BIN := aisteroids

COMPILE_OPTS = -DDEBUG
OPTMIZATIONS = -Os 

CC = gcc

# -Wextra to be added later 
CFLAGS := -pg -g -ggdb -std=c11 -Wall -Wshadow -Wpedantic `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS := -pg -lm `pkg-config --libs sdl2 SDL2_image`

SUPFLAGS = $(foreach file,$(SUP_FILES), --suppressions=$(file))

# PURISTFLAGS
# -Wextra -Werror -Wshadow  -Wno-missing-field-initializers
#-march=native -msse4.2 -ggdb -flto 


$(BIN): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(COMPILE_OPTS) -c -o $@ $< 

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

distclean: stud_clean clean

install:
	@echo "There is no install..." 


.PHONY: stud stud_clean clean distclean install 
