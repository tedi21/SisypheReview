#ifndef _FACTORY_TYPES_HPP_
#define _FACTORY_TYPES_HPP_

#include "CoreExport.hpp"
#include "Parser.hpp"
#include "Generator.hpp"
// factory
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "bebop.hpp"

namespace dsg {

    typedef fctr::ObjectManager< vector<string> >       FamilyManager;
    typedef fctr::ClassManager<Generator>               GeneratorManager;
    typedef fctr::ClassManager<Parser>                  ParserManager;

}

#endif // _FACTORY_TYPES_HPP_

