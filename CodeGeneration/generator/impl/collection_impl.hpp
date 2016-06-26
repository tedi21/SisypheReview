

namespace gen {

    template <typename ContextT>
    template <typename CollectionT>
    inline collection<ContextT> &
    collection<ContextT>::operator=(CollectionT const& l)
    {
        ptr.reset(new concrete_collection<CollectionT,range_t,data_t>(l));
        return *this;
    }

    template <typename ContextT>
    inline collection<ContextT>&
    collection<ContextT>::operator=(collection const& l)
    {
        ptr.reset(new concrete_collection<collection,range_t,data_t>(l));
        return *this;
    }

    template <typename ContextT>
    inline collection<ContextT>
    collection<ContextT>::copy() const
    {
        return collection<ContextT>(ptr.get() ? ptr->clone() : 0);
    }

    template <typename ContextT>
    inline collection<ContextT>::operator enumerated_collection<ContextT>() const
    {
        return enumerated_collection<ContextT>(ptr, base_t::name);
    }

    template <typename ContextT>
    inline enumerated_collection<ContextT>&
    enumerated_collection<ContextT>::operator=(enumerated_collection const& l)
    {
        base_t::name = l.getName();
        ptr = l.ptr;
        return *this;
    }
	
    template <
        typename DerivedT,       // derived class
        typename EmbedT,         // how derived class is embedded
        typename ContextT
    >
    template <class DataT>
    typename collection_base<DerivedT,EmbedT,ContextT>::enumerated_t
    collection_base<DerivedT,EmbedT,ContextT>::enumerate(TYPE_CONTEXT(DataT) & c) const
    {
        abstract_collection_t* p = NULL;
        DerivedT const* derived_this = static_cast<DerivedT const*>(this);
        if (collection_access::get(*derived_this))
        {   
            p = collection_access::get(*derived_this)
                    ->do_enumerate_virtual(c);
        }
        return collection_base<DerivedT,EmbedT,ContextT>::enumerated_t(
            boost::shared_ptr<abstract_collection_t>(p), getName());
    }

    template <
        typename DerivedT,       // derived class
        typename EmbedT,         // how derived class is embedded
        typename ContextT
    >
    typename collection_base<DerivedT,EmbedT,ContextT>::iterator_t
    collection_base<DerivedT,EmbedT,ContextT>::begin() const
    {
        iterator_t i;
        DerivedT const* derived_this = static_cast<DerivedT const*>(this);
        if (collection_access::get(*derived_this))
        {
            i = collection_access::get(*derived_this)
                    ->do_begin_virtual();
        }
        return i;
    }

    template <
        typename DerivedT,       // derived class
        typename EmbedT,         // how derived class is embedded
        typename ContextT
    >
    typename collection_base<DerivedT,EmbedT,ContextT>::iterator_t
    collection_base<DerivedT,EmbedT,ContextT>::end() const
    {
        iterator_t i;
        DerivedT const* derived_this = static_cast<DerivedT const*>(this);
        if (collection_access::get(*derived_this))
        {
            i = collection_access::get(*derived_this)
                    ->do_end_virtual();
        }
        return i;
    }
}

