#include <algorithm>

namespace gen {

    template <class CompositorT1, class CompositorT2>
    template <class DataT>
    typename intersect_expr<CompositorT1,CompositorT2>::enumerated_t
    intersect_expr<CompositorT1,CompositorT2>::enumerate(TYPE_CONTEXT(DataT) & context) const
    {
        typename CompositorT1::enumerated_t copy1 = expr1.template enumerate<DataT>(context);
        typename CompositorT2::enumerated_t copy2 = expr2.template enumerate<DataT>(context);

        intersect_expr<CompositorT1,CompositorT2> copy(expr1, expr2);

        container_t sorted_copy1;
        sorted_copy1.assign(copy1.begin(), copy1.end());
        std::sort(sorted_copy1.begin(), sorted_copy1.end());

        container_t sorted_copy2;
        sorted_copy2.assign(copy2.begin(), copy2.end());
        std::sort(sorted_copy2.begin(), sorted_copy2.end());

        std::set_intersection(sorted_copy1.begin(), sorted_copy1.end(), sorted_copy2.begin(), sorted_copy2.end(), std::back_inserter(copy.m_container));
        return copy;
    }

    template <class CompositorT1, class CompositorT2>
    typename intersect_expr<CompositorT1,CompositorT2>::iterator_t
    intersect_expr<CompositorT1,CompositorT2>::begin() const
    {
        return m_container.begin();
    }

    template <class CompositorT1, class CompositorT2>
    typename intersect_expr<CompositorT1,CompositorT2>::iterator_t
    intersect_expr<CompositorT1,CompositorT2>::end() const
    {
        return m_container.end();
    }

    template <class DerivedT1, class DerivedT2>
    inline intersect_expr< DerivedT1,DerivedT2 >
    operator&( collection_expr<DerivedT1> const& b1,
               collection_expr<DerivedT2> const& b2)
    {
        return intersect_expr< DerivedT1,DerivedT2 >(b1, b2);
    }

}