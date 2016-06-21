#include "connectionInterpreter.hpp"
#include "statementInterpreter.hpp"
#include "dataParametersInterpreter.hpp"

using namespace interp;

//////////////////////////////////////////
// Exportation des classes
//////////////////////////////////////////

FACTORY_EXPORT_FILE(ConnectionInterpreter<ucs>, SqlInterpreter)
FACTORY_EXPORT_FILE(StatementInterpreter<ucs>, SqlInterpreter)
FACTORY_EXPORT_FILE(DataParametersInterpreter<ucs>, SqlInterpreter)

