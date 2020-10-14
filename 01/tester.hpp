#pragma once

#include <exception>
#include <iostream>

void assertTestPassed(bool assertion, const std::string hint)
{
    if (!assertion) {
        throw std::runtime_error(hint);
    }
}

void runTests(Allocator& allocator)
{
    assertTestPassed(allocator.alloc(1) == nullptr, "Test 1: alloc 1.");
    
    allocator.makeAllocator(1000);
    assertTestPassed(allocator.alloc(1) != nullptr, "Test 2: alloc 1.");
    assertTestPassed(allocator.alloc(999) != nullptr, "Test 3: alloc 999.");
    assertTestPassed(allocator.alloc(1) == nullptr, "Test 4: alloc 1.");
    allocator.reset();
    
    allocator.makeAllocator(500);
    assertTestPassed(allocator.alloc(501) == nullptr, "Test 5: alloc 501.");
    assertTestPassed(allocator.alloc(500) != nullptr, "Test 6: alloc 500.");
    assertTestPassed(allocator.alloc(1) == nullptr, "Test 7: alloc 1.");
}

int test()
{
    Allocator allocator = Allocator();
    try {
        runTests(allocator);
    } catch (std::runtime_error& e) {
        std::cerr << "Test failed. " << e.what() << std::endl;
        return -1;
    }
    return 0;
}