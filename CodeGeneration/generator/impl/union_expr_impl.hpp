
#include <algorithm>

namespace gen {

    template <class CompositorT1, class CompositorT2>
    template <class DataT>
    typename union_expr<CompositorT1,CompositorT2>::enumerated_t
    union_expr<CompositorT1,CompositorT2>::enumerate(TYPE_CONTEXT(DataT) & context) const
    {
        typename CompositorT1::enumerated_t copy1 = expr1.template enumerate<DataT>(context);
        typename CompositorT2::enumerated_t copy2 = expr2.template enumerate<DataT>(context);

        union_expr<CompositorT1,CompositorT2> copy(expr1, expr2);

        container_t sorted_copy1;
        sorted_copy1.assign(copy1.begin(), copy1.end());
        std::sort(sorted_copy1.begin(), sorted_copy1.end());

        container_t sorted_copy2;
        sorted_copy2.assign(copy2.begin(), copy2.end());
        std::sort(sorted_copy2.begin(), sorted_copy2.end());

        std::set_union(sorted_copy1.begin(), sorted_copy1.end(), sorted_copy2.begin(), sorted_copy2.end(), std::back_inserter(copy.m_container));
        return copy;
    }

    template <class CompositorT1, class CompositorT2>
    typename union_expr<CompositorT1,CompositorT2>::iterator_t
    union_expr<CompositorT1,CompositorT2>::begin() const
    {
        return m_container.begin();
    }

    template <class CompositorT1, class CompositorT2>
    typename union_expr<CompositorT1,CompositorT2>::iterator_t
    union_expr<CompositorT1,CompositorT2>::end() const
    {
        return m_container.end();
    }

    template <class DerivedT1, class DerivedT2>
    inline union_expr< limits<DerivedT1>,limits<DerivedT2> >
    operator|( marker_expr<DerivedT1> const& b1,
               marker_expr<DerivedT2> const& b2)
    {
        return union_expr< limits<DerivedT1>,limits<DerivedT2> >((b1,1), (b2,1));
    }

    template <class DerivedT1, class DerivedT2>
    inline union_expr< DerivedT1,limits<DerivedT2> >
    operator|( collection_expr<DerivedT1> const& b1,
               marker_expr<DerivedT2> const& b2)
    {
        return union_expr< DerivedT1,limits<DerivedT2> >(b1, (b2,1));
    }

    template <class DerivedT1, class DerivedT2>
    inline union_expr< limits<DerivedT1>,DerivedT2 >
    operator|( marker_expr<DerivedT1> const& b1,
               collection_expr<DerivedT2> const& b2)
    {
        return union_expr< limits<DerivedT1>,DerivedT2 >((b1,1), b2);
    }

    template <class DerivedT1, class DerivedT2>
    inline union_expr< DerivedT1,DerivedT2 >
    operator|( collection_expr<DerivedT1> const& b1,
               collection_expr<DerivedT2> const& b2)
    {
        return union_expr< DerivedT1,DerivedT2 >(b1, b2);
    }

}