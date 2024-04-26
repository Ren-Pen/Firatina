#include <new>
#include <cstdio>
#include <cstring>
#include "StackMemoryAllocator.h"

using namespace slimenano::memory;

StackMemoryAllocator::StackMemoryAllocator(int bufferSize)
    : BufferedMemoryAllocator(bufferSize + sizeof(m_pvTopFrame)), m_pvTopFrame(nullptr)
{
}

StackMemoryAllocator::~StackMemoryAllocator()
{
    Finalize();
}

int StackMemoryAllocator::Initialize()
{
    static bool f_sInitialized = false;
    if (f_sInitialized)
        return 0;
    int ret = BufferedMemoryAllocator::Initialize();
    if (ret != 0)
    {
        return ret;
    }
    if (!Buffer())
    {
        printf_s("Failed initialize stack allocator");
        return 1;
    }
    f_sInitialized = true;
    return 0;
}

void StackMemoryAllocator::Finalize()
{
    Reset();
    BufferedMemoryAllocator::Finalize();
}

void StackMemoryAllocator::Tick()
{
}

void StackMemoryAllocator::Reset()
{
    m_sUsedSize = 0;
    m_pvTopFrame = nullptr;
}

uint8_t *StackMemoryAllocator::Top()
{
    return m_pvTopFrame ? reinterpret_cast<uint8_t *>(m_pvTopFrame) + sizeof(m_pvTopFrame) : reinterpret_cast<uint8_t *>(Buffer());
}

void *StackMemoryAllocator::Alloc(size_t size)
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
    memset(ptr, 0xFE, size);
#endif //!_DEBUG

    return ptr;
}

void StackMemoryAllocator::Free(void *pointer, size_t size)
{
    if (!m_pvTopFrame)
        return;
    uint8_t *delete_frame = reinterpret_cast<uint8_t *>(m_pvTopFrame);
    m_pvTopFrame = m_pvTopFrame->m_pfLastFrame;

    uint8_t* top = Top();
    size_t free_size = (delete_frame - top) + sizeof(Frame);
    m_sUsedSize -= free_size;
#ifdef _DEBUG
    memset(top, 0xFD, free_size);
#endif //!_DEBUG
}
