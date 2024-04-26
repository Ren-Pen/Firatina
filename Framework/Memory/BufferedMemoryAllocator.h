#pragma once
#ifndef __FRAMWORK_BUFFERED_MEMORY_ALLOCATOR_H
#define __FRAMWORK_BUFFERED_MEMORY_ALLOCATOR_H

#include <cstddef>
#include "IMemoryAllocator.h"
#include "SystemMemoryAllocator.h"

namespace slimenano
{
    namespace memory
    {

        class BufferedMemoryAllocator : public IMemoryAllocator
        {
        public:
            BufferedMemoryAllocator(size_t bufferSize);
            virtual ~BufferedMemoryAllocator();
            virtual int Initialize() override;
            virtual void Finalize() override;
            virtual void Tick() override;
            virtual void Reset() = 0;

        protected:
            virtual void *Alloc(size_t size) = 0;
            virtual void Free(void *pointer, size_t size) = 0;

        public:
            size_t UsedSize() const;
            size_t BufferSize() const;
            size_t FreeSize() const;

        protected:
            void* Buffer() const;

        protected:
            size_t m_sUsedSize;

        private:
            slimenano::unsafe::SystemMemoryAllocator m_mSysAllocator;
            size_t m_sBufferSize;
            void *m_pvBuffer;
        };

    }
}

#endif