#pragma once
#ifndef __FRAMWORK_STACK_MEMORY_ALLOCATOR
#define __FRAMWORK_STACK_MEMORY_ALLOCATOR

#include "IMemoryAllocator.h"

namespace slimenano
{

    namespace memory
    {

        class StackMemoryAllocator : public IMemoryAllocator
        {
        public:
            virtual ~StackMemoryAllocator(){};
            virtual int Initialize() override { return 0; };
            virtual void Finalize() override{};
            virtual void Tick() override{};

        protected:
            virtual void *Alloc(size_t size);
            virtual void Free(void *pointer, size_t size);
        };

    }

}

#endif //!__FRAMWORK_STACK_MEMORY_ALLOCATOR