#pragma once
#ifndef __FRAMEWORK_MEMEORY_MANAGER_H
#define __FRAMEWORK_MEMEORY_MANAGER_H

#include <new>

#include "IRuntimeModule.h"
#include "BlockAllocator.h"

namespace slimenano
{

    namespace memory
    {

        class MemoryManager : public IRuntimeModule
        {
        public:
            template <typename T, typename... Arguments>
            T *New(Arguments... parameters)
            {
                return new (Allocate(sizeof(T))) T(parameters...);
            }

            template <typename T>
            void Delete(T *p)
            {
                reinterpret_cast<T *>(p)->~T();
                Free(p, sizeof(T));
            }

        public:
            MemoryManager(){}
            virtual ~MemoryManager() {}

            virtual int Initialize() override;
            virtual void Finalize() override;
            virtual void Tick() override;

            void *Allocate(size_t size);
            void Free(void *p, size_t size);
        private:
            static size_t* m_pBlockSizeLookup;
            static Allocator* m_pAllocators;
        private:
            static Allocator* LookUpAllocator(size_t size);
        };

    }

}

#endif //!__FRAMEWORK_MEMEORY_MANAGER_H
