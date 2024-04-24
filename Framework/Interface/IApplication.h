#pragma once
#ifndef __FRAMEWORK_IAPPLICATION_H
#define __FRAMEWORK_IAPPLICATION_H

#include "IRuntimeModule.h"

namespace slimenano
{

    class IApplication : public IRuntimeModule
    {
    public:
        virtual ~IApplication() {}
        virtual int Initialize() override = 0;
        virtual void Finalize() override = 0;
        virtual void Tick() override = 0;
        virtual bool IsQuit() = 0;
    };

}

#endif