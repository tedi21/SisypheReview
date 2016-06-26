#include "SimpleHPPConnectionGenerator.hpp"
#include "FileGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleHPPConnectionConv
    : FileGenerator<SimpleHPPConnectionConv>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleHPPConnectionGenerator    generator_t;
    };

    const char * SimpleHPPConnectionConv::Format_Name = "DataConnection.hpp";
    const char * SimpleHPPConnectionConv::Family_Name = "db";

    FACTORY_EXPORT(SimpleHPPConnectionConv)

}