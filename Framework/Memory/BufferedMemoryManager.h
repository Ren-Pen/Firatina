#pragma once
#ifndef __FRAMWORK_BUFFERED_MEMORY_ALLOCATOR_H
#define __FRAMWORK_BUFFERED_MEMORY_ALLOCATOR_H

#include <cstddef>
#include "IMemoryManager.h"

namespace slimenano
{
    namespace memory
    {

        class BufferedMemoryManager : public IMemoryManager
        {
        private:
            BufferedMemoryManager(const BufferedMemoryManager &) = delete;
            BufferedMemoryManager &operator=(const BufferedMemoryManager &) = delete;

        public:
            BufferedMemoryManager(IMemoryManager &memoryManager, size_t bufferSize);
            virtual ~BufferedMemoryManager();
            virtual void Reset() = 0;
            virtual void *Alloc(size_t size) override = 0;
            virtual void Free(void *pointer, size_t size) override = 0;
            virtual int Initialize() override { return 0; };
            virtual void Finalize() override {};
            virtual void Tick() override {};

        public:
            size_t UsedSize() const;
            size_t BufferSize() const;
            size_t FreeSize() const;

        protected:
            void *Buffer() const;

        protected:
            size_t m_sUsedSize;

        private:
            IMemoryManager &m_mAllocator;
            const size_t m_sBufferSize;
            void *m_pvBuffer;
        };

    }
}

#endif