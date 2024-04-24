#pragma once
#ifndef __FRAMEWORK_IRUNTIME_MODULE_H
#define __FRAMEWORK_IRUNTIME_MODULE_H

namespace slimenano
{

    class IRuntimeModule
    {
    public:
        virtual ~IRuntimeModule(){};
        virtual int Initialize() = 0;
        virtual void Finalize() = 0;
        virtual void Tick() = 0;
    };

}

#endif //!__FRAMEWORK_IRUNTIME_MODULE_H
