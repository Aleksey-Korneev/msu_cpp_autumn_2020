#include "allocator.hpp"
#include "iterator.hpp"
#include "vector.hpp"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <sstream>
#include <exception>

template<class T, class V_Allocator>
void print(const Vector<T, V_Allocator>& v)
{
    std::cout << '{';
    if (!v.empty()) {
        std::cout << v[0];
    }
    for (size_t i = 1; i < v.size(); ++i) { 
        std::cout << ", " << v[i];
    }
    std::cout << '}' << std::endl << std::endl;
}

template<class T, class V_Allocator>
void print_vector_info(const Vector<T, V_Allocator>& v)
{
    std::cout << "Vector: is empty = " << (v.empty() ? "true" : "false")
            << ", size = " << v.size() <<
            ", capacity = " << v.capacity() << std::endl;
    print(v);
}

//Checking the correctness of constructors and assignment operators
void test1()
{
    std::cout << __func__ << std::endl;
    Vector<int> v1;
    print_vector_info(v1);
    Vector<int> v2(10);
    print_vector_info(v2);
    Vector<int> v3(10, 5);
    print_vector_info(v3);
    Vector<int> v4(v3);
    print_vector_info(v4);
    Vector<int> v5(std::move(v4));
    print_vector_info(v5);
    Vector<int> v6(v3.begin(), v3.end());
    print_vector_info(v6);
    Vector<int> v7({ 1, 2, 3, 4, 5 });
    print_vector_info(v7);
    Vector<int> v8(v7.begin(), v7.end());
    print_vector_info(v8);
    v1 = v7;
    print_vector_info(v1);
    v1 = std::move(v7);
    print_vector_info(v1);
}

//Access to elements
void test2()
{
    std::cout << std::endl << __func__ << std::endl;
    Vector<std::string> v = { "abc", "def", "ghi", "jkl", "mno" };
    assert(v.size() == 5 && v.capacity() == 5);
    v[0] = v[1] = "New string";
    assert(v[0] == "New string");
    assert(v[1] == "New string");
    try {
        std::string tmp = v.at(5);
    } catch(const std::exception& e) {
        std::cout << "Caught an expected exception: " << e.what() << std::endl;
    }

}

//Modifiers
void test3()
{
    std::cout << std::endl << __func__ << std::endl;
    Vector<int> v({ 1, 2, 3, 4, 5});
    v.push_back(6);
    int x = 7;
    v.push_back(std::move(x));
    v.emplace_back(8);
    v.emplace_back(9);
    v.emplace_back(10);
    v.emplace_back(11);
    assert(v.size() == 11 && v.capacity() == 20);
    v.shrink_to_fit();
    assert(v.size() == v.capacity());
    v.resize(16, -1);
    assert(v == Vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, -1, -1, -1, -1, -1}));
    v.pop_back();
    print_vector_info(v);
    v.clear();
    assert(v.size() == 0);
    try {
        v.pop_back();
    } catch(const std::out_of_range& e) {
        std::cout << "Caught an expected exception: " << e.what() << std::endl;
    }
    assert(v.begin() == v.end() && v.rbegin() == v.rend());
}

//Iterators
void test4()
{
    std::cout << std::endl << __func__ << std::endl;
    Vector<int> v({ 1, 2, 3, 4, 5 });
    std::stringstream str;
    for (Vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        str << *it << ' ';
    }
    assert(str.str() == "1 2 3 4 5 ");
    str.str("");
    for (Vector<int>::iterator it = v.rbegin(); it != v.rend(); ++it) {
        str << *it << ' ';
    }
    assert(str.str() == "5 4 3 2 1 ");
    assert(v.end() - v.begin() == static_cast<int>(v.size()));
    assert(++(++v.begin()) == --(--(--v.end())));
    assert(*(++(++v.begin())) == *(++(++v.rbegin())));
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
