#include <windows.h>
#include "ProgramInterpreter.hpp"
#include "WordXMLInterpreter.hpp"

using namespace enc;
using namespace fctr;
using namespace interp;

//////////////////////////////////////////
// Exportation des classes
//////////////////////////////////////////
FACTORY_EXPORT_FILE(WordXMLInterpreter<ucs>, wordxml_interpreter)