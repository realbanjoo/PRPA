#Makefile for TBB and C++11
#Setup for GNU Make

#Compilers and libs
CPPFLAGS=
CXX=g++ -pthread
CXXFLAGS= -Wall -Werror -Wextra -pedantic -std=c++14 -Itbb2017_20170604oss/include
LDFLAGS=
LDLIBS= -lrt -ltbb

OBJ=src/geometric_spanner.o src/main.o
EXEC=spanner

all: debug

debug:	CXXFLAGS += -g
debug: $(EXEC)

release:	CXXFLAGS += -O3
release: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $@ $^

clean:
	@rm -f $(OBJ) $(EXEC) src/*.gch

.PHONY: all clean debug release
