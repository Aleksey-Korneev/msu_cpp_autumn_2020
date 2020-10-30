g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -c parser.cpp
g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -c test.cpp
g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -o out.exe parser.o test.o
./out.exe > out.txt
rm -f parser.o test.o out.exe
cat out.txt
