// PackWORD.cpp : Defines the entry point for the DLL application.
//

#include "PackWORD.h"

namespace dsg {

    const char * SimpleHPPWordConv::Format_Name = "{f}.h";
	const char * SimpleHPPWordConv::Family_Name = "word";

    const char * SimpleCPPWordConv::Format_Name = "{f}.cpp";
	const char * SimpleCPPWordConv::Family_Name = "word";

    const char * SimpleHPPCOMWordConv::Format_Name = "word.h";
	const char * SimpleHPPCOMWordConv::Family_Name = "word";

    const char * SimpleCPPCOMWordConv::Format_Name = "word.cpp";
	const char * SimpleCPPCOMWordConv::Family_Name = "word";

	const char * SimpleHPPWordErrorConv::Format_Name = "word_error.h";
	const char * SimpleHPPWordErrorConv::Family_Name = "word";

	const char * SimpleCPPWordErrorConv::Format_Name = "word_error.cpp";
	const char * SimpleCPPWordErrorConv::Family_Name = "word";
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

extern "C" PACKWORD_API void PlugInit(va_list vl, void** res)
{        
    dsg::SimpleHPPWordConv::register_class();
    dsg::SimpleCPPWordConv::register_class();
    dsg::SimpleHPPCOMWordConv::register_class();
    dsg::SimpleCPPCOMWordConv::register_class();
    dsg::SimpleHPPWordErrorConv::register_class();
    dsg::SimpleCPPWordErrorConv::register_class();
}

extern "C" PACKWORD_API void PlugTerm(void** res)
{        
    dsg::SimpleHPPWordConv::unregister_class();
    dsg::SimpleCPPWordConv::unregister_class();
    dsg::SimpleHPPCOMWordConv::unregister_class();
    dsg::SimpleCPPCOMWordConv::unregister_class();
    dsg::SimpleHPPWordErrorConv::unregister_class();
    dsg::SimpleCPPWordErrorConv::unregister_class();
}
