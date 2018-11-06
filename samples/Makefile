CC		:= g++
C_FLAGS := -std=c++11 -Wall -Wextra -msse2 -mfpmath=sse

BIN		:= ../bin/samples
INCLUDE	:= ../include

SRCS = $(wildcard *.cpp)
PROGS = $(patsubst %.cpp,%,$(SRCS))

all: $(PROGS)

%: %.cpp
	mkdir -p $(BIN)
	$(CC) $(C_FLAGS) -I$(INCLUDE) -o $(BIN)/$@ $<

clean:
	rm -rf $(BIN)

run: all
	$(BIN)/$(PROGS)

.PHONY: all clean run