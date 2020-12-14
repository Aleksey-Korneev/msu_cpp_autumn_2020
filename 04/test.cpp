#include "bigint.hpp"
#include <iostream>
#include <cassert>
#include <sstream>
#include <exception>

//Various constructors and assignment operators
void test1()
{
    BigInt x1;
    assert(x1 == BigInt());
    
    BigInt x2(1234);
    assert(x2 == BigInt("1234"));
    
    BigInt x3 = -1234;
    assert(x3 == BigInt("-1234"));
    
    BigInt x4(x3);
    assert(x4 == BigInt("-1234"));
    
    BigInt x5(std::move(x4));
    assert(x5 == BigInt("-1234"));
    
    BigInt x6 = std::move(x5);
    assert(x6 == BigInt("-1234"));
    
    BigInt x7("2147483647");
    assert(x7 == BigInt("2147483647"));
    
    BigInt x8 = std::string("-2147483648");
    assert(x8 == BigInt("-2147483648"));

    try {
        BigInt spoiled1("NaN");
    } catch (const std::invalid_argument&) {
    }
    
    try {
        BigInt spoiled2("-");
    } catch (const std::invalid_argument&) {
    }
    
    try {
        BigInt spoiled3("-34577f68");
    } catch (const std::invalid_argument&) {
    }
}

//Comparison operators
void test2()
{
    BigInt x7 = -567;
    BigInt x8(std::move(x7));
    assert(x8 == x8);
    assert(x8 != x7);

    BigInt y1(007);
    BigInt y2 = std::string("007");
    assert(y1 == y2);
    
    BigInt z1(1234);
    BigInt z2;
    z2 = z1 = y1;
    assert(z2 == z1 && z1 == y1);

    BigInt p1(-100), p2(-50), p3(0), p4(50), p5(100);
    assert(p1 < p2 && p2 < p3 && p3 < p4 && p4 < p5);
    assert(p5 > p4 && p4 > p3 && p3 > p2 && p2 > p1);
    assert(p1 < p5);
    assert(p5 > p1);
    
    BigInt p6(p1);
    BigInt p7(p5);
    assert(p6 <= p1 && p6 >= p1 && p6 == p1);
    assert(p7 <= p5 && p7 >= p5 && p7 == p5);
    assert(p1 <= p5 && p5 >= p1);
}

//Arithmetic operators
void test3()
{
    int v1 = -123456, v2 = -23456789, v3 = 0, v4 = 123456, v5 = 23456789;
    BigInt q1(v1), q2(v2), q3(v3), q4(v4), q5(v5);
    assert(q1 + q2 == BigInt(v1 + v2));
    assert(q4 + q5 == BigInt(v4 + v5));
    assert(q1 + q3 == BigInt(v1 + v3));
    assert(q1 + q4 == BigInt(v1 + v4));
    assert(q2 + q1 == BigInt(v1 + v2));
    assert(q5 + q4 == BigInt(v4 + v5));
    assert(q3 + q1 == BigInt(v1 + v3));
    assert(q4 + q1 == BigInt(v1 + v4));
    assert(q1 + -q1 == 0);
    assert(q1 + 5 == BigInt(v1 + 5));
    assert(5 + q1 == v1 + 5);


    assert(q1 - q2 == BigInt(v1 - v2));
    assert(q4 - q5 == BigInt(v4 - v5));
    assert(q1 - q3 == BigInt(v1 - v3));
    assert(q1 - q4 == BigInt(v1 - v4));
    assert(q2 - q1 == -BigInt(v1 - v2));
    assert(q5 - q4 == -BigInt(v4 - v5));
    assert(q3 - q1 == -BigInt(v1 - v3));
    assert(q4 - q1 == -BigInt(v1 - v4));
    assert(q1 - q2 == -(q2 - q1));
    assert(q1 - q1 == 0);
    assert(q1 - 5 == BigInt(v1 - 5));
    assert(5 - q1 == 5 - v1);

    assert(q1 * q2 == BigInt("2895881342784"));
    assert(q4 * q5 == BigInt("2895881342784"));
    assert(q1 * q3 == BigInt("0"));
    assert(q1 * q4 == BigInt("-15241383936"));
    assert(q2 * q1 == BigInt("2895881342784"));
    assert(q5 * q4 == BigInt("2895881342784"));
    assert(q3 * q1 == BigInt("0"));
    assert(q4 * q1 == BigInt("-15241383936"));
    assert(q1 * q2 == q2 * q1);
    assert(q1 * q1 == q4 * q4);
    assert(q1 * 0 == 0);
    assert(q1 * 5 == BigInt(v1 * 5));
    assert(5 * q1 == v1 * 5);
}

//Output operator
void test4()
{
    BigInt w1("0000000000000000000000000000000007");
    BigInt w2 = 0007;
    std::stringstream str;
    str << w1;
    assert(str.str() == "7");
    str.str("");
    str << w2;
    assert(str.str() == "7");
    str.str("");
    BigInt w3("-123456789");
    str << w3;
    assert(str.str() == "-123456789");
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
