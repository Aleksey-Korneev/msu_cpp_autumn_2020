#include <iostream>
#include "sharedptr.hpp"

class Test {
public:
    Test() = default;
    void print()
    {
        std::cout << "Test.print()" << std::endl;
    }
};


int main()
{
    SharedPtr<int> x1(new int(1));
    SharedPtr<int> x2 = x1;
    SharedPtr<int> x3(x1);
    SharedPtr<int> x4(std::move(x1));
    
    std::cout << x1.get() << std::endl; // was moved
    std::cout << x2.get() << std::endl;
    std::cout << x3.get() << std::endl;
    std::cout << x3.get() << std::endl;
    

    SharedPtr<int> x6(new int(4));
    x2 = x6;
    x3 = std::move(x6);

    x3.reset(new int(5));
    x1 = x3;

    SharedPtr<Test> x5(new Test());
    x5->print();
    
    return 0;
}
