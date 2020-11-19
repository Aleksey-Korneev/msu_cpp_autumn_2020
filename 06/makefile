CC = g++
FLAGS =  -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic
TARGET = out.exe
OUTPUT = out.txt

all: test clean

test: format
	./$(TARGET) > $(OUTPUT)

format: test.cpp
	$(CC) $(FLAGS) -o $(TARGET) test.cpp

clean:
	rm -f *.o $(TARGET)
