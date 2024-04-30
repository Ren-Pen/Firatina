#include <cstdio>

#include <cstring>
#include "EmptyApplication.h"
#include "StackMemoryManager.h"
#include "SingleFrameMemoryManager.h"

#undef _DEBUG

using slimenano::IApplication;
using slimenano::memory::StackMemoryManager;
using slimenano::memory::SingleFrameMemoryManager;

EmptyApplication g_App;
StackMemoryManager g_pMemoryAllocator(64, 2);
SingleFrameMemoryManager s1(g_pMemoryAllocator, 32);
SingleFrameMemoryManager s2(g_pMemoryAllocator, 32);


namespace slimenano
{
    IApplication *g_pApp = &g_App;
}

int EmptyApplication::Initialize()
{
    return 0;
}

void EmptyApplication::Tick()
{
    s1.Tick();
    s2.Tick();
    printf("Tick!\n");
    char* c1 = reinterpret_cast<char*>(s1.Alloc(15));
    c1[14] = '\0';
    strcpy_s(c1, 15, "Hello World!!\n");
    printf_s(c1);
    this->m_bQuit = true;
}

void EmptyApplication::Finalize()
{

}