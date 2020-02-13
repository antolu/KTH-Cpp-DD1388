SRC_DIR=.
INC_DIR=../04-matrix
BUILD_DIR=build

CC=g++
LD=g++

CFLAGS=-O2 -Wall -std=c++17 -g -fext-numeric-literals -I$(INC_DIR)
LFLAGS=-lgtest
DFLAGS=-ggdb3 -O0 -DDEBUG
CFLAGS+=$(DFLAGS)

SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard $(INC_DIR)/*.h)
OBJS = $(patsubst %,$(BUILD_DIR)/%.o,$(basename $(SOURCES)))

test : $(BUILD_DIR)/main
	./$(BUILD_DIR)/main --use-colour=no

.PHONY: all 
all: $(OBJS)

.PHONY: debug
debug: 
	CFLAGS+="$(DFLAGS)"

.PHONY: chess
chess: $(BUILD_DIR)/chess

$(BUILD_DIR)/chess: $(OBJS) | build_dir
	$(CC) $(CXXLIBS) $(CFLAGS) $(LFLAGS) -o $@ $^


$(BUILD_DIR)/tests: $(OBJS) | build_dir
	$(CC) $(CXXLIBS) -o $@ $^

$(BUILD_DIR)/%.o : %.cpp | build_dir
	$(CC) $(CFLAGS) $(INCFLAGS) -c -o $@ $<

.PHONY: build_dir
build_dir:
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)


