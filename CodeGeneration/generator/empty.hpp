/**
 * @class empty
 * @date 20/06/2015
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief
 */

#ifndef EMPTY_HPP
#define EMPTY_HPP

#include "if_expr.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  empty class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <class CollectionT>
    class empty
    : public cond_expr< empty<CollectionT> >
    {
    public:
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(CollectionT))

        empty(collection_expr<CollectionT> const& collection)
        : m_collection(collection.derived())
        {}

        template <typename DataT>
        bool
        evaluate(TYPE_CONTEXT(DataT) & c) const;

    private:
        typename CollectionT::embed_t m_collection;
    };

    template <typename CollectionT>
    inline empty<CollectionT>
    empty_g(collection_expr<CollectionT> const& collection);

}

#include "impl/empty_impl.hpp"

#endif

