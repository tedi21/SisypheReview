#include "SimpleHDataGenerator.hpp"
#include "FileGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleHDataConv
    : FileGenerator<SimpleHDataConv>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleHDataGenerator    generator_t;
    };

    const char * SimpleHDataConv::Format_Name = "DataAccess.h";
    const char * SimpleHDataConv::Family_Name = "cpp";

    FACTORY_EXPORT(SimpleHDataConv)

}