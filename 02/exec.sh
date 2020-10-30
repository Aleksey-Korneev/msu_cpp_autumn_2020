g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -c parser.cpp
g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -c test.cpp
g++ -std=gnu++17 -O2 -Wall -Werror -Wextra -pedantic -o out.e parser.o test.o
./out.e > out.txt
rm -f *.o out.e
cat out.txt
