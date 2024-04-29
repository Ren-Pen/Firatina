#pragma
#ifndef __FRAMEWORK_IMEMORY_MANAGER_H
#define __FRAMEWORK_IMEMORY_MANAGER_H

#include <cstddef>
#include <new>
#include "IRuntimeModule.h"

namespace slimenano
{
    namespace memory
    {

        class IMemoryAllocator : public IRuntimeModule
        {
        public:

            void* New(size_t size)
            {
                return Alloc(size);
            }

            void Delete(void* p = nullptr, size_t size = 0)
            {
                Free(p, size);
            }

            template <typename T, typename... Parameters>
            T *New(Parameters... parameters)
            {
                return new (Alloc(sizeof(T))) T(parameters...);
            }

            template <typename T>
            void Delete(T *p)
            {
                if (p){
                    reinterpret_cast<T *>(p)->~T();
                }
                Free(p, sizeof(T));
            }

        public:
            virtual ~IMemoryAllocator(){};
            virtual int Initialize() override {};
            virtual void Finalize() override {};
            virtual void Tick() override {};
            virtual void *Alloc(size_t size) = 0;
            virtual void Free(void *pointer, size_t size) = 0;
        };
    }

}

#endif //!__FRAMEWORK_IMEMORY_MANAGER_H