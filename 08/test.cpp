#include "threadpool.hpp"
#include <cassert>
#include <array>
#include <iostream>

void f1() {}

int f2(int x, int y)
{
    return x + y;
}

constexpr size_t size = 200;

std::array<size_t, size> f3()
{
    std::array<size_t, size> arr;
    for (size_t i = 0; i < size; ++i) {
        arr[i] = size - i - 1;
    }
    std::sort(arr.begin(), arr.end());
    return arr;
}

int f4()
{
    size_t res = 0;
    for (size_t i = 0; i < 100; ++i) {
        for (size_t j = 0; j < 100; ++j) {
            ++res;
        }
    }
    return res;
}

int main()
{
    ThreadPool pool(4);
    auto task1 = pool.exec(f1);
    auto task2 = pool.exec(f2, 1, 2);
    auto task3 = pool.exec(f3);
    auto task4 = pool.exec(f4);
    task1.get();
    assert(task2.get() == 3);
    std::array<size_t, size> arr = task3.get();
    for (size_t i = 0; i < size; ++i) {
        assert(arr[i] == i);
    }
    assert(task4.get() == 10000);

    std::cout << "All tests passed." << std::endl;
    return 0;
}