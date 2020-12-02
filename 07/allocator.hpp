#pragma once
#include <cstddef>

template<class T>
struct Allocator
{
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    
public:
    pointer allocate(size_type) const;
    void deallocate(pointer) const;
};

#include "impl/allocator.tpp"