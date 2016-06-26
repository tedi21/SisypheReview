/**
 * @class var
 * @date 20/07/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_VAR_HPP
#define GEN_VAR_HPP

#include "va_arg.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  var class
    //
    //      Handles expressions of the form:
    //
    //          $(0)
    //
    //
    ///////////////////////////////////////////////////////////////////////////
    
    struct var
    : public generator<var>
    {
        typedef var            self_t;
        DECLARE_EMPTY_CONTEXT()

        var(size_t n)
        : pos(n) {}
    
        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    
        size_t pos;
    };
   
    //////////////////////////////////
    inline var
    $(size_t n);

}

#include "impl/var_impl.hpp"

#endif
