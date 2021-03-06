/**
 * @class first
 * @date 20/07/2008
 * @author Teddy DID�
 * @version  1.0
 * @brief 
 */

#ifndef GEN_FIRST_HPP
#define GEN_FIRST_HPP

#include "generator.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  first class
    //
    //      Handles expressions of the form:
    //
    //          +a
    //
    //      where a is a generator. The expression returns a composite
    //      generator that generate its subject 1 time.
    //
    ///////////////////////////////////////////////////////////////////////////
    
    template <typename S>
    struct first
    : public unary<S, generator<first<S> > >
    {
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(S))

        typedef first<S>                     self_t;
        typedef unary_generator_category     generator_category_t;
        typedef unary<S, generator<self_t> > base_t;

        first(S const& a)
        : base_t(a) {}
    
        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };
    
    //////////////////////////////////
    template <typename S>
    first<S>
    operator+(generator<S> const& a);

}

#include "impl/first_impl.hpp"

#endif
