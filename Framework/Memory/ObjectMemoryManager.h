#pragma once
#ifndef __FRAMEWORK_OBJECT_MEMORY_MANAGER_H
#define __FRAMEWORK_OBJECT_MEMORY_MANAGER_H


#include "BufferedMemoryManager.h"

namespace slimenano
{
    namespace memory
    {

        template<typename T>
        class ObjectMemoryManager : public BufferedMemoryManager
        {
        private:
            ObjectMemoryManager(const ObjectMemoryManager &) = delete;
            ObjectMemoryManager &operator=(const ObjectMemoryManager &) = delete;
        public:
            ObjectMemoryManager(size_t maxCount);
            ObjectMemoryManager(IMemoryManager &memoryAllocator, size_t maxCount);
            virtual void Reset() override;
            virtual void *Alloc(size_t size) override;
            virtual void Free(void *pointer, size_t size) override;
            virtual void Tick() override;
        };

    }
}





#endif //!__FRAMEWORK_OBJECT_MEMORY_MANAGER_H