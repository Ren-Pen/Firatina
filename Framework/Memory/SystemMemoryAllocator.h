#pragma once
#ifndef __FRAMWORK_SYSTEM_MEMORY_ALLOCATOR
#define __FRAMWORK_SYSTEM_MEMORY_ALLOCATOR

#include "IMemoryAllocator.h"

namespace slimenano
{

    namespace unsafe
    {

        class SystemMemoryAllocator : public memory::IMemoryAllocator
        {
        public:
            static SystemMemoryAllocator* Instance();
            virtual int Initialize() override;
            virtual void Finalize() override;
            virtual void Tick() override;
        private:
            static SystemMemoryAllocator m_sInstance;
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