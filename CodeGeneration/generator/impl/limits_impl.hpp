namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  limits class implementation
    //
    ///////////////////////////////////////////////////////////////////////////

    template <class MarkerT>
    limits<MarkerT>& 
    limits<MarkerT>::operator=(limits<MarkerT> const& l)
    {
        m_first = l.m_first;
        m_end   = l.m_end;
        return *this;
    }

    template <class MarkerT>
    template <class DataT>
    typename limits<MarkerT>::enumerated_t
    limits<MarkerT>::enumerate(TYPE_CONTEXT(DataT) & context) const
    {
        // Creates deep copy
        typename MarkerT::factory_t factory(m_first);
        MarkerT copy = factory.make();

        // Enumerates 
        copy.enumerate<DataT>(context);

        return limits<MarkerT>(copy, factory.make(m_end.get_cursor(), m_end.get_offset()));
    }

    template <class MarkerT>
    typename limits<MarkerT>::iterator_t
    limits<MarkerT>::begin() const
    {
        return m_first.reach();
    }

    template <class MarkerT>
    typename limits<MarkerT>::iterator_t
    limits<MarkerT>::end() const
    {
        return m_end.reach();
    }

    template <class MarkerT>
    inline limits<MarkerT> 
    operator,( marker_expr<MarkerT> const& b1,
               marker_expr<MarkerT> const& b2)
    {
        return limits<MarkerT>(b1, b2);
    }


    template <class MarkerT>
    inline limits<MarkerT>            
    operator,( marker_expr<MarkerT> const& b1, 
               typename MarkerT::diff_t offset)
    {
        MarkerT b2 = b1.derived() + offset;
        return limits<MarkerT>(b1, b2);
    }

    template <class MarkerT>
    inline limits<MarkerT>            
    operator,( typename MarkerT::diff_t offset,
               marker_expr<MarkerT> const& b2)
    {
        MarkerT b1 = offset + b2.derived();
        return limits<MarkerT>(b1, b2);
    }
}