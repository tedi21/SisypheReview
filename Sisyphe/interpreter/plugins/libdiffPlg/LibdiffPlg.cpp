#include "LibDiffPlg.h"
#include "DiffInterpreter.hpp"
#include "DiffTypeInterpreter.hpp"
#include "DiffValueInterpreter.hpp"

using namespace enc;
using namespace fctr;
using namespace interp;

extern "C" LIBDIFFPLG_API void PlugInit(va_list vl, void** res)
{
    DiffInterpreter<ucs>::register_class();
    DiffTypeInterpreter<ucs>::register_class();
    DiffValueInterpreter<ucs>::register_class();
    *res = (void*) LOGNAME;
}

extern "C" LIBDIFFPLG_API void PlugTerm(void** res)
{
    DiffInterpreter<ucs>::unregister_class();
    DiffTypeInterpreter<ucs>::unregister_class();
    DiffValueInterpreter<ucs>::unregister_class();
}
