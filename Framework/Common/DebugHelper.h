#ifdef _DEBUG

#pragma once

#ifndef __FRAMEWORK_DEBUG_HELPER_H
#define __FRAMEWORK_DEBUG_HELPER_H

    namespace slimenano
    {
        namespace debug
        {
            const unsigned char D_MEM_SYS_ALLOC = 0xFF;
            const unsigned char D_MEM_STACK_ALLOC = 0xFE;
            const unsigned char D_MEM_STACK_FREE = 0xFD;
            const unsigned char D_MEM_S_FRAME_ALLOC = 0xFC;
            const unsigned char D_MEM_S_FRAME_FREE = 0xFB;
        }
    }

#endif //!__FRAMEWORK_DEBUG_HELPER_H

#endif //!_DEBUG