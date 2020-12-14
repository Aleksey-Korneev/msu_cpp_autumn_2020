g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -c bigint.cpp
g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -c test.cpp
g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -o out.exe bigint.o test.o
./out.exe > out.txt
rm -f *.o out.exe
