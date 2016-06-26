// PackINTERPRETER.cpp : Defines the entry point for the DLL application.
//

#include "PackINTERPRETER.h"

namespace dsg {
    const char* SimpleHPPInterpreterConv::Format_Name = "{f}Interpreter.hpp";
    const char* SimpleHPPInterpreterConv::Family_Name = "interpreter";

    const char* SimpleCPPInterpreterConv::Format_Name = "{f}Interpreter_impl.hpp";
    const char* SimpleCPPInterpreterConv::Family_Name = "interpreter";

    const char* SimpleCPPDataInterpreterConv::Format_Name = "{w}Interpreter.cpp";
    const char* SimpleCPPDataInterpreterConv::Family_Name = "interpreter";
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

extern "C" PACKINTERPRETER_API void PlugInit(va_list vl, void** res)
{        
     dsg::SimpleHPPInterpreterConv::register_class();
     dsg::SimpleCPPInterpreterConv::register_class();
     dsg::SimpleCPPDataInterpreterConv::register_class();
}

extern "C" PACKINTERPRETER_API void PlugTerm(void** res)
{        
     dsg::SimpleHPPInterpreterConv::unregister_class();
     dsg::SimpleCPPInterpreterConv::unregister_class();
     dsg::SimpleCPPDataInterpreterConv::unregister_class();
}
