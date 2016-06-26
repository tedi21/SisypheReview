#include "boost/lexical_cast.hpp"

namespace gen {
 
    template <typename CollectionT>
    template <typename DataT>
    void
    size<CollectionT>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        // Enumerates 
        typename CollectionT::enumerated_t copy = m_collection.template enumerate<DataT>(context);
        // Get length
        context.append(
            boost::lexical_cast<TYPE_CONTEXT(DataT)::str_t>(
                copy.end() - copy.begin() ));
    }
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  size class implementation
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    inline size<T>
    size_g(collection_expr<T> const& collection)
    {
        return size<T>(collection);
    }

}

