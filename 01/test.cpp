#include "allocator.hpp"
#include "tester.hpp"

#include <iostream>

int main()
{
    if (!test()) {
        std::cout << "All tests passed." << std::endl;
    }
    return 0;
}