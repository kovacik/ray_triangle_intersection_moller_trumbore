GOOGLE_TEST_LIB := gtest
GOOGLE_TEST_INCLUDE := /usr/local/include

CC		:= g++
C_FLAGS := -c -std=c++11 -Wall -Wextra -Wno-unused-function -msse2 -mfpmath=sse
LD_FLAGS := -L /usr/local/lib -l $(GOOGLE_TEST_LIB) -l pthread

BIN		:= ../bin/tests
INCLUDE	:= ../include

_OBJECTS = main.o triangle_ray_intersection_test.o
OBJECTS = $(patsubst %,$(BIN)/%,$(_OBJECTS))
TARGET = $(BIN)/triangle_ray_intersection_test

all: $(TARGET)

$(BIN)/%.o : %.cpp
	mkdir -p $(BIN)
	$(CC) $(C_FLAGS) -I $(GOOGLE_TEST_INCLUDE) -I $(INCLUDE) -o $@ $<

$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

clean:
	rm -f $(TARGET) $(OBJECTS)

run: clean all
	$(TARGET)
                    
.PHONY: all clean run