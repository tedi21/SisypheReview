/**
 * @class notlast
 * @date 20/07/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_NOT_LAST_HPP
#define GEN_NOT_LAST_HPP

#include "last.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  not_last class
    //
    //      Handles expressions of the form:
    //
    //          ~(+a)
    //
    //      where a is a generator. The expression returns a composite
    //      generator that generate its subject n times (except last).
    //
    ///////////////////////////////////////////////////////////////////////////
    
    template <typename S>
    struct not_last
    :   public unary<S, generator<not_last<S> > >
    {
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(S))

        typedef not_last<S>                    self_t;
        typedef unary_generator_category    generator_category_t;
        typedef unary<S, generator<self_t> > base_t;
    
        not_last(S const& a)
        : base_t(a) {}
  
        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };
    
    //////////////////////////////////
    template <typename S>
    not_last<S>
    operator~(last<S> const& a);

}

#include "impl/notlast_impl.hpp"

#endif
