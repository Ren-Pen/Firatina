#pragma once
#ifndef __FRAMWORK_SYSTEM_MEMORY_ALLOCATOR_H
#define __FRAMWORK_SYSTEM_MEMORY_ALLOCATOR_H

#include "IMemoryManager.h"

namespace slimenano
{

    namespace unsafe
    {

        class SystemMemoryAllocator : public memory::IMemoryManager
        {
        private:
            SystemMemoryAllocator(const SystemMemoryAllocator&) = delete;
            SystemMemoryAllocator& operator=(const SystemMemoryAllocator&) = delete;
            SystemMemoryAllocator();
        public:
            virtual ~SystemMemoryAllocator();
            virtual void *Alloc(size_t size) override;
            virtual void Free(void *pointer, size_t size) override;
            virtual int Initialize() override { return 0; };
            virtual void Finalize() override {};
            virtual void Tick() override {};

        public:
            static SystemMemoryAllocator& Instance();
#ifdef _DEBUG
            size_t m_sAllocated;
#endif //!_DEBUG
        };

    }

}

#endif //!__FRAMWORK_SYSTEM_MEMORY_ALLOCATOR_H