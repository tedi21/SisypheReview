#include "LibParsePlg.h"
#include "CPPParserInterpreter.hpp"

using namespace enc;
using namespace fctr;
using namespace interp;

extern "C" LIBPARSEPLG_API void PlugInit(va_list vl, void** res)
{
    CPPParserInterpreter<ucs>::register_class();
    *res = (void*) LOGNAME;
}

extern "C" LIBPARSEPLG_API void PlugTerm(void** res)
{
    CPPParserInterpreter<ucs>::unregister_class();
}
