#include <cstdio>

#include <cstring>
#include "EmptyApplication.h"
#include "StackMemoryManager.h"
#include "SingleFrameMemoryManager.h"
#include "ObjectMemoryManager.h"

#undef _DEBUG

using slimenano::IApplication;
using slimenano::memory::StackMemoryManager;
using slimenano::memory::SingleFrameMemoryManager;
using slimenano::memory::ObjectMemoryManager;

EmptyApplication g_App;
StackMemoryManager g_pMemoryAllocator(1024, 2);
ObjectMemoryManager<int> s1(g_pMemoryAllocator, 32);

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
    printf("Tick!\n");
    this->m_bQuit = true;
}

void EmptyApplication::Finalize()
{

}