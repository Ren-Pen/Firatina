#include "BufferedMemoryAllocator.h"
#include <cstdint>
#include <cstdio>

using slimenano::unsafe::SystemMemoryAllocator;
using namespace slimenano::memory;

BufferedMemoryAllocator::BufferedMemoryAllocator(size_t bufferSize)
    : m_sBufferSize(bufferSize),
      m_sUsedSize(0),
      m_mSysAllocator({}),
      m_pvBuffer(nullptr)
{
}

BufferedMemoryAllocator::~BufferedMemoryAllocator()
{
    Finalize();
}

int BufferedMemoryAllocator::Initialize()
{
    static bool f_sInitialized = false;
    if (f_sInitialized)
        return 0;
    if (m_mSysAllocator.Initialize())
    {
        printf_s("Failed initialize sys allocator");
        return 1;
    }

    if (!m_pvBuffer)
    {
        m_pvBuffer = m_mSysAllocator.Alloc(m_sBufferSize);
    }

    Reset();
    f_sInitialized = true;
    return 0;
}

void BufferedMemoryAllocator::Finalize()
{
    if (m_pvBuffer)
    {
        m_mSysAllocator.Free(m_pvBuffer, m_sBufferSize);
        m_sUsedSize = 0;
        m_pvBuffer = nullptr;
    }
    m_mSysAllocator.Finalize();
}

void BufferedMemoryAllocator::Tick()
{
}

size_t BufferedMemoryAllocator::UsedSize() const
{
    return m_sUsedSize;
}
size_t BufferedMemoryAllocator::BufferSize() const
{
    return m_sBufferSize;
}

size_t BufferedMemoryAllocator::FreeSize() const
{
    return m_sBufferSize - m_sUsedSize;
}

void* BufferedMemoryAllocator::Buffer() const
{
    return m_pvBuffer;
}