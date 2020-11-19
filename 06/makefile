CC = g++
FLAGS =  -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic
TARGET = out.exe
OUTPUT = out.txt
SOURCE = test.cpp
OBJECT_FILES = test.o
all: test clean

test: format
	./$(TARGET) > $(OUTPUT)

format: $(SOURCE)
	$(CC) $(FLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(OBJECT_FILES) $(TARGET)
