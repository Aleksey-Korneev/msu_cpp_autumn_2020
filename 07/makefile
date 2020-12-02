CC = g++
FLAGS =  -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic
TARGET = out.exe
OUTPUT = out.txt
SOURCE = test.cpp

all: test clean

test: main
	./$(TARGET) > $(OUTPUT)

main: $(SOURCE) *.hpp impl/*.tpp
	$(CC) $(FLAGS) -o $(TARGET) $(SOURCE)	

clean:
	rm -f *.o $(TARGET)