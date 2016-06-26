#include "SimpleCPPConnectionGenerator.hpp"
#include "FileGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleCPPConnectionConv
    : FileGenerator<SimpleCPPConnectionConv>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleCPPConnectionGenerator    generator_t;
    };

    const char * SimpleCPPConnectionConv::Format_Name = "DataConnection_impl.hpp";
    const char * SimpleCPPConnectionConv::Family_Name = "db";

    FACTORY_EXPORT(SimpleCPPConnectionConv)

}