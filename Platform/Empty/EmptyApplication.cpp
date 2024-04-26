#include <cstdio>

#include "EmptyApplication.h"
#include "StackMemoryAllocator.h"

#undef _DEBUG

using slimenano::IApplication;
using slimenano::memory::StackMemoryAllocator;

EmptyApplication g_App;
StackMemoryAllocator *g_pMemoryAllocator;

namespace slimenano
{
    IApplication *g_pApp = &g_App;
}

int EmptyApplication::Initialize()
{
    g_pMemoryAllocator = new StackMemoryAllocator(64);
    return g_pMemoryAllocator->Initialize();
    // return 0;
}

void EmptyApplication::Tick()
{
    printf("Tick!\n");
    g_pMemoryAllocator->New(16);
    g_pMemoryAllocator->New(16);
    g_pMemoryAllocator->Delete();
    g_pMemoryAllocator->Delete();
    g_pMemoryAllocator->New(16);
    g_pMemoryAllocator->New(18);
    g_pMemoryAllocator->Delete();
    this->m_bQuit = true;
}

void EmptyApplication::Finalize()
{
    g_pMemoryAllocator->Finalize();
    delete g_pMemoryAllocator;
}