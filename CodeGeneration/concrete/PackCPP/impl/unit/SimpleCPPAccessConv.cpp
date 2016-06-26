#include "SimpleCPPAccessGenerator.hpp"
#include "ProjectGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleCPPAccessConv
    : ProjectGenerator<SimpleCPPAccessConv>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleCPPAccessGenerator    generator_t;
    };

    const char * SimpleCPPAccessConv::Format_Name = "Access_impl.hpp";
    const char * SimpleCPPAccessConv::Family_Name = "cpp";

    FACTORY_EXPORT(SimpleCPPAccessConv)

}