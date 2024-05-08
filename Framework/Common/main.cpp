#include <cstdio>
#include "FrameWorkDefinitions.h"
#include "IApplication.h"

namespace slimenano
{

    extern IApplication *g_pApp;

}

int main(int argc, char **argv)
{
    using slimenano::g_pApp;
    int ret;

    if ((ret = g_pApp->Initialize()) != 0)
    {
        printf("App Initialize failed, will exit now.");
        return ret;
    }

    while (!g_pApp->IsQuit())
    {
        g_pApp->Tick();
    }

    g_pApp->Finalize();

    return 0;
}