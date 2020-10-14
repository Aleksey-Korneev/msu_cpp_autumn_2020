CC = g++
FLAGS = -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic
TARGET = out.e

all: $(TARGET) clean

$(TARGET): allocator.o test.o
	$(CC) $(FLAGS) -o $(TARGET) allocator.o test.o

test: $(TARGET)
	./$(TARGET)

allocator.o: allocator.cpp allocator.hpp
	$(CC) $(FLAGS) -c allocator.cpp
    
test.o: test.cpp allocator.hpp tester.hpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -rf *.o