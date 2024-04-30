#ifdef _DEBUG
#include <cstring>
#include "DebugHelper.h"
#endif //!_DEBUG
#include <cstdint>

#include "SystemMemoryAllocator.h"
#include "SingleFrameMemoryManager.h"

using namespace slimenano::unsafe;
using namespace slimenano::memory;

SingleFrameMemoryManager::SingleFrameMemoryManager(size_t bufferSize)
    : SingleFrameMemoryManager(SystemMemoryAllocator::Instance(), bufferSize)
{
}

SingleFrameMemoryManager::SingleFrameMemoryManager(IMemoryManager &memoryAllocator, size_t bufferSize)
    : BufferedMemoryManager(memoryAllocator, bufferSize)
{
}

void SingleFrameMemoryManager::Reset()
{
    this->m_sUsedSize = 0;
#ifdef _DEBUG
        memset(Buffer(), debug::D_MEM_S_FRAME_FREE, BufferSize());
#endif //!_DEBUG
}

void *SingleFrameMemoryManager::Alloc(size_t size)
{
    if (FreeSize() < size) 
    {
        return nullptr;
    }
    void* ptr = reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(Buffer()) + m_sUsedSize);
#ifdef _DEBUG
    memset(ptr, debug::D_MEM_S_FRAME_ALLOC, size);
#endif //!_DEBUG
    m_sUsedSize += size;
    return ptr;
}

void SingleFrameMemoryManager::Free(void *pointer, size_t size)
{
    // do nothing
}

void SingleFrameMemoryManager::Tick()
{
    Reset();
}
