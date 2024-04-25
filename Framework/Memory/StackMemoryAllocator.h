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
        private:
            StackMemoryAllocator(){}
        public:
            virtual ~StackMemoryAllocator(){};
            virtual int Initialize() override;
            virtual void Finalize() override;
            virtual void Tick() override;

        private:
            virtual void *Alloc(size_t size) override;
            virtual void Free(void *pointer, size_t size) override;
        private:
            
        };

    }

}

#endif //!__FRAMWORK_STACK_MEMORY_ALLOCATOR