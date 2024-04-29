#include "BufferedMemoryAllocator.h"
#include <cstdint>
#include <cstdio>

using slimenano::unsafe::SystemMemoryAllocator;
using namespace slimenano::memory;

BufferedMemoryAllocator::BufferedMemoryAllocator(IMemoryAllocator *memoryAllocator, size_t bufferSize)
    : m_sBufferSize(bufferSize),
      m_sUsedSize(0),
      m_mAllocator(memoryAllocator),
      m_pvBuffer(nullptr)
{
    m_pvBuffer = memoryAllocator->Alloc(m_sBufferSize);
}

BufferedMemoryAllocator::~BufferedMemoryAllocator()
{
    if (m_pvBuffer)
    {
        Reset();
        m_mAllocator->Free(m_pvBuffer, m_sBufferSize);
        m_sUsedSize = 0;
        m_pvBuffer = nullptr;
    }
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

void *BufferedMemoryAllocator::Buffer() const
{
    return m_pvBuffer;
}