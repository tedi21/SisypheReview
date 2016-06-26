
namespace gen {

    template <typename FunctorT, typename ContextT>
    template <typename DataT>
    void
    marker<FunctorT,ContextT>::enumerate(TYPE_CONTEXT(DataT) & c) const
    {
        if (m_container)
        {
            range_t r = actor_base_policy<FunctorT,DataT,ContextT>::apply(m_container->functor,c);
            m_container->range = r;
        }
    }

    template <typename FunctorT, typename ContextT>
    typename marker<FunctorT,ContextT>::iterator_t
    marker<FunctorT,ContextT>::reach() const
    {
        iterator_t i = m_container->range.end();
        if (m_container && 
            m_container->range.end() != m_container->range.begin())
        {
            if (m_base_cur == beg)
            {
                i = m_container->range.begin();
            }
            i += get_offset();
        }
        return i;
    }

    template <typename FunctorT, typename ContextT>
    marker<FunctorT,ContextT>
    marker<FunctorT,ContextT>::operator+(typename marker<FunctorT,ContextT>::diff_t offset) const
    {
        marker<FunctorT,ContextT> copy(*this);
        copy.m_offset += offset;
        return copy;
    }

    template <typename FunctorT, typename ContextT>
    marker<FunctorT,ContextT>
    marker<FunctorT,ContextT>::operator-(typename marker<FunctorT,ContextT>::diff_t offset) const
    {
        return operator+(-offset);
    }

    template <typename FunctorT, typename ContextT>
    typename marker<FunctorT,ContextT>::diff_t 
    marker<FunctorT,ContextT>::get_offset() const
    {
        return m_offset;
    }

    template <typename FunctorT, typename ContextT>
    marker_cur_t 
    marker<FunctorT,ContextT>::get_cursor() const
    {
        return m_base_cur;
    }

    template<class MarkerT>
    inline MarkerT
    operator+(typename MarkerT::diff_t offset, const MarkerT& m)
    {
        return m+offset;
    }

    template <class T>
    inline marker<T>
    beg_g(const T & f)
    {
        return marker<T>(f,beg);
    }

    template <class T>
    inline marker<T>
    end_g(const T & f)
    {
        return marker<T>(f,end);
    }

    template <class ContextT, class FunctorT>
    inline marker<FunctorT,ContextT>
    begT_g(const FunctorT & f)
    {
        return marker<FunctorT,ContextT>(f,beg);
    }

    template <class ContextT, class FunctorT>
    inline marker<FunctorT,ContextT>
    endT_g(const FunctorT & f)
    {
        return marker<FunctorT,ContextT>(f,end);
    }

    template <typename FunctorT, typename ContextT>
    marker<FunctorT,ContextT>
    marker_factory<FunctorT,ContextT>::make(marker_cur_t base_cur, typename marker_factory<FunctorT,ContextT>::diff_t offset) const
    {
        return marker<FunctorT,ContextT>(m_container, base_cur, offset);
    }

    template <typename FunctorT, typename ContextT>
    marker<FunctorT,ContextT>
    marker_factory<FunctorT,ContextT>::make(typename marker_factory<FunctorT,ContextT>::diff_t offset) const
    {
        return marker<FunctorT,ContextT>(m_container, m_base_cur, m_offset + offset);
    }
}
