#ifndef _PARSER_TYPES_HPP_
#define _PARSER_TYPES_HPP_

#include "CoreTypes.hpp"
#include "encoding.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>

using namespace enc;
using namespace boost;

namespace dsg {

    namespace parser {
    //////////////////////////////////////////////////////
    // Type declaration
    //////////////////////////////////////////////////////
        typedef std::vector<short>   key_t;
        typedef map<key_t,UniString> dictionnary_t;
        typedef shared_ptr< map<key_t,UniString> > dictionnary_ptr_t;
    }
}

#endif