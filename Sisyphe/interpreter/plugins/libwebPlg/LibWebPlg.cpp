#include "LibWebPlg.h"
#include "JSONConverterInterpreter.hpp"
#include "JSONArrayFormatterInterpreter.hpp"
#include "JSONStructureFormatterInterpreter.hpp"
#include "HTMLFormatterInterpreter.hpp"

using namespace enc;
using namespace fctr;
using namespace interp;

extern "C" LIBWEBPLG_API void PlugInit(va_list vl, void** res)
{
    JSONConverterInterpreter<ucs>::register_class();
    JSONArrayFormatterInterpreter<ucs>::register_class();
    JSONStructureFormatterInterpreter<ucs>::register_class();
    HTMLFormatterInterpreter<ucs>::register_class();
    *res = (void*) LOGNAME;
}

extern "C" LIBWEBPLG_API void PlugTerm(void** res)
{
    JSONConverterInterpreter<ucs>::unregister_class();
    JSONArrayFormatterInterpreter<ucs>::unregister_class();
    JSONStructureFormatterInterpreter<ucs>::unregister_class();
    HTMLFormatterInterpreter<ucs>::unregister_class();
}
