add_executable(LGL_CreateWindow_Win32 WindowsCreateWindow.cpp)

target_link_libraries(LGL_CreateWindow_Win32 user32.lib gdi32.lib)
target_link_libraries(LGL_CreateWindow_Win32 Common Manager Memory UnSafe)