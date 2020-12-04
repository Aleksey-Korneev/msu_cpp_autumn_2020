#include <cassert>
#include "format.hpp"

struct UserType {
    int x;
    int y;
    UserType(int x_, int y_) : x(x_), y(y_)
    {
    }
    friend std::ostream& operator<< (std::ostream &out, const UserType& user_type)
    {
        out << "struct UserType { x = " << user_type.x << "; y = " << user_type.y << "; }";
        return out;
    }
};

struct AnotherUserType {
    int x;
    int y;
    AnotherUserType(int x_, int y_) : x(x_), y(y_)
    {
    }
};

void print_info(const std::string &test_str,
        const std::string &expected_res, const std::string &res)
{
    static size_t cnt = 0;
    std::cout << "Test " << ++cnt << std::endl;
    std::cout << "test_str     = " << test_str << std::endl;
    std::cout << "expected_res = " << expected_res << std::endl;
    std::cout << "res          = " << res << std::endl;
    std::cout << std::endl;
}

void run_tests()
{
    //Test 1. A string with no argument fields
    std::string test_str = "An ordinary string () <>";
    std::string expected_res(test_str);
    std::stringstream res;
    try {
        res << format(test_str);
    } catch(const InvalidFormat& e) {
        res << "Caught an exception (InvalidFormat): " << e.what();
    }
    print_info(test_str, expected_res, res.str());
    assert(res.str() == expected_res);
    res.str(std::string());
    
    //Test 2. A string with multiple argument fields
    test_str = "{2} {3} {1} {4} {0} {5}";
    expected_res = "Hello, world! My name is Aleksey.";
    try {
        res << format(test_str, "is", "My", "Hello,", "world!", "name", "Aleksey.");
    } catch(const InvalidFormat& e) {
        res << "Caught an exception (InvalidFormat): " << e.what();
    }
    print_info(test_str, expected_res, res.str());
    assert(res.str() == expected_res);
    res.str(std::string());
        
    //Test 3. A string with user-defined data type with overloaded operator '<<'
    test_str = "int: {0}; double: {1}; char: {2}; string: {3}; UserType: {4}";
    expected_res = "int: 999999; double: 123.456; char: x; "
            "string: \"String 1\"; UserType: struct UserType { x = 0; y = 0; }";
    try {
        res << format(test_str, 999999, 123.456, 'x', "\"String 1\"", UserType(0, 0));
    } catch(const InvalidFormat& e) {
        res << "Caught an exception (InvalidFormat): " << e.what();
    }
    print_info(test_str, expected_res, res.str());
    assert(res.str() == expected_res);
    res.str(std::string());

    //Test 4. A string with an extra opening brace
    test_str = "Here is one { extra opening brace.";
    expected_res = "Caught an exception (InvalidFormat): Unexpected opening brace.";
    try {
        res << format(test_str, "Extra parameters are not banned");
    } catch(const InvalidFormat& e) {
        res << "Caught an exception (InvalidFormat): " << e.what();
    }
    print_info(test_str, expected_res, res.str());
    assert(res.str() == expected_res);
    res.str(std::string());
    
    //Test 5. A string with an extra closing brace
    test_str = "H}ere is one extra closing brace.";
    expected_res = "Caught an exception (InvalidFormat): Unexpected closing brace.";
    try {
        res << format(test_str);
    } catch(const InvalidFormat& e) {
        res << "Caught an exception (InvalidFormat): " << e.what();
    }
    print_info(test_str, expected_res, res.str());
    assert(res.str() == expected_res);
    res.str(std::string());
    
    //Test 6. A string with a violation of order of braces (case "}{")
    test_str = "}1{";
    expected_res = "Caught an exception (InvalidFormat): Unexpected closing brace.";
    try {
        res << format(test_str);
    } catch(const InvalidFormat& e) {
        res << "Caught an exception (InvalidFormat): " << e.what();
    }
    print_info(test_str, expected_res, res.str());
    assert(res.str() == expected_res);
    res.str(std::string());
    
    //Test 7. A string with a violation of order of braces (case "{{}}")
    test_str = "Violated order {{0}}";
    expected_res = "Caught an exception (InvalidFormat): Unexpected opening brace.";
    try {
        res << format(test_str, 0);
    } catch(const InvalidFormat& e) {
        res << "Caught an exception (InvalidFormat): " << e.what();
    }
    print_info(test_str, expected_res, res.str());
    assert(res.str() == expected_res);
    res.str(std::string());
    
    //Test 8. A string with an appeal to the argument index out of range
    test_str = "Only one argument {1}";
    expected_res = "Caught an exception (InvalidValue): Argument index out of range.";
    try {
        res << format(test_str, 0);
    } catch(const InvalidValue& e) {
        res << "Caught an exception (InvalidValue): " << e.what();
    }
    print_info(test_str, expected_res, res.str());
    assert(res.str() == expected_res);
    res.str(std::string());
}

int main()
{
    run_tests();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
