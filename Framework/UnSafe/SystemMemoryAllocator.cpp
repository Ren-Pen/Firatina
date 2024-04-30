#include <cstdlib>

#ifdef _DEBUG
#include <cstdio>
#include <cstring>
#include "DebugHelper.h"
#endif

#include "SystemMemoryAllocator.h"

using slimenano::unsafe::SystemMemoryAllocator;

SystemMemoryAllocator& SystemMemoryAllocator::Instance(){ 
    static SystemMemoryAllocator m_sInstance;
    return m_sInstance;
}

void *SystemMemoryAllocator::Alloc(size_t size)
{
    void *buffer = malloc(size);
#ifdef _DEBUG
    std::memset(buffer, debug::D_MEM_SYS_ALLOC, size);
    m_sAllocated += size;
#endif //!_DEBUG
    return buffer;
}

void SystemMemoryAllocator::Free(void *ptr, size_t size)
{
#ifdef _DEBUG
    m_sAllocated -= size;
#endif //!_DEBUG
    free(ptr);
}

SystemMemoryAllocator::SystemMemoryAllocator()
#ifdef _DEBUG
    : m_sAllocated(0)
#endif //!_DEBUG
{
}

SystemMemoryAllocator::~SystemMemoryAllocator()
{
#ifdef _DEBUG
    if (m_sAllocated)
    {
        printf_s("Memory Leak: %lld\n", m_sAllocated);
    }
#endif //!_DEBUG
}
