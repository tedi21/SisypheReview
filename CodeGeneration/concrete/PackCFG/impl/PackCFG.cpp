// PackCFG.cpp : Defines the entry point for the DLL application.
//

#include "PackCFG.h"
#include "FileCFGParser.hpp"

using namespace cfg;

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

extern "C" PACKCFG_API void PlugInit(va_list vl, void** res)
{
    FileCFGParser::register_class();
}

extern "C" PACKCFG_API void PlugTerm(void** res)
{        
    FileCFGParser::unregister_class();
}
