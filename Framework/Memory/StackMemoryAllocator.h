#pragma once
#ifndef __FRAMWORK_STACK_MEMORY_ALLOCATOR
#define __FRAMWORK_STACK_MEMORY_ALLOCATOR

#include <cstdint>

#include "BufferedMemoryAllocator.h"

namespace slimenano
{

    namespace memory
    {

        class StackMemoryAllocator : public BufferedMemoryAllocator
        {
        private:
            struct Frame
            {
                Frame *m_pfLastFrame;
            };

        public:
            StackMemoryAllocator(int bufferSize);
            virtual ~StackMemoryAllocator();
            virtual int Initialize() override;
            virtual void Finalize() override;
            virtual void Tick() override;
            virtual void Reset() override;

        private:
            virtual void *Alloc(size_t size) override;
            virtual void Free(void *pointer, size_t size) override;
            uint8_t *Top();

        private:
            Frame *m_pvTopFrame;
        };

    }

}

#endif //!__FRAMWORK_STACK_MEMORY_ALLOCATOR