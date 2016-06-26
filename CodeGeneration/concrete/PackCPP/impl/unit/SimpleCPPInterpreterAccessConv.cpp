#include "SimpleCPPInterpreterAccessGenerator.hpp"
#include "ProjectGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleCPPInterpreterAccessConv
    : ProjectGenerator<SimpleCPPInterpreterAccessConv>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleCPPInterpreterAccessGenerator    generator_t;
    };

    const char * SimpleCPPInterpreterAccessConv::Format_Name = "InterpreterAccess_impl.hpp";
    const char * SimpleCPPInterpreterAccessConv::Family_Name = "cpp";

    FACTORY_EXPORT(SimpleCPPInterpreterAccessConv)

}
