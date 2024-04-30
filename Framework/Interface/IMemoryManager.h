#pragma once
#ifndef __FRAMEWORK_IMEMORY_MANAGER_H
#define __FRAMEWORK_IMEMORY_MANAGER_H

#include <cstddef>
#include <new>
#include "IRuntimeModule.h"

namespace slimenano
{
    namespace memory
    {

        class IMemoryManager : public IRuntimeModule
        {
        public:
            virtual ~IMemoryManager(){};
            virtual int Initialize() override = 0;
            virtual void Finalize() override = 0;
            virtual void Tick() override = 0;
            virtual void *Alloc(size_t size) = 0;
            virtual void Free(void *pointer, size_t size) = 0;
        };
    }

}

#endif //!__FRAMEWORK_IMEMORY_MANAGER_H