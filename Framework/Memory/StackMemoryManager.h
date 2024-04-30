#pragma once
#ifndef __FRAMWORK_STACK_MEMORY_ALLOCATOR
#define __FRAMWORK_STACK_MEMORY_ALLOCATOR

#include <cstdint>

#include "BufferedMemoryManager.h"

namespace slimenano
{

    namespace memory
    {

        class StackMemoryManager : public BufferedMemoryManager
        {
        private:
            struct Frame
            {
                Frame *m_pfLastFrame;
            };
            StackMemoryManager(const StackMemoryManager &) = delete;
            StackMemoryManager &operator=(const StackMemoryManager &) = delete;

        public:
            StackMemoryManager(size_t bufferSize, size_t frameCapacity = 1);
            StackMemoryManager(IMemoryManager &memoryAllocator, size_t bufferSize, size_t frameCapacity = 1);
            virtual void Reset() override;
            virtual void *Alloc(size_t size) override;
            virtual void Free(void *pointer, size_t size) override;
            void Free();
            uint8_t *Top();

        private:
            Frame *m_pvTopFrame;
        };

    }

}

#endif //!__FRAMWORK_STACK_MEMORY_ALLOCATOR