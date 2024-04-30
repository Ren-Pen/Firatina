#include <cstdint>

#ifdef _DEBUG
#include <cstring>
#include "DebugHelper.h"
#endif //!_DEBUG
#include "SystemMemoryAllocator.h"
#include "StackMemoryManager.h"

using namespace slimenano::unsafe;
using namespace slimenano::memory;

slimenano::memory::StackMemoryManager::StackMemoryManager(size_t bufferSize, size_t frameCapacity)
    : StackMemoryManager(SystemMemoryAllocator::Instance(), bufferSize, frameCapacity)
{
}

StackMemoryManager::StackMemoryManager(IMemoryManager &memoryAllocator, size_t bufferSize, size_t frameCapacity)
    : BufferedMemoryManager(memoryAllocator, bufferSize + sizeof(m_pvTopFrame) * frameCapacity), m_pvTopFrame(nullptr)
{
}

void StackMemoryManager::Reset()
{
    m_sUsedSize = 0;
    m_pvTopFrame = nullptr;
}

uint8_t *StackMemoryManager::Top()
{
    return m_pvTopFrame ? reinterpret_cast<uint8_t *>(m_pvTopFrame) + sizeof(m_pvTopFrame) : reinterpret_cast<uint8_t *>(Buffer());
}

void *StackMemoryManager::Alloc(size_t size)
{
    size_t new_size = sizeof(m_pvTopFrame) + size;
    if (FreeSize() < new_size)
        return nullptr;

    uint8_t *ptr = Top();

    Frame *new_top_frame = reinterpret_cast<Frame *>(ptr + size);
    new_top_frame->m_pfLastFrame = m_pvTopFrame;
    m_pvTopFrame = new_top_frame;
    m_sUsedSize += new_size;

#ifdef _DEBUG
    memset(ptr, debug::D_MEM_STACK_ALLOC, size);
#endif //!_DEBUG

    return ptr;
}

void StackMemoryManager::Free(void *pointer, size_t size)
{
    if (!m_pvTopFrame)
        return;
    uint8_t *delete_frame = reinterpret_cast<uint8_t *>(m_pvTopFrame);
    m_pvTopFrame = m_pvTopFrame->m_pfLastFrame;

    uint8_t *top = Top();
    size_t free_size = (delete_frame - top) + sizeof(Frame);
    m_sUsedSize -= free_size;
#ifdef _DEBUG
    memset(top, debug::D_MEM_STACK_FREE, free_size);
#endif //!_DEBUG
}

void StackMemoryManager::Free()
{
    Free(nullptr, 0);
}
