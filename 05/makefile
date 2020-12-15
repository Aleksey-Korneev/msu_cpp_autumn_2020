CC = g++
FLAGS =  -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic
TARGET = out.exe
OUTPUT = out.txt
SOURCE = test.cpp
OBJECT_FILE = test.o

all: test clean

test: main
	./$(TARGET) > $(OUTPUT)

main: $(OBJECT_FILE)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJECT_FILE)

$(OBJECT_FILE): $(SOURCE)
	$(CC) $(FLAGS) -c $(SOURCE)

clean:
	rm $(OBJECT_FILE) $(TARGET)
