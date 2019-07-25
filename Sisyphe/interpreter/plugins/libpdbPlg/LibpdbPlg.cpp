#include "LibpdbPlg.h"
#include <windows.h>
#include "ProgramInterpreter.hpp"
#include "PdbParserInterpreter.hpp"
#include "IDiaDataSourcePtrInterpreter.hpp"
#include "IDiaSessionPtrInterpreter.hpp"
#include "IDiaSymbolPtrInterpreter.hpp"
#include "IDiaEnumSymbolsPtrInterpreter.hpp"
#include "SymTagEnumTypeInterpreter.hpp"
#include "NameSearchOptionsInterpreter.hpp"
#include "IDiaLineNumberPtrInterpreter.hpp"
#include "IDiaEnumLineNumbersPtrInterpreter.hpp"
#include "IDiaSourceFilePtrInterpreter.hpp"
#include "IDiaEnumSourceFilesPtrInterpreter.hpp"
#include "IDiaEnumSymbolsByAddrPtrInterpreter.hpp"
#include "IDiaEnumTablesPtrInterpreter.hpp"
#include "IDiaTablePtrInterpreter.hpp"
#include "DataKindInterpreter.hpp"
#include "BasicTypeInterpreter.hpp"

using namespace enc;
using namespace fctr;
using namespace interp;

extern "C" LIBPDBPLG_API void PlugInit(va_list vl, void** res)
{
    PdbParserInterpreter<ucs>::register_class();
    IDiaDataSourcePtrInterpreter<ucs>::register_class();
    IDiaSessionPtrInterpreter<ucs>::register_class();
    IDiaSymbolPtrInterpreter<ucs>::register_class();
    IDiaEnumSymbolsPtrInterpreter<ucs>::register_class();
    SymTagEnumTypeInterpreter<ucs>::register_class();
    NameSearchOptionsInterpreter<ucs>::register_class();
    IDiaLineNumberPtrInterpreter<ucs>::register_class();
    IDiaEnumLineNumbersPtrInterpreter<ucs>::register_class();
    IDiaSourceFilePtrInterpreter<ucs>::register_class();
    IDiaEnumSourceFilesPtrInterpreter<ucs>::register_class();
    IDiaTablePtrInterpreter<ucs>::register_class();
    IDiaEnumTablesPtrInterpreter<ucs>::register_class();
    IDiaEnumSymbolsByAddrPtrInterpreter<ucs>::register_class();
    DataKindInterpreter<ucs>::register_class();
    BasicTypeInterpreter<ucs>::register_class();
    *res = (void*) LOGNAME;
}

extern "C" LIBPDBPLG_API void PlugTerm(void** res)
{
    PdbParserInterpreter<ucs>::unregister_class();
    IDiaDataSourcePtrInterpreter<ucs>::unregister_class();
    IDiaSessionPtrInterpreter<ucs>::unregister_class();
    IDiaSymbolPtrInterpreter<ucs>::unregister_class();
    IDiaEnumSymbolsPtrInterpreter<ucs>::unregister_class();
    SymTagEnumTypeInterpreter<ucs>::unregister_class();
    NameSearchOptionsInterpreter<ucs>::unregister_class();
    IDiaLineNumberPtrInterpreter<ucs>::unregister_class();
    IDiaEnumLineNumbersPtrInterpreter<ucs>::unregister_class();
    IDiaSourceFilePtrInterpreter<ucs>::unregister_class();
    IDiaEnumSourceFilesPtrInterpreter<ucs>::unregister_class();
    IDiaTablePtrInterpreter<ucs>::unregister_class();
    IDiaEnumTablesPtrInterpreter<ucs>::unregister_class();
    IDiaEnumSymbolsByAddrPtrInterpreter<ucs>::unregister_class();
    DataKindInterpreter<ucs>::unregister_class();
    BasicTypeInterpreter<ucs>::unregister_class();
}
