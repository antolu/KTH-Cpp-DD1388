SRC_DIR=.
INC_DIR=inc
BUILD_DIR=build

CC=g++
LD=g++

CFLAGS=-O2 -Wall -std=c++11 -g -fext-numeric-literals
LFLAGS=-lgtest
DFLAGS=-ggdb3 -O0 -DDEBUG
CFLAGS+=$(DFLAGS)

SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard $(INC_DIR)/*.h)
OBJS = $(patsubst %,$(BUILD_DIR)/%.o,$(basename $(SOURCES)))

.PHONY: all 
all: $(OBJS)

.PHONY: debug
debug: 
	CFLAGS+="$(DFLAGS)"

.PHONY: matrix
matrix: $(BUILD_DIR)/matrix.o

test : $(BUILD_DIR)/tests
	./$(BUILD_DIR)/tests --use-colour=no

$(BUILD_DIR)/tests: $(OBJS) | build_dir
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

$(BUILD_DIR)/%.o : %.cpp | build_dir
	$(CC) $(CFLAGS) $(INCFLAGS) -c -o $@ $<

.PHONY: build_dir
build_dir:
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)


