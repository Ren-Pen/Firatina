
#pragma once
#ifndef __FRAMEWORK_FRAMEWORK_DEFINITIONS_H
#define __FRAMEWORK_FRAMEWORK_DEFINITIONS_H

#include <cstdint>
namespace slimenano
{

    enum PLATFORM_TYPE
    {
        WINDOWS,
        LINUX,
        MACOS,
        UNKNOWN
    };

    namespace window
    {

        enum WINDOW_MODE
        {
            WINDOWED,
            BORDERLESS,
            FULLSCREEN
        };

        struct VIDEO_MODE
        {
            const WINDOW_MODE eWindowMode;
            const uint16_t xPixels;
            const uint16_t yPixels;
            const uint8_t r;
            const uint8_t g;
            const uint8_t b;
            const char *pDesc;
        };

    }
}
#endif //!__FRAMEWORK_FRAMEWORK_DEFINITIONS_H