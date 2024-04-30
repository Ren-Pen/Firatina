#include <cstdio>

#include "EmptyApplication.h"
#include "StackMemoryManager.h"

#undef _DEBUG

using slimenano::IApplication;
using slimenano::memory::StackMemoryManager;

EmptyApplication g_App;
StackMemoryManager *g_pMemoryAllocator;

namespace slimenano
{
    IApplication *g_pApp = &g_App;
}

int EmptyApplication::Initialize()
{
    g_pMemoryAllocator = new StackMemoryManager(64);
    return g_pMemoryAllocator->Initialize();
    // return 0;
}

void EmptyApplication::Tick()
{
    printf("Tick!\n");
    g_pMemoryAllocator->Alloc(16);
    g_pMemoryAllocator->Alloc(16);
    g_pMemoryAllocator->Free();
    g_pMemoryAllocator->Free();
    g_pMemoryAllocator->Alloc(16);
    g_pMemoryAllocator->Alloc(18);
    g_pMemoryAllocator->Free();
    this->m_bQuit = true;
}

void EmptyApplication::Finalize()
{
    g_pMemoryAllocator->Finalize();
    delete g_pMemoryAllocator;
}