/**
 * @class set
 * @date 03/11/2012
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_SET_HPP
#define GEN_SET_HPP

#include "generator.hpp"

namespace gen {

    template <class CollectionT1, class ConditionT2>
    class set_expr
    : public collection_expr < set_expr<CollectionT1, ConditionT2> >
    {
    public:
        typedef set_expr<CollectionT1,ConditionT2>  self_t;
        typedef collection_expr<self_t>             base_t;
        typedef typename base_t::enumerated_t       enumerated_t;
        typedef typename CollectionT1::context_t    context_t;
        typedef typename context_t::container_t     container_t;
        typedef typename context_t::iterator_t      iterator_t;
        typedef typename context_t::value_t         value_t;

        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(CollectionT1))

        set_expr(collection_expr<CollectionT1> const& c1, cond_expr<ConditionT2> const& c2)
        :collection(c1.derived()), condition(c2.derived())
        {}

        template <typename DataT>
        enumerated_t
        enumerate(TYPE_CONTEXT(DataT) & c) const;

        iterator_t
        begin() const;

        iterator_t
        end() const;

    private:
        typename CollectionT1::embed_t collection;
        typename ConditionT2::embed_t  condition;

        container_t m_container;
    };

    template <class DerivedT1, class DerivedT2>
    inline set_expr< DerivedT1,DerivedT2 >
    set_g( collection_expr<DerivedT1> const& c1,
           cond_expr<DerivedT2> const& c2);

}

#include "impl/set_impl.hpp"

#endif
