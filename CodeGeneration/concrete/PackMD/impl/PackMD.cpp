// PackMD.cpp : Defines the entry point for the DLL application.
//

#include "PackMD.h"

namespace dsg {
    const char* SimpleMDConv::Format_Name = "{f}.md";
    const char* SimpleMDConv::Family_Name = "MD";
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" PACKMD_API void PlugInit(va_list vl, void** res)
{        
     dsg::SimpleMDConv::register_class();
}

extern "C" PACKMD_API void PlugTerm(void** res)
{        
     dsg::SimpleMDConv::unregister_class();
}
