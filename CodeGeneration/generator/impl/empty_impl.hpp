namespace gen {

    template <class CollectionT>
    template <typename DataT>
    bool
    empty<CollectionT>::evaluate(TYPE_CONTEXT(DataT) & c) const
    {
        // Enumerates 
        typename CollectionT::enumerated_t copy = 
            m_collection.template enumerate<DataT>(c);
        // Check iterators
        return copy.begin() == copy.end();
    }

    template <typename CollectionT>
    inline empty<CollectionT>
    empty_g(collection_expr<CollectionT> const& collection)
    {
        return empty<CollectionT>(collection);
    }
}
