g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -c test.cpp
g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -o out.exe test.o
./out.exe > out.txt
rm test.o out.exe
