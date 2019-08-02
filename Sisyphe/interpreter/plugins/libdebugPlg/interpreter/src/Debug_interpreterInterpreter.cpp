#include <windows.h>
#include "ProgramInterpreter.hpp"
#include "DebugEngineInterpreter.hpp"
#include "IDebugClientPtrInterpreter.hpp"
#include "IDebugControlPtrInterpreter.hpp"
#include "DEBUG_VALUEInterpreter.hpp"
#include "IDebugSystemObjectsPtrInterpreter.hpp"
#include "IDebugSymbolsPtrInterpreter.hpp"
#include "IDebugBreakpointPtrInterpreter.hpp"
#include "DEBUG_STACK_FRAMEInterpreter.hpp"

using namespace enc;
using namespace fctr;
using namespace interp;

//////////////////////////////////////////
// Exportation des classes
//////////////////////////////////////////
FACTORY_EXPORT_FILE(DebugEngineInterpreter<ucs>, Debug_interpreter)
FACTORY_EXPORT_FILE(IDebugClientPtrInterpreter<ucs>, Debug_interpreter)
FACTORY_EXPORT_FILE(IDebugControlPtrInterpreter<ucs>, Debug_interpreter)
FACTORY_EXPORT_FILE(IDebugSystemObjectsPtrInterpreter<ucs>, Debug_interpreter)
FACTORY_EXPORT_FILE(IDebugSymbolsPtrInterpreter<ucs>, Debug_interpreter)
FACTORY_EXPORT_FILE(IDebugBreakpointPtrInterpreter<ucs>, Debug_interpreter)