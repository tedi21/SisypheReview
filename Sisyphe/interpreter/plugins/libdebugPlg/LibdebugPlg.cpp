#define INITGUID
#include <windows.h>
#include <dbgeng.h>
#include "LibdebugPlg.h"
#include "ProgramInterpreter.hpp"
#include "DebugEngineInterpreter.hpp"
#include "IDebugClientPtrInterpreter.hpp"
#include "IDebugControlPtrInterpreter.hpp"
#include "CreateFlagsInterpreter.hpp"
#include "DEBUG_VALUEInterpreter.hpp"
#include "DebugStatusInterpreter.hpp"
#include "TimeOutInterpreter.hpp"
#include "WaitFlagsInterpreter.hpp"
#include "DebugExecuteInterpreter.hpp"
#include "DebugOutCTLInterpreter.hpp"
#include "ImageFileMachineInterpreter.hpp"
#include "IDebugSystemObjectsPtrInterpreter.hpp"
#include "IDebugSymbolsPtrInterpreter.hpp"
#include "DebugValueInterpreter.hpp"
#include "DebugBreakpointInterpreter.hpp"
#include "DebugBreakpointFlagInterpreter.hpp"
#include "IDebugBreakpointPtrInterpreter.hpp"

DEFINE_GUID(IID_IUnknown, 0x00000000, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

using namespace enc;
using namespace fctr;
using namespace interp;

extern "C" LIBDEBUGPLG_API void PlugInit(va_list vl, void** res)
{
    DebugEngineInterpreter<ucs>::register_class();
    IDebugClientPtrInterpreter<ucs>::register_class();
    IDebugControlPtrInterpreter<ucs>::register_class();
    CreateFlagsInterpreter<ucs>::register_class();
    DEBUG_VALUEInterpreter<ucs>::register_class();
    DebugStatusInterpreter<ucs>::register_class();
    TimeOutInterpreter<ucs>::register_class();
    WaitFlagsInterpreter<ucs>::register_class();
    DebugExecuteInterpreter<ucs>::register_class();
    DebugOutCTLInterpreter<ucs>::register_class();
    ImageFileMachineInterpreter<ucs>::register_class();
    IDebugSystemObjectsPtrInterpreter<ucs>::register_class();
    IDebugSymbolsPtrInterpreter<ucs>::register_class();
    DebugValueInterpreter<ucs>::register_class();
    DebugBreakpointInterpreter<ucs>::register_class();
    DebugBreakpointFlagInterpreter<ucs>::register_class();
    IDebugBreakpointPtrInterpreter<ucs>::register_class();
    *res = (void*) LOGNAME;
}

extern "C" LIBDEBUGPLG_API void PlugTerm(void** res)
{
    DebugEngineInterpreter<ucs>::unregister_class();
    IDebugClientPtrInterpreter<ucs>::unregister_class();
    IDebugControlPtrInterpreter<ucs>::unregister_class();
    CreateFlagsInterpreter<ucs>::unregister_class();
    DEBUG_VALUEInterpreter<ucs>::unregister_class();
    DebugStatusInterpreter<ucs>::unregister_class();
    TimeOutInterpreter<ucs>::unregister_class();
    WaitFlagsInterpreter<ucs>::unregister_class();
    DebugExecuteInterpreter<ucs>::unregister_class();
    DebugOutCTLInterpreter<ucs>::unregister_class();
    ImageFileMachineInterpreter<ucs>::unregister_class();
    IDebugSystemObjectsPtrInterpreter<ucs>::unregister_class();
    IDebugSymbolsPtrInterpreter<ucs>::unregister_class();
    DebugValueInterpreter<ucs>::unregister_class();
    DebugBreakpointInterpreter<ucs>::unregister_class();
    DebugBreakpointFlagInterpreter<ucs>::unregister_class();
    IDebugBreakpointPtrInterpreter<ucs>::unregister_class();
}
