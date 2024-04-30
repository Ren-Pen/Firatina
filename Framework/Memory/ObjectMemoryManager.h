#pragma once
#ifndef __FRAMEWORK_OBJECT_MEMORY_MANAGER_H
#define __FRAMEWORK_OBJECT_MEMORY_MANAGER_H

#include <cstdint>

#include "BufferedMemoryManager.h"

namespace slimenano
{
    namespace memory
    {

        template <typename T>
        class ObjectMemoryManager : public BufferedMemoryManager
        {
        private:
            ObjectMemoryManager(const ObjectMemoryManager &) = delete;
            ObjectMemoryManager &operator=(const ObjectMemoryManager &) = delete;

        public:
            ObjectMemoryManager(size_t maxCount)
                : ObjectMemoryManager(SystemMemoryAllocator::Instance(), maxCount) {}

            ObjectMemoryManager(IMemoryManager &memoryAllocator, size_t maxCount)
                : BufferedMemoryManager(memoryAllocator, (sizeof(T) + sizeof(void *)) * maxCount)
            {
                const size_t FRAME_SIZE = sizeof(T) + sizeof(void *);
                uint8_t *ptr = reinterpret_cast<uint8_t *>(Buffer());
                for (size_t i = 0; i < maxCount; i++)
                {
                    uint8_t *nextFree = ptr + FRAME_SIZE;
                    memcpy(ptr + sizeof(T), &nextFree, sizeof(void *));
                    ptr += FRAME_SIZE;
                }
            }
            virtual void Reset() override {};
            virtual void *Alloc(size_t size) override { return nullptr; };
            virtual void Free(void *pointer, size_t size) override {};
            virtual void Tick() override {};

        private:
            void *m_pvFree;
        };

    }
}

#endif //!__FRAMEWORK_OBJECT_MEMORY_MANAGER_H