#pragma once
#ifndef __FRAMEWORK_OBJECT_MEMORY_MANAGER_H
#define __FRAMEWORK_OBJECT_MEMORY_MANAGER_H

#include <cstdint>
#include <cstring>
#include <new>

#include "SystemMemoryAllocator.h"
#include "BufferedMemoryManager.h"
#include "DebugHelper.h"

namespace slimenano
{
    namespace memory
    {

        template <class T>
        class ObjectMemoryManager : public BufferedMemoryManager
        {
        private:
            const size_t FRAME_SIZE = sizeof(T) + sizeof(void *);
            ObjectMemoryManager(const ObjectMemoryManager &) = delete;
            ObjectMemoryManager &operator=(const ObjectMemoryManager &) = delete;

        public:
            static size_t FrameSize(size_t maxCount = 1)
            {
                return (sizeof(T) + sizeof(void *)) * maxCount;
            }

        public:
            template <typename... Arguments>
            T *New(Arguments... parameters)
            {
                void *buffer = Alloc(sizeof(T));
                if (buffer)
                {
                    return new (buffer) T(parameters...);
                }
                return nullptr;
            }

            void Delete(T *tPtr)
            {
                if (tPtr)
                {
                    tPtr->~T();
                    Free(tPtr, sizeof(T));
                }
            }

        public:
            ObjectMemoryManager(size_t maxCount)
                : ObjectMemoryManager(slimenano::unsafe::SystemMemoryAllocator::Instance(), maxCount) {}

            ObjectMemoryManager(IMemoryManager &memoryAllocator, size_t maxCount)
                : BufferedMemoryManager(memoryAllocator, (sizeof(T) + sizeof(void *)) * maxCount),
                  m_sMaxCount(maxCount),
                  m_pvFree(nullptr)
            {
                Reset();
            }
            virtual void Reset() override
            {
                uint8_t *ptr = reinterpret_cast<uint8_t *>(Buffer());
                for (size_t i = 0; i < m_sMaxCount; i++)
                {
                    if (i == m_sMaxCount - 1)
                    {
                        memset(ptr + sizeof(T), 0, sizeof(void *)); // last frame
                    }
                    else
                    {
                        uint8_t *nextFree = ptr + FRAME_SIZE;
                        memcpy(ptr + sizeof(T), &nextFree, sizeof(void *));
                        ptr += FRAME_SIZE;
                    }
                }
                m_pvFree = Buffer();
            };
            virtual void *Alloc(size_t size) override
            {
                if (!m_pvFree)
                {
                    return nullptr;
                }

                void *buffer = m_pvFree;
                m_pvFree = *reinterpret_cast<void **>(reinterpret_cast<uint8_t *>(m_pvFree) + sizeof(T));
                return buffer;
            };
            virtual void Free(void *pointer, size_t size) override
            {
                void *nextFree = m_pvFree;
                m_pvFree = pointer;
                memcpy(reinterpret_cast<uint8_t *>(m_pvFree) + sizeof(T), &nextFree, sizeof(void *));
#ifdef _DEBUG
                memset(m_pvFree, debug::D_MEM_S_OBJ_FREE, sizeof(T));
#endif //! _DEBUG
            };
            virtual void Tick() override {};

        private:
            void *m_pvFree;
            size_t m_sMaxCount;
        };

    }
}

#endif //!__FRAMEWORK_OBJECT_MEMORY_MANAGER_H