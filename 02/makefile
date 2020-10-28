CC = g++
FLAGS =  -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic
TARGET = out.e
OUTPUT = out.txt

all: $(TARGET)

$(TARGET): parser.o test.o
	$(CC) $(FLAGS) -o $(TARGET) parser.o test.o

test: $(TARGET)
	./$(TARGET) > $(OUTPUT)

parser.o: parser.hpp parser.cpp
	$(CC) $(FLAGS) -c parser.cpp

test.o: test.hpp test.cpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -f *.o