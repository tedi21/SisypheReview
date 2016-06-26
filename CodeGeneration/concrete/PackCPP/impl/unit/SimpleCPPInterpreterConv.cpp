#include "SimpleCPPInterpreterGenerator.hpp"
#include "ProjectGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleCPPInterpreterConv
    : ProjectGenerator<SimpleCPPInterpreterConv>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleCPPInterpreterGenerator    generator_t;
    };

    const char * SimpleCPPInterpreterConv::Format_Name = "Interpreter_impl.hpp";
    const char * SimpleCPPInterpreterConv::Family_Name = "cpp";

    FACTORY_EXPORT(SimpleCPPInterpreterConv)

}
