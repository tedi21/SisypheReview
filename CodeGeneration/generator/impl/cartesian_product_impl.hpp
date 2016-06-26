
namespace gen {

    template <class CompositorT1, class CompositorT2>
    template <class DataT>
    typename cartesian_product<CompositorT1,CompositorT2>::enumerated_t
    cartesian_product<CompositorT1,CompositorT2>::enumerate(TYPE_CONTEXT(DataT) & context) const
    {
        cartesian_product<CompositorT1,CompositorT2> copy(expr1, expr2);
        container_t& container = copy.m_container;

        typename CompositorT1::enumerated_t copy1 = expr1.template enumerate<DataT>(context);
        typename CompositorT1::context_t c(copy1.begin(), copy1.end(), context);
        for (; c.current() != copy1.end(); c.increment())
        {
            typename CompositorT2::enumerated_t copy2 = expr2.template enumerate<DataT>(c);

            container.insert(container.end(), copy2.begin(), copy2.end());
        }
        return copy;
    }

    template <class CompositorT1, class CompositorT2>
    typename cartesian_product<CompositorT1,CompositorT2>::iterator_t
    cartesian_product<CompositorT1,CompositorT2>::begin() const
    {
        return m_container.begin();
    }

    template <class CompositorT1, class CompositorT2>
    typename cartesian_product<CompositorT1,CompositorT2>::iterator_t
    cartesian_product<CompositorT1,CompositorT2>::end() const
    {
        return m_container.end();
    }

    template <class DerivedT1, class DerivedT2>
    inline cartesian_product< DerivedT1,DerivedT2 >
    operator*( collection_expr<DerivedT1> const& b1,
               collection_expr<DerivedT2> const& b2)
    {
        return cartesian_product< DerivedT1,DerivedT2 >(b1, b2);
    }

}