/**
 * @class notfirst
 * @date 20/07/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_NOT_FIRST_HPP
#define GEN_NOT_FIRST_HPP

#include "first.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  not_first class
    //
    //      Handles expressions of the form:
    //
    //          ~(+a)
    //
    //      where a is a generator. The expression returns a composite
    //      generator that generate its subject n times (except first).
    //
    ///////////////////////////////////////////////////////////////////////////
    
    template <typename S>
    struct not_first
    :   public unary<S, generator<not_first<S> > >
    {
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(S))

        typedef not_first<S>                    self_t;
        typedef unary_generator_category        generator_category_t;
        typedef unary<S, generator<self_t> >    base_t;
    
        not_first(S const& a)
        : base_t(a) {}
  
        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };
    
    //////////////////////////////////
    template <typename S>
    not_first<S>
    operator~(first<S> const& a);

}

#include "impl/notfirst_impl.hpp"

#endif
