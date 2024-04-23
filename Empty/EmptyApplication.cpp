#include "BaseApplication.h"

namespace slimenano {
    BaseApplication g_App;
    extern IApplication* g_pApp = &g_App;
}