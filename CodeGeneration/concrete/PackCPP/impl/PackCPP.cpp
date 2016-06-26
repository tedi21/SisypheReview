// PackCPP.cpp : Defines the entry point for the DLL application.
//

#include "PackCPP.h"

namespace dsg {
    const char* SimpleHPPEntityConv::Format_Name = "{f}.hpp";
	const char* SimpleHPPEntityConv::Family_Name = "cpp";

    const char* SimpleHPPAccessConv::Format_Name = "{f}Access.hpp";
	const char* SimpleHPPAccessConv::Family_Name = "cpp";

    const char* SimpleCPPAccessConv::Format_Name = "{f}Access_impl.hpp";
	const char* SimpleCPPAccessConv::Family_Name = "cpp";

	const char* SimpleHPPLogConv::Format_Name = "config.hpp";
	const char* SimpleHPPLogConv::Family_Name = "cpp";

    const char* SimpleHPPExportConv::Format_Name = "{w}Export.hpp";
    const char* SimpleHPPExportConv::Family_Name = "cpp";

    const char* SimpleHDataConv::Format_Name = "{w}Data.h";
	const char* SimpleHDataConv::Family_Name = "cpp";

    const char* SimpleHPPPredicateConv::Format_Name = "{f}Predicate.hpp";
	const char* SimpleHPPPredicateConv::Family_Name = "cpp";

    const char* SimpleHPPInterpreterConv::Format_Name = "{f}Interpreter.hpp";
	const char* SimpleHPPInterpreterConv::Family_Name = "cpp";

    const char* SimpleCPPInterpreterConv::Format_Name = "{f}Interpreter_impl.hpp";
	const char* SimpleCPPInterpreterConv::Family_Name = "cpp";

    const char* SimpleHPPInterpreterAccessConv::Format_Name = "{f}InterpreterAccess.hpp";
	const char* SimpleHPPInterpreterAccessConv::Family_Name = "cpp";

    const char* SimpleCPPInterpreterAccessConv::Format_Name = "{f}InterpreterAccess_impl.hpp";
	const char* SimpleCPPInterpreterAccessConv::Family_Name = "cpp";

    const char* SimpleCPPInterpreterDataConv::Format_Name = "{w}Interpreter.cpp";
	const char* SimpleCPPInterpreterDataConv::Family_Name = "cpp";

    const char* SimpleCPPDataConv::Format_Name = "{w}Data.cpp";
    const char* SimpleCPPDataConv::Family_Name = "cpp";

    const char* SimpleMDConv::Format_Name = "{f}.md";
    const char* SimpleMDConv::Family_Name = "cpp";

    const char* SimpleMDAccessConv::Format_Name = "{f}Access.md";
    const char* SimpleMDAccessConv::Family_Name = "cpp";
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

extern "C" PACKCPP_API void PlugInit(va_list vl, void** res)
{        
    dsg::SimpleHPPEntityConv::register_class();
    dsg::SimpleHPPAccessConv::register_class();
    dsg::SimpleCPPAccessConv::register_class();
    dsg::SimpleHPPPredicateConv::register_class();
    dsg::SimpleHPPLogConv::register_class();
    dsg::SimpleHPPExportConv::register_class();
    dsg::SimpleHDataConv::register_class();
    dsg::SimpleHPPInterpreterConv::register_class();
    dsg::SimpleCPPInterpreterConv::register_class();
    dsg::SimpleHPPInterpreterAccessConv::register_class();
    dsg::SimpleCPPInterpreterAccessConv::register_class();
    dsg::SimpleCPPInterpreterDataConv::register_class();
    dsg::SimpleCPPDataConv::register_class();
    dsg::SimpleMDConv::register_class();
    dsg::SimpleMDAccessConv::register_class();
}

extern "C" PACKCPP_API void PlugTerm(void** res)
{        
    dsg::SimpleHPPEntityConv::unregister_class();
    dsg::SimpleHPPAccessConv::unregister_class();
    dsg::SimpleCPPAccessConv::unregister_class();
    dsg::SimpleHPPPredicateConv::unregister_class();
    dsg::SimpleHPPLogConv::unregister_class();
    dsg::SimpleHPPExportConv::unregister_class();
    dsg::SimpleHDataConv::unregister_class();
    dsg::SimpleHPPInterpreterConv::unregister_class();
    dsg::SimpleCPPInterpreterConv::unregister_class();
    dsg::SimpleHPPInterpreterAccessConv::unregister_class();
    dsg::SimpleCPPInterpreterAccessConv::unregister_class();
    dsg::SimpleCPPInterpreterDataConv::unregister_class();
    dsg::SimpleCPPDataConv::unregister_class();
    dsg::SimpleMDConv::unregister_class();
    dsg::SimpleMDAccessConv::unregister_class();
}
