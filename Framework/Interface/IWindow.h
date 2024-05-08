#pragma once
#ifndef __FRAMEWORK_IWINDOW_H
#define __FRAMEWORK_IWINDOW_H

#include "FrameWorkDefinitions.h"
#include "IRuntimeModule.h"

namespace slimenano
{

    namespace window
    {

        class IWindow : public IRuntimeModule
        {
        public:
            virtual ~IWindow() {}
            virtual int Initialize() = 0;
            virtual void Finalize() = 0;
            virtual void Tick() = 0;

        public:
            virtual const char* AppxId() = 0;
            virtual PLATFORM_TYPE PlatForm() = 0;

        public:
            virtual void SetVideoMode(const VIDEO_MODE *) = 0;
            // Returns an array, the last one being nullptr
            virtual VIDEO_MODE *SupportVideoModes(const WINDOW_MODE) = 0;
            virtual VIDEO_MODE *CurrentVideoMode() = 0;
            virtual WINDOW_MODE CurrentWindowMode() = 0;
        public:
            virtual void SetVisible(const bool) = 0;
            virtual bool Visible() = 0;
            // Must reset the video mode after window resized.
            virtual void SetResizable(const bool) = 0;
            virtual bool Resizable() = 0;

        public:
            virtual void SetEnable(const bool) = 0;
            virtual bool Enabled() = 0;

            virtual void SetForceFront(const bool) = 0;
            virtual bool ForceFront() = 0;

            virtual void FocusOn() = 0;
            virtual bool Focused() = 0;

        public:
            virtual void* InternalHandle() = 0;
        };

    }
}
#endif // !__FRAMEWORK_IWINDOW_H