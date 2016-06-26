/**
 * @class size
 * @date 16/12/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_SIZE_HPP
#define GEN_SIZE_HPP

#include "generator.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  size class
    //
    //      Handles expressions of the form:
    //
    //          size_g
    //
    //      where a is a generator. The expression returns a size
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CollectionT>
    class size
    : public generator< size<CollectionT> >
    {
    protected:
        typename CollectionT::embed_t m_collection;

    public:
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(CollectionT))
        typedef size<CollectionT> self_t;

        size(collection_expr<CollectionT> const& collection)
        :m_collection(collection.derived())
        {}

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };
    
    //////////////////////////////////
    template <typename T>
    size<T>
    size_g(collection_expr<T> const& collection);

}

#include "impl/size_impl.hpp"

#endif
