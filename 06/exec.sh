g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -o out.exe test.cpp
./out.exe > out.txt
rm -f *.o out.exe
