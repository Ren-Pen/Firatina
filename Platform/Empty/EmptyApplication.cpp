#include <cstdio>

#include "EmptyApplication.h"
#include "SystemMemoryAllocator.h"

#undef _DEBUG

using slimenano::IApplication;
using slimenano::unsafe::SystemMemoryAllocator;

EmptyApplication g_App;
SystemMemoryAllocator* g_pMemoryManager = SystemMemoryAllocator::Instance();

namespace slimenano
{
    IApplication *g_pApp = &g_App;
}

int EmptyApplication::Initialize()
{
    return g_pMemoryManager->Initialize();
}

void EmptyApplication::Tick()
{
    printf("Tick!\n");
    char *word = g_pMemoryManager->New<char, 16>();
    word[0] = 'H';
    word[1] = 'E';
    word[2] = 'L';
    word[3] = 'L';
    word[4] = 'O';
    word[5] = ' ';
    word[6] = 'W';
    word[7] = 'O';
    word[8] = 'R';
    word[9] = 'L';
    word[10] = 'D';
    word[11] = '!';
    word[12] = '\n';
    word[13] = '\0';
    printf(word);
    g_pMemoryManager->Delete<16>(word);
    this->m_bQuit = true;
}

void EmptyApplication::Finalize()
{
    g_pMemoryManager->Finalize();
}