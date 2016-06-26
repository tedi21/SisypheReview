// PackSQL.cpp : Defines the entry point for the DLL application.
//

#include "PackSQL.h"

namespace dsg {
const char * SimpleSQLConverter::Format_Name = "{f}.sql";
const char * SimpleSQLConverter::Family_Name = "sql";
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

extern "C" PACKSQL_API void PlugInit(va_list vl, void** res)
{
    dsg::SimpleSQLConverter::register_class();
}

extern "C" PACKSQL_API void PlugTerm(void** res)
{
    dsg::SimpleSQLConverter::unregister_class();
}
