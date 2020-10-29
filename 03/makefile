CC = g++
FLAGS =  -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic
TARGET = out.exe
OUTPUT = out.txt
OBJECT_FILES = matrix.o test.o

all: $(TARGET)

$(TARGET): $(OBJECT_FILES)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJECT_FILES)

test: $(TARGET)
	./$(TARGET) > $(OUTPUT)

matrix.o: matrix.hpp matrix.cpp
	$(CC) $(FLAGS) -c matrix.cpp

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -f *.o
