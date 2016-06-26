#ifndef _GENERATOR_TYPES_HPP_
#define _GENERATOR_TYPES_HPP_

#include "CoreTypes.hpp"
#include "Chance.hpp"
#include "encoding.hpp"

using namespace enc;
using namespace gen;

namespace dsg {

    namespace generator {
    //////////////////////////////////////////////////////
    // Type declaration
    //////////////////////////////////////////////////////

        // Context declaration 
        typedef generator_type<ucs::char_t> gen_info;

        DEFINE_EMPTY_CONTEXT(ucs::char_t, start_context)
        DEFINE_CONTEXT_RANGE(start_context, UniFileArray,       file_context)
        DEFINE_CONTEXT_RANGE(file_context,  UniEntityArray,     ent_context)
        DEFINE_CONTEXT_RANGE(ent_context,   UniAttributeArray,  attr_context)
        DEFINE_CONTEXT_RANGE(file_context,  UniRelationArray,   rel_context)
        DEFINE_CONTEXT_RANGE(file_context,  UniContentArray,    cnt_context)

    //////////////////////////////////////////////////////
    // Macro helper declaration
    //////////////////////////////////////////////////////
        #define file_g  callT_g<file_context>
        #define ent_g   callT_g<ent_context>
        #define attr_g  callT_g<attr_context>
        #define rel_g   callT_g<rel_context>
        #define cnt_g   callT_g<cnt_context>
    }
}

#endif
