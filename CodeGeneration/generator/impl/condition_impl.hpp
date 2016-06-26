

namespace gen {

    template <typename DataT>
    template <typename CondT>
    inline condition<DataT> &
    condition<DataT>::operator=(CondT const& c)
    {
        ptr.reset(new concrete_condition<CondT, DataT>(c));
        return *this;
    }

    template <typename DataT>
    inline condition<DataT>&
    condition<DataT>::operator=(condition const& f)
    {
        ptr.reset(new concrete_condition<condition, DataT>(f));
        return *this;
    }

    template <typename DataT>
    inline condition<DataT>
    condition<DataT>::copy() const
    {
        return condition<DataT>(ptr.get() ? ptr->clone() : 0);
    }


    template <
        typename DerivedT,       // derived class
        typename EmbedT,         // how derived class is embedded
        typename DataT
    >
    template <class>
    bool
    condition_base<DerivedT,EmbedT,DataT>::evaluate(TYPE_CONTEXT(DataT) & c) const
    {
        bool r = true;
        DerivedT const* derived_this = static_cast<DerivedT const*>(this);
        if (condition_base_access::get(*derived_this))                
        {                                                            
            r = condition_base_access::get(*derived_this)                
                    ->do_evaluate_virtual(c);                        
        }
        return r;
    }

}

