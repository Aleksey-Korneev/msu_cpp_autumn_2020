g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -c matrix.cpp
g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -c test.cpp
g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -o out.exe matrix.o test.o
rm -f *.o
./out.exe > out.txt
cat out.txt