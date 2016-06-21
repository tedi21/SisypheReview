#include <windows.h>
#include "ProgramInterpreter.hpp"
#include "WordXMLDocumentInterpreter.hpp"
#include "WordXMLNodeInterpreter.hpp"
#include "WordXMLNodeListInterpreter.hpp"
#include "WordMacroInterpreter.hpp"

using namespace enc;
using namespace fctr;
using namespace interp;

//////////////////////////////////////////
// Exportation des classes
//////////////////////////////////////////
FACTORY_EXPORT_FILE(WordXMLDocumentInterpreter<ucs>, word_interpreter)
FACTORY_EXPORT_FILE(WordXMLNodeInterpreter<ucs>, word_interpreter)
FACTORY_EXPORT_FILE(WordXMLNodeListInterpreter<ucs>, word_interpreter)
FACTORY_EXPORT_FILE(WordMacroInterpreter<ucs>, word_interpreter)