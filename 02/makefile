CC = g++
FLAGS =  -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic
TARGET = out.exe
OUTPUT = out.txt
OBJECT_FILES = parser.o test.o

all: $(TARGET) test clean

$(TARGET): $(OBJECT_FILES)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJECT_FILES)

test: $(TARGET)
	./$(TARGET) > $(OUTPUT)

parser.o: parser.hpp parser.cpp
	$(CC) $(FLAGS) -c parser.cpp

test.o: test.hpp test.cpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -f $(OBJECT_FILES) $(TARGET)
