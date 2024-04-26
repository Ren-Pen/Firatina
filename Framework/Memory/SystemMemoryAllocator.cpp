#include <new>

#ifdef _DEBUG
#include <cstdio>
#include <cstring>
#endif

#include "SystemMemoryAllocator.h"

using slimenano::unsafe::SystemMemoryAllocator;

void *SystemMemoryAllocator::Alloc(size_t size)
{
    void *buffer = ::operator new(size);
#ifdef _DEBUG
    std::memset(buffer, 0xFF, size);
    m_sAllocated += size;
#endif //!_DEBUG
    return buffer;
}

void SystemMemoryAllocator::Free(void *ptr, size_t size)
{
#ifdef _DEBUG
    m_sAllocated -= size;
#endif //!_DEBUG
    ::operator delete(ptr);
}

int SystemMemoryAllocator::Initialize()
{
    return 0;
}

void SystemMemoryAllocator::Finalize()
{
#ifdef _DEBUG
    if (m_sAllocated)
    {
        printf_s("Memory Leak: %lld\n", m_sAllocated);
    }
#endif //!_DEBUG
}

void SystemMemoryAllocator::Tick()
{
}

SystemMemoryAllocator::SystemMemoryAllocator()
#ifdef _DEBUG
    : m_sAllocated(0)
#endif //!_DEBUG
{
}

SystemMemoryAllocator::~SystemMemoryAllocator()
{
}
