/**
 * @class last
 * @date 20/07/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_LAST_HPP
#define GEN_LAST_HPP

#include "generator.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  last class
    //
    //      Handles expressions of the form:
    //
    //          -a
    //
    //      where a is a generator. The expression returns a composite
    //      generator that generate its subject 1 time.
    //
    ///////////////////////////////////////////////////////////////////////////
    
    template <typename S>
    struct last
    :   public unary<S, generator<last<S> > >
    {
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(S))

        typedef last<S>                     self_t;
        typedef unary_generator_category    generator_category_t;
        typedef unary<S, generator<self_t> > base_t;

        last(S const& a)
        : base_t(a) {}
    
        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };
    
    //////////////////////////////////
    template <typename S>
    last<S>
    operator-(generator<S> const& a);

}

#include "impl/last_impl.hpp"

#endif
