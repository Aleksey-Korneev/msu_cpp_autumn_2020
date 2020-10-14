#include "allocator.hpp"
#include <cstddef>

Allocator::Allocator()
{
	data_ptr = nullptr;
	created = false;
}

void Allocator::makeAllocator(size_t maxSize)
{
	if (!created) {
		data_ptr = new char[maxSize];
		created = true;
		allocator_size = maxSize;
		offset = 0;
	} else if (created && offset == 0) {
        allocator_size = maxSize;
    }
}

char* Allocator::alloc(size_t size)
{
	if (created && allocator_size - offset >= size) {
		offset += size;
		return data_ptr + (offset - size);
	}
	return nullptr;
}

void Allocator::reset()
{
	offset = 0;
}

Allocator::~Allocator()
{
	if (created) {
		delete[] data_ptr;
		created = false;
	}
}