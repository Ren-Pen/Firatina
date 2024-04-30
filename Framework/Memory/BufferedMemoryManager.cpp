#include "BufferedMemoryManager.h"
#include <cstdint>

using namespace slimenano::memory;

BufferedMemoryManager::BufferedMemoryManager(IMemoryManager &memoryAllocator, size_t bufferSize)
    : m_sBufferSize(bufferSize),
      m_sUsedSize(0),
      m_mAllocator(memoryAllocator),
      m_pvBuffer(memoryAllocator.Alloc(m_sBufferSize))
{
}

BufferedMemoryManager::~BufferedMemoryManager()
{
    if (m_pvBuffer)
    {
        m_mAllocator.Free(m_pvBuffer, m_sBufferSize);
        m_sUsedSize = 0;
        m_pvBuffer = nullptr;
    }
}

size_t BufferedMemoryManager::UsedSize() const
{
    return m_sUsedSize;
}
size_t BufferedMemoryManager::BufferSize() const
{
    return m_sBufferSize;
}

size_t BufferedMemoryManager::FreeSize() const
{
    return m_sBufferSize - m_sUsedSize;
}

void *BufferedMemoryManager::Buffer() const
{
    return m_pvBuffer;
}