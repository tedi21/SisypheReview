#include "SimpleHPPLogGenerator.hpp"
#include "FileGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleHPPLogConv
    : FileGenerator<SimpleHPPLogConv>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleHPPLogGenerator    generator_t;
    };

    const char * SimpleHPPLogConv::Format_Name = "config.hpp";
    const char * SimpleHPPLogConv::Family_Name = "cpp";

    FACTORY_EXPORT(SimpleHPPLogConv)

}