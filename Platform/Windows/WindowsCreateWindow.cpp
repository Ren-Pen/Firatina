#ifdef __WIN32__
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

#include <d2d1.h>

#include <iostream>
#include <cstring>

#include "BaseApplication.h"

class Win32Window
{

public:
    Win32Window(const wchar_t *className,
                const wchar_t *title,
                int width,
                int height) : m_wcx{0},
                              m_hInstance(GetModuleHandleW(NULL)),
                              m_hHandle(NULL),
                              m_bQuit(false)
    {
        m_wcx.cbSize = sizeof(WNDCLASSEXW);
        m_wcx.style = CS_OWNDC;
        m_wcx.lpfnWndProc = &Win32Window::MainWndProc;
        m_wcx.hInstance = m_hInstance;
        m_wcx.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
        m_wcx.lpszClassName = className;
        if (!RegisterClassExW(&m_wcx))
        {
            m_bQuit = true;
            return;
        }
        m_hHandle = CreateWindowW(className, title, WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, m_hInstance, NULL);
        if (!m_hHandle)
        {
            m_bQuit = true;
            return;
        }
    }

    ~Win32Window()
    {
        if (m_hHandle)
        {
            DestroyWindow(m_hHandle);
        }
    }

    bool IsQuit()
    {
        return m_bQuit;
    }

    void Tick()
    {
        if (m_hHandle == NULL)
        {
            return;
        }
        MSG msg = {0};
        if (GetMessageW(&msg, m_hHandle, 0, 0) > 0)
        {
            DispatchMessageW(&msg);
        }
        else
        {
            m_bQuit = true;
        }
    }

    void Show()
    {
        ShowWindow(m_hHandle, SW_NORMAL | SW_SHOW);
    }

private:
    static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            RECT rec = {20, 20, 60, 80};
            HBRUSH brush = (HBRUSH)GetStockObject(BLACK_BRUSH);
            FillRect(hdc, &rec, brush);
            EndPaint(hWnd, &ps);
        }
        break;
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        break;
        }
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }

private:
    WNDCLASSEXW m_wcx;
    HINSTANCE m_hInstance;
    HWND m_hHandle;
    bool m_bQuit;
};

class CreateWindowApplication : public slimenano::BaseApplication
{

public:
    virtual int Initialize() override
    {
        m_pWindow = new Win32Window(L"MyApp", L"MyApp", 640, 480);
        if (m_pWindow->IsQuit())
        {
            m_bQuit = true;
        }
        else
        {
            m_pWindow->Show();
        }
        return 0;
    }

    virtual void Finalize() override
    {
        delete m_pWindow;
    }

    virtual void Tick() override
    {
        m_pWindow->Tick();
        if (m_pWindow->IsQuit())
        {
            m_bQuit = true;
        }
    }

private:
    Win32Window *m_pWindow = NULL;
};

CreateWindowApplication g_App;

namespace slimenano
{
    IApplication *g_pApp = &g_App;
}

#endif