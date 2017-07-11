#Makefile for TBB and C++11
#Setup for GNU Make

#Compilers and libs
CPPFLAGS=
CXX=clang++ -pthread
CXXFLAGS=-Wall -Werror -Wextra -pedantic -std=c++14
LDFLAGS=
LDLIBS=

SRC=src/geometric_spanner.cpp src/main.cpp
OBJ=src/geometric_spanner.o src/main.o
EXEC=spanner

all: debug

debug:	CXXFLAGS += -g
debug: $(EXEC)

release:	CXXFLAGS += -O3
release: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	@rm -f $(OBJ) $(EXEC)

.PHONY: all clean debug release
