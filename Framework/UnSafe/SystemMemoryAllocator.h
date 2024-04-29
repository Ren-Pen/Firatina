#pragma once
#ifndef __FRAMWORK_SYSTEM_MEMORY_ALLOCATOR
#define __FRAMWORK_SYSTEM_MEMORY_ALLOCATOR

#include "IMemoryAllocator.h"

namespace slimenano
{
    namespace memory
    {
        class BufferedMemoryAllocator;
    }

    namespace unsafe
    {

        class SystemMemoryAllocator : private memory::IMemoryAllocator
        {
            friend slimenano::memory::BufferedMemoryAllocator;

        private:
            SystemMemoryAllocator();
            virtual ~SystemMemoryAllocator();

            virtual void *Alloc(size_t size) override;
            virtual void Free(void *pointer, size_t size) override;

        private:
#ifdef _DEBUG
            size_t m_sAllocated;
#endif //!_DEBUG
        };

    }

}

#endif //!__FRAMWORK_SYSTEM_MEMORY_ALLOCATOR