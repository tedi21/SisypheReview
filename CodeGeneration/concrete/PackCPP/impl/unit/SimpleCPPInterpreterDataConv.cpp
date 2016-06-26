#include "SimpleCPPInterpreterDataGenerator.hpp"
#include "FileGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleCPPInterpreterDataConv
    : FileGenerator<SimpleCPPInterpreterDataConv>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleCPPInterpreterDataGenerator    generator_t;
    };

    const char * SimpleCPPInterpreterDataConv::Format_Name = "InterpreterData.cpp";
    const char * SimpleCPPInterpreterDataConv::Family_Name = "cpp";

    FACTORY_EXPORT(SimpleCPPInterpreterDataConv)

}
