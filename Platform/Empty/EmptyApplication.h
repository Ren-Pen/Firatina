#pragma once
#ifndef __PLATFORM_EMPTY_APPLICATION_H
#define __PLATFORM_EMPTY_APPLICATION_H

#include "BaseApplication.h"

class EmptyApplication : public slimenano::BaseApplication
{

    virtual int Initialize() override;
    virtual void Finalize() override;
	virtual void Tick() override;

};

#endif //!__PLATFORM_EMPTY_APPLICATION_H