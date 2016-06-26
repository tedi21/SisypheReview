#include "SimpleHPPPredicateGenerator.hpp"
#include "ProjectGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleHPPPredicateConv
    : ProjectGenerator<SimpleHPPPredicateConv>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleHPPPredicateGenerator    generator_t;
    };

    const char * SimpleHPPPredicateConv::Format_Name = "Predicate.hpp";
    const char * SimpleHPPPredicateConv::Family_Name = "cpp";

    FACTORY_EXPORT(SimpleHPPPredicateConv)

}
