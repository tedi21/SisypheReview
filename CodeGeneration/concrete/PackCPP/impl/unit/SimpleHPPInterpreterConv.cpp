#include "SimpleHPPInterpreterGenerator.hpp"
#include "ProjectGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleHPPInterpreterConv
    : ProjectGenerator<SimpleHPPInterpreterConv>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleHPPInterpreterGenerator    generator_t;
    };

    const char * SimpleHPPInterpreterConv::Format_Name = "Interpreter.hpp";
    const char * SimpleHPPInterpreterConv::Family_Name = "cpp";

    FACTORY_EXPORT(SimpleHPPInterpreterConv)

}
