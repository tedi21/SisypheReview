/**
 * @class unique
 * @date 10/06/2015
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef UNIQUE_HPP
#define UNIQUE_HPP

#include "loop.hpp"

namespace gen {

    template <class CompositorT1>
    class unique
    : public collection_expr < unique<CompositorT1> >
    {
    public:
        typedef unique<CompositorT1>                self_t;
        typedef collection_expr<self_t>             base_t;
        typedef typename base_t::enumerated_t       enumerated_t;
        typedef typename CompositorT1::context_t    context_t;
        typedef typename context_t::container_t     container_t;
        typedef typename context_t::iterator_t      iterator_t;
        typedef typename context_t::value_t         value_t;

        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(CompositorT1))

        unique(collection_expr<CompositorT1> const& e)
        :expr(e.derived())
        {}

        template <typename DataT>
        enumerated_t
        enumerate(TYPE_CONTEXT(DataT) & c) const;

        iterator_t
        begin() const;

        iterator_t
        end() const;

    private:
        typename CompositorT1::embed_t expr;

        container_t m_container;
    };

    template <class DerivedT1>
    inline unique< DerivedT1 >
    unique_g( collection_expr<DerivedT1> const& b );
}

#include "impl/unique_impl.hpp"

#endif
