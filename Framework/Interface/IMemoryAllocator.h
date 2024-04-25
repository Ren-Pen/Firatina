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
            template <typename T, typename... Parameters>
            T *New(Parameters... parameters)
            {
                return new (Alloc(sizeof(T))) T(parameters...);
            }

            template <typename T, size_t size, typename... Parameters>
            T *New(Parameters... parameters)
            {
                return new (Alloc(sizeof(T) * size)) T[size](parameters...);
            }

            template <typename T>
            void Delete(T *p)
            {
                reinterpret_cast<T *>(p)->~T();
                Free(p, sizeof(T));
            }

            template <size_t size, typename T>
            void Delete(T *p)
            {
                for (size_t i = 0; i < size; i++)
                {
                    reinterpret_cast<T *>(p + i)->~T();
                }
                Free(p, sizeof(T) * size);
            }

        public:
            virtual ~IMemoryAllocator(){};
            virtual int Initialize() override = 0;
            virtual void Finalize() override = 0;
            virtual void Tick() override = 0;

        protected:
            virtual void *Alloc(size_t size) = 0;
            virtual void Free(void *pointer, size_t size) = 0;
        };
    }

}

#endif //!__FRAMEWORK_IMEMORY_MANAGER_H