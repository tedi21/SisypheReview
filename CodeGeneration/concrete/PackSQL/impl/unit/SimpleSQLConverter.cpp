#include "SimpleSQLGenerator.hpp"
#include "SimpleSQLParser.hpp"
#include "ProjectConverter.hpp"

using namespace fctr;
using namespace dsg::generator;
using namespace dsg::parser;

namespace dsg {

    struct SimpleSQLConverter
    : ProjectConverter<SimpleSQLConverter>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleSQLGenerator generator_t;
        typedef SimpleSQLParser    parser_t; 
    };

    const char * SimpleSQLConverter::Format_Name = ".sql";
    const char * SimpleSQLConverter::Family_Name = "sql";

    FACTORY_EXPORT(SimpleSQLConverter)

}
