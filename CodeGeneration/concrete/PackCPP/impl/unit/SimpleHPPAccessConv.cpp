#include "SimpleHPPAccessGenerator.hpp"
#include "ProjectGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleHPPAccessConv
    : ProjectGenerator<SimpleHPPAccessConv>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleHPPAccessGenerator    generator_t;
    };

    const char * SimpleHPPAccessConv::Format_Name = "Access.hpp";
    const char * SimpleHPPAccessConv::Family_Name = "cpp";

    FACTORY_EXPORT(SimpleHPPAccessConv)

}