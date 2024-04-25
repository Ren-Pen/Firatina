#include <new>
#include <cstdio>
#include "SystemMemoryAllocator.h"

using slimenano::unsafe::SystemMemoryAllocator;

SystemMemoryAllocator SystemMemoryAllocator::m_sInstance;

void *SystemMemoryAllocator::Alloc(size_t size)
{
#ifdef _DEBUG
    m_sAllocated += size;
#endif //!_DEBUG
    return ::operator new(size);
}

void SystemMemoryAllocator::Free(void *ptr, size_t size)
{
#ifdef _DEBUG
    m_sAllocated -= size;
#endif //!_DEBUG
    ::operator delete(ptr);
}

SystemMemoryAllocator *SystemMemoryAllocator::Instance()
{
    return &m_sInstance;
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
