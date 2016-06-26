/**
 * @class cartesian_product
 * @date 10/01/2013
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef CARTESIAN_PRODUCT_HPP
#define CARTESIAN_PRODUCT_HPP

#include "loop.hpp"

namespace gen {

    #define CONTEXT_PRODUCT(a,b)\
        context<b::container_t,a::parent_t>

    template <class CompositorT1, class CompositorT2>
    class cartesian_product
    : public collection_expr < cartesian_product<CompositorT1, CompositorT2> >
    {
    public:
        typedef cartesian_product<CompositorT1,CompositorT2> self_t;
        typedef collection_expr<self_t>             base_t;
        typedef typename base_t::enumerated_t       enumerated_t;
        typedef typename CompositorT2::context_t    context_t2;
        typedef typename context_t2::container_t    container_t;
        typedef typename context_t2::iterator_t     iterator_t;
        typedef typename context_t2::value_t        value_t;
        typedef typename CompositorT1::context_t    context_t1;
        typedef typename context_t1::parent_t       parent_t;
        DEFINE_CONTEXT_RANGE(parent_t, container_t, context_t)

        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(CompositorT1))

        cartesian_product(collection_expr<CompositorT1> const& e1, collection_expr<CompositorT2> const& e2)
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

    template <class DerivedT1, class DerivedT2>
    inline cartesian_product< DerivedT1,DerivedT2 >
    operator*( collection_expr<DerivedT1> const& b1,
               collection_expr<DerivedT2> const& b2);
}

#include "impl/cartesian_product_impl.hpp"

#endif
