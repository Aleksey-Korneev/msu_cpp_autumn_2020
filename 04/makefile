CC = g++
FLAGS =  -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic
TARGET = out.exe
OUTPUT = out.txt
SOURCE = test.cpp
OBJECT_FILES = bigint.o test.o

all: test clean

test: main
	./$(TARGET) > $(OUTPUT)

main: $(OBJECT_FILES)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJECT_FILES)

bigint.o: bigint.hpp bigint.cpp
	$(CC) $(FLAGS) -c bigint.cpp

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -f *.o $(TARGET)
