#pragma once

#include <cstddef>

class Allocator
{    
    char *data_ptr;
    size_t allocator_size;
    size_t offset;
    bool created;
public:
    Allocator();
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};