#include <new>
#include "StackMemoryAllocator.h"

using namespace slimenano::memory;

void *StackMemoryAllocator::Alloc(size_t size)
{
    return ::operator new(size);
}

void StackMemoryAllocator::Free(void *ptr, size_t size)
{
    ::operator delete(ptr);
}