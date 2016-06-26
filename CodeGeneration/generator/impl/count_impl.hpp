namespace gen {

    template <class CollectionT, class OperatorT>
    template <typename DataT>
    bool
    count<CollectionT,OperatorT>::evaluate(TYPE_CONTEXT(DataT) & c) const
    {
        int nb_value = (int) m_value;
        int nb_valid = 0;

        // Enumerates 
        typename CollectionT::enumerated_t copy = 
            m_collection.template enumerate<DataT>(c);
        // Check number of items
        nb_valid = (int) (copy.end() - copy.begin());
        return m_op(nb_valid, nb_value);
    }

    template <typename CollectionT, typename OperatorT>
    inline count<CollectionT, OperatorT>
    has_g(size_t value, 
          collection_expr<CollectionT> const& collection, 
          OperatorT const& op)
    {
        return count<CollectionT, OperatorT>(value, collection, op);
    }
}
