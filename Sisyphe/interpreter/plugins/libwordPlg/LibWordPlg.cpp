#include "LibWordPlg.h"
#ifdef _WIN32
#include <windows.h>
#include "WordMacroInterpreter.hpp"
#endif
#include "WordXMLInterpreter.hpp"
#include "ProgramInterpreter.hpp"
#include "StringListInterpreter.hpp"
#include "WordXMLDocumentInterpreter.hpp"
#include "WordXMLNodeListInterpreter.hpp"
#include "WordXMLNodeInterpreter.hpp"

using namespace enc;
using namespace fctr;
using namespace interp;

extern "C" LIBWORDPLG_API void PlugInit(va_list vl, void** res)
{
#ifdef _WIN32
    WordMacroInterpreter<ucs>::register_class();
#endif
    WordXMLInterpreter<ucs>::register_class();
    WordXMLDocumentInterpreter<ucs>::register_class();
    WordXMLNodeListInterpreter<ucs>::register_class();
    WordXMLNodeInterpreter<ucs>::register_class();
    StringListInterpreter<ucs>::register_class();
    StringListIteratorInterpreter<ucs>::register_class();
    *res = (void*) LOGNAME;
}

extern "C" LIBWORDPLG_API void PlugTerm(void** res)
{
#ifdef _WIN32
    WordMacroInterpreter<ucs>::unregister_class();
#endif
    WordXMLInterpreter<ucs>::unregister_class();
    WordXMLDocumentInterpreter<ucs>::unregister_class();
    WordXMLNodeListInterpreter<ucs>::unregister_class();
    WordXMLNodeInterpreter<ucs>::unregister_class();
    StringListInterpreter<ucs>::unregister_class();
    StringListIteratorInterpreter<ucs>::unregister_class();
}
