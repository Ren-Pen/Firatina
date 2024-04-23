#pragma once
#ifndef __FRAMWORK_GRAPHICS_MANAGER_H
#define __FRAMWORK_GRAPHICS_MANAGER_H

#include "IRuntimeModule.h" 
namespace slimenano {

    class GraphicsManager : public IRuntimeModule
    {
    public:
        virtual ~GraphicsManager() {}
    };

}

#endif // !__FRAMWORK_GRAPHICS_MANAGER_H
