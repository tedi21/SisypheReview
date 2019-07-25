#include <windows.h>
#include "ProgramInterpreter.hpp"
#include "PdbParserInterpreter.hpp"
#include "IDiaDataSourcePtrInterpreter.hpp"
#include "IDiaSessionPtrInterpreter.hpp"
#include "IDiaEnumTablesPtrInterpreter.hpp"
#include "IDiaEnumSymbolsByAddrPtrInterpreter.hpp"
#include "IDiaSymbolPtrInterpreter.hpp"
#include "IDiaEnumSymbolsPtrInterpreter.hpp"
#include "IDiaLineNumberPtrInterpreter.hpp"
#include "IDiaEnumLineNumbersPtrInterpreter.hpp"
#include "IDiaSourceFilePtrInterpreter.hpp"
#include "IDiaEnumSourceFilesPtrInterpreter.hpp"
#include "IDiaTablePtrInterpreter.hpp"

using namespace enc;
using namespace fctr;
using namespace interp;

//////////////////////////////////////////
// Exportation des classes
//////////////////////////////////////////
FACTORY_EXPORT_FILE(PdbParserInterpreter<ucs>, Pdb_interpreter)
FACTORY_EXPORT_FILE(IDiaDataSourcePtrInterpreter<ucs>, Pdb_interpreter)
FACTORY_EXPORT_FILE(IDiaSessionPtrInterpreter<ucs>, Pdb_interpreter)
FACTORY_EXPORT_FILE(IDiaEnumTablesPtrInterpreter<ucs>, Pdb_interpreter)
FACTORY_EXPORT_FILE(IDiaEnumSymbolsByAddrPtrInterpreter<ucs>, Pdb_interpreter)
FACTORY_EXPORT_FILE(IDiaSymbolPtrInterpreter<ucs>, Pdb_interpreter)
FACTORY_EXPORT_FILE(IDiaEnumSymbolsPtrInterpreter<ucs>, Pdb_interpreter)
FACTORY_EXPORT_FILE(IDiaLineNumberPtrInterpreter<ucs>, Pdb_interpreter)
FACTORY_EXPORT_FILE(IDiaEnumLineNumbersPtrInterpreter<ucs>, Pdb_interpreter)
FACTORY_EXPORT_FILE(IDiaSourceFilePtrInterpreter<ucs>, Pdb_interpreter)
FACTORY_EXPORT_FILE(IDiaEnumSourceFilesPtrInterpreter<ucs>, Pdb_interpreter)
FACTORY_EXPORT_FILE(IDiaTablePtrInterpreter<ucs>, Pdb_interpreter)