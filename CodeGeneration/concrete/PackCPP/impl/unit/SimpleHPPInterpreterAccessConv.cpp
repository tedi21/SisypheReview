#include "SimpleHPPInterpreterAccessGenerator.hpp"
#include "ProjectGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleHPPInterpreterAccessConv
    : ProjectGenerator<SimpleHPPInterpreterAccessConv>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleHPPInterpreterAccessGenerator    generator_t;
    };

    const char * SimpleHPPInterpreterAccessConv::Format_Name = "InterpreterAccess.hpp";
    const char * SimpleHPPInterpreterAccessConv::Family_Name = "cpp";

    FACTORY_EXPORT(SimpleHPPInterpreterAccessConv)

}
