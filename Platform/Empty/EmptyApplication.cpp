#include <cstdio>

#include "EmptyApplication.h"
#include "MemoryManager.h"

#undef _DEBUG

using slimenano::IApplication;
using slimenano::memory::MemoryManager;

EmptyApplication g_App;
MemoryManager memoryManager;

namespace slimenano
{
    IApplication *g_pApp = &g_App;
}

int EmptyApplication::Initialize()
{
    return memoryManager.Initialize();
}

void EmptyApplication::Tick()
{
    printf("Tick!\n");
    char* word = memoryManager.New<char>(14);
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
    memoryManager.Free(word, 14);
    this->m_bQuit = true;
}

void EmptyApplication::Finalize()
{
    memoryManager.Finalize();
}