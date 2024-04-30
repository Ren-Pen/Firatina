#pragma once
#ifndef __FRAMWORK_SINGLE_FRAME_MEMORY_MANAGER_H
#define __FRAMWORK_SINGLE_FRAME_MEMORY_MANAGER_H

#include <cstdint>

#include "BufferedMemoryManager.h"

namespace slimenano
{

    namespace memory
    {
        class SingleFrameMemoryManager : public BufferedMemoryManager
        {
        public:
            SingleFrameMemoryManager(size_t bufferSize);
            SingleFrameMemoryManager(IMemoryManager &memoryAllocator, size_t bufferSize);
            virtual void Reset() override;
            virtual void *Alloc(size_t size) override;
            virtual void Free(void *pointer, size_t size) override;
            virtual void Tick() override;
        };
    }
}

#endif //!__FRAMWORK_SINGLE_FRAME_MEMORY_MANAGER_H