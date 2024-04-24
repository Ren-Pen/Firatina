#include "MemoryManager.h"

using namespace slimenano::memory;

namespace slimenano
{

    namespace memory
    {

        size_t* MemoryManager::m_pBlockSizeLookup = nullptr;
        Allocator* MemoryManager::m_pAllocators = nullptr;
        static const uint32_t kBlockSizes[] = {
            // 16bit
            4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48,
            52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96,

            // 32bit
            128, 160, 192, 224, 256, 288, 320, 352, 384,
            416, 448, 480, 512, 544, 576, 608, 640,

            // 64bit
            704, 768, 832, 896, 960, 1024};

        static const uint32_t kPageSize = 8192;
        static const uint32_t kAlignment = 4;

        static const uint32_t kNumBlockSizes = sizeof(kBlockSizes) / sizeof(kBlockSizes[0]);

        static const uint32_t kMaxBlockSize = kBlockSizes[kNumBlockSizes - 1];

    }

}

int MemoryManager::Initialize()
{
    static bool s_bInitialized = false;
    if (!s_bInitialized)
    {

        m_pBlockSizeLookup = new size_t[kMaxBlockSize + 1];
        size_t j = 0;
        for (size_t i = 0; i <= kMaxBlockSize; i++)
        {
            if (i > kBlockSizes[j])
                ++j;
            m_pBlockSizeLookup[i] = j;
        }

        m_pAllocators = new Allocator[kNumBlockSizes];
        for (size_t i = 0; i < kNumBlockSizes; i++)
        {
            m_pAllocators[i].Reset(kBlockSizes[i], kPageSize, kAlignment);
        }

        s_bInitialized = true;
    }
    return 0;
}

void MemoryManager::Finalize()
{
    delete[] m_pAllocators;
    delete[] m_pBlockSizeLookup;
}

void MemoryManager::Tick()
{
}

Allocator *MemoryManager::LookUpAllocator(size_t size)
{
    if (size <= kMaxBlockSize)
    {
        return m_pAllocators + m_pBlockSizeLookup[size];
    }
    else
    {
        return nullptr;
    }
}

void *MemoryManager::Allocate(size_t size)
{
    Allocator *pAlloc = LookUpAllocator(size);
    if (pAlloc)
    {
        return pAlloc->Allocate();
    }
    else
    {
        return malloc(size);
    }
}

void MemoryManager::Free(void *p, size_t size)
{
    Allocator *pAlloc = LookUpAllocator(size);
    if (pAlloc)
    {
        pAlloc->Free(p);
    }
    else
    {
        free(p);
    }
}