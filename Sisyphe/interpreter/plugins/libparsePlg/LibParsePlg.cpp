#include "LibParsePlg.h"
#include "CPPParserInterpreter.hpp"
#include "GitInterpreter.hpp"
#include "GitRepositoryInterpreter.hpp"
#include "GitBlameInterpreter.hpp"

using namespace enc;
using namespace fctr;
using namespace interp;

extern "C" LIBPARSEPLG_API void PlugInit(va_list vl, void** res)
{
    CPPParserInterpreter<ucs>::register_class();
    GitInterpreter<ucs>::register_class();
    GitRepositoryInterpreter<ucs>::register_class();
    GitBlameInterpreter<ucs>::register_class();
    *res = (void*) LOGNAME;
}

extern "C" LIBPARSEPLG_API void PlugTerm(void** res)
{
    CPPParserInterpreter<ucs>::unregister_class();
    GitInterpreter<ucs>::unregister_class();
    GitRepositoryInterpreter<ucs>::unregister_class();
    GitBlameInterpreter<ucs>::unregister_class();
}
