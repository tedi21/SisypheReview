namespace gen {

    template <class CollectionT1, class ConditionT2>
    template <class DataT>
    typename set_expr<CollectionT1,ConditionT2>::enumerated_t
    set_expr<CollectionT1,ConditionT2>::enumerate(TYPE_CONTEXT(DataT) & context) const
    {
        set_expr<CollectionT1,ConditionT2> copy(collection, condition);
        container_t& container = copy.m_container;

        typename CollectionT1::enumerated_t copy1 = collection.template enumerate<DataT>(context);
        typename CollectionT1::context_t c(copy1.begin(), copy1.end(), context);
        for (; c.current() != copy1.end(); c.increment())
        {
            if (copy.condition.template evaluate<DataT>(c))
            {
                container.push_back(*(c.current()));
            }
        }
        return copy;
    }

    template <class CollectionT1, class ConditionT2>
    typename set_expr<CollectionT1,ConditionT2>::iterator_t
    set_expr<CollectionT1,ConditionT2>::begin() const
    {
        return m_container.begin();
    }

    template <class CollectionT1, class ConditionT2>
    typename set_expr<CollectionT1,ConditionT2>::iterator_t
    set_expr<CollectionT1,ConditionT2>::end() const
    {
        return m_container.end();
    }

    template <class DerivedT1, class DerivedT2>
    inline set_expr< DerivedT1,DerivedT2 >
    set_g( collection_expr<DerivedT1> const& c1,
           cond_expr<DerivedT2> const& c2)
    {
        return set_expr< DerivedT1,DerivedT2 >(c1, c2);
    }

}