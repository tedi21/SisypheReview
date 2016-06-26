/**
 * @class difference_expr
 * @date 10/01/2013
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef DIFFERENCE_EXPR_HPP
#define DIFFERENCE_EXPR_HPP

#include "loop.hpp"

namespace gen {

    template <class CompositorT1, class CompositorT2>
    class difference_expr
    : public collection_expr < difference_expr<CompositorT1, CompositorT2> >
    {
    public:
        typedef difference_expr<CompositorT1,CompositorT2> self_t;
        typedef collection_expr<self_t>             base_t;
        typedef typename base_t::enumerated_t       enumerated_t;
        typedef typename CompositorT1::context_t    context_t;
        typedef typename context_t::container_t     container_t;
        typedef typename context_t::iterator_t      iterator_t;
        typedef typename context_t::value_t         value_t;

        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT2(CompositorT1, CompositorT2))

        difference_expr(collection_expr<CompositorT1> const& e1, collection_expr<CompositorT2> const& e2)
        :expr1(e1.derived()), expr2(e2.derived())
        {}

        template <typename DataT>
        enumerated_t
        enumerate(TYPE_CONTEXT(DataT) & c) const;

        iterator_t
        begin() const;

        iterator_t
        end() const;

    private:
        typename CompositorT1::embed_t expr1;
        typename CompositorT2::embed_t expr2;

        container_t m_container;
    };

    template <class DerivedT1, class DerivedT2, class ContextT>
    inline difference_expr< DerivedT1,DerivedT2 >
    operator/( collection_expr<DerivedT1> const& b1,
               collection_expr<DerivedT2> const& b2);
}

#include "impl/difference_expr_impl.hpp"

#endif
