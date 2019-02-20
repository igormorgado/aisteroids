BIN := aisteroids

SRC_DIR := ./src
OBJ_DIR := ./obj
UTIL_DIR := ./utils
INCLUDES := -I./src
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

TEST_DIR := ./tests
TEST_BIN_DIR := ./tests/bin
TEST_OBJ_FILES := $(filter-out $(OBJ_DIR)/main.o,$(OBJ_FILES))
TEST_SRC_FILES := $(wildcard $(TEST_DIR)/*.c)
TEST_TARGETS := $(patsubst $(TEST_DIR)/%.c,$(TEST_BIN_DIR)/%,$(TEST_SRC_FILES))
TEST_INCLUDES := -I./tests

PERF_FILES := aisteroids.gprof gmon.out perf.data perf.data.old report
SUP_FILES = $(wildcard $(UTIL_DIR)/*.supp)

CC = gcc

#DEBUG_CPPFLAGS = -DDEBUG

# PROF_CFLAGS := -pg
# OPTMIZATION_CFLAGS := -Os 
# TEST_CFLAGS = 
# DEBUG_CFLAGS := -g -ggdb
PEDANTIC_CFLAGS := -std=c11 -Wall -Wshadow -Wpedantic  # -Wextra

# COMMENT FLAGS DECLARATION ABOVE NOT ASSINGMENT BELOW
# #####################################################
#
# Libraries Flags
SDL_CFLAGS = `pkg-config --cflags sdl2 SDL2_image`
SDL_LDFLAGS = `pkg-config --libs sdl2 SDL2_image`

# CPP Flags
CPPFLAGS :=
CPPFLAGS += $(DEBUG_CPPFLAGS)

# GCC Flags
CFLAGS :=
CFLAGS += $(DEBUG_CFLAGS)
CFLAGS += $(OPTMIZATION_CFLAGS)
CFLAGS += $(PROF_CFLAGS)
CFLAGS += $(PEDANTIC_CFLAGS)
CFLAGS += $(SDL_CFLAGS)

# Linker Flags
#PROF_LDFLAGS := -pg
TEST_LDFLAGS = -lcunit

LDFLAGS := -lm
LDFLAGS += $(PROF_LDFLAGS) 
LDFLAGS += $(SDL_LDFLAGS)

# Valgrind suppression files
SUPFLAGS = $(foreach file,$(SUP_FILES), --suppressions=$(file))

##################################
# MAIN TARGETS
##################################
$(BIN): $(OBJ_FILES)
	$(CC) $(INCLUDES) -o $@ $^ $(LDFLAGS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(INCLUDES) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

clean: 
	rm -rf $(BIN) $(OBJ_FILES)  $(PERF_FILES) gmon*.out

distclean: stud_clean clean tests_clean

install:
	@echo "There is no install..." 

###################################
# TEST TARGETS
###################################
run_tests: tests
	./run_tests.sh

tests: $(TEST_TARGETS)

tests_clean:
	rm -rf $(TEST_TARGETS)

$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(TEST_OBJ_FILES)
	$(CC) $(INCLUDES) $(TEST_INCLUDES) $(CFLAGS) $(TEST_CFLAGS) $(LDFLAGS) $(TEST_LDFLAGS) $^ -o $@

##################################
# PROFILING TARGETS
##################################
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


#################################
# STUDY FILES
#################################
stud:
	make -C stud

stud_clean:
	make -C stud clean

all: $(BIN) tests stud

#################################
# PHONY
#################################
.PHONY: all clean distclean install \
	stud stud_clean \
	tests tests_clean run_tests \
	check_static check_leaks \
	valg_gen_supp valg_supp_merge \
	profile_perf profile_gprof
