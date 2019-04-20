APP=01

SRC_DIR=.
INC_DIR=inc
BUILD_DIR=build

CC=g++
LD=g++
CFLAGS=-O2 -Wall -std=c++11 -g
LFLGAS=
DFLAGS=-g3 -O0 -DDEBUG
INCFLAGS=-I$(INC_DIR)

SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
HEADERS=$(wildcard $(INC_DIR)/*.h)

.PHONY: all 
all: $(BUILD_DIR)/$(APP)

.PHONY: debug
debug: CFLAGS+=$(DFLAGS)
debug: all 

weird : | $(BUILD_DIR)
	$(CC) $(CFLAGS) weird.cpp -o $(BUILD_DIR)/$@

$(BUILD_DIR)/%.o : %.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# %.out : %.cpp
# 	g++ -std=c++11 -g -Wall $*.cpp -o $*.out

# CC = g++
# # CC   = clang++-3.8 -L /usr/lib/gcc/x86_64-linux-gnu/5.4.0 -I /usr/include/x86_64-linux-gnu/c++/5.4.0 -I /usr/include/c++/5.4.0

# FLAGS = -std=c++11 -g -Wall -pedantic

# main.out: main.cpp hello.o
# 	 $(CC) $(FLAGS) main.cpp hello.o -o main.out

# hello.o: hello.cpp
# 	$(CC) $(FLAGS) -c hello.cpp

# clean:
# 	rm -f *.o *.out