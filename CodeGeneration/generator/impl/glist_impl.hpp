namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  glist class implementation
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename FunctorT, typename ContextT>
    template <class DataT>
    typename glist<FunctorT,ContextT>::enumerated_t
    glist<FunctorT,ContextT>::enumerate(TYPE_CONTEXT(DataT) & context) const
    {
        glist<FunctorT,ContextT> copy(m_container.functor);
        copy.m_container.range = 
            actor_base_policy<FunctorT,DataT,ContextT>::apply(copy.m_container.functor,context);
        return copy;
    }

    template <typename FunctorT, typename ContextT>
    typename glist<FunctorT,ContextT>::iterator_t
    glist<FunctorT,ContextT>::begin() const
    {
        return m_container.range.begin();
    }

    template <typename FunctorT, typename ContextT>
    typename glist<FunctorT,ContextT>::iterator_t
    glist<FunctorT,ContextT>::end() const
    {
        return m_container.range.end();
    }

    template <class T>
    inline glist<T>
    list_g(const T & f)
    {
        return glist<T>(f);
    }

    template <class ContextT, class FunctorT>
    inline glist<FunctorT,ContextT>
    listT_g(const FunctorT & f)
    {
        return glist<FunctorT,ContextT>(f);
    }
}