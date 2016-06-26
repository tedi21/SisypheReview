#include "SimpleHPPEntityGenerator.hpp"
#include "ProjectGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleHPPEntityConv
    : ProjectGenerator<SimpleHPPEntityConv>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleHPPEntityGenerator    generator_t;
    };

    const char * SimpleHPPEntityConv::Format_Name = ".hpp";
    const char * SimpleHPPEntityConv::Family_Name = "cpp";

    FACTORY_EXPORT(SimpleHPPEntityConv)

}