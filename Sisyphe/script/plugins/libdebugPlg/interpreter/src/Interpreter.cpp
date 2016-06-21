#include <windows.h>
#include "ProgramInterpreter.hpp"
#include "DebugEngineInterpreter.hpp"
#include "IDebugClientPtrInterpreter.hpp"
#include "IDebugControlPtrInterpreter.hpp"
#include "DEBUG_VALUEInterpreter.hpp"

using namespace enc;
using namespace fctr;
using namespace interp;

//////////////////////////////////////////
// Exportation des classes
//////////////////////////////////////////
FACTORY_EXPORT_FILE(DebugEngineInterpreter<ucs>, )
FACTORY_EXPORT_FILE(IDebugClientPtrInterpreter<ucs>, )
FACTORY_EXPORT_FILE(IDebugControlPtrInterpreter<ucs>, )