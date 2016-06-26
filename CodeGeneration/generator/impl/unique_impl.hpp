
#include <algorithm>

namespace gen {

    template <class CompositorT1>
    template <class DataT>
    typename unique<CompositorT1>::enumerated_t
    unique<CompositorT1>::enumerate(TYPE_CONTEXT(DataT) & context) const
    {
        typename CompositorT1::enumerated_t copy1 = expr.template enumerate<DataT>(context);

        unique<CompositorT1> copy(expr);

        container_t sorted_copy1;
        sorted_copy1.assign(copy1.begin(), copy1.end());
        std::sort(sorted_copy1.begin(), sorted_copy1.end());

        typename container_t::iterator last = std::unique(sorted_copy1.begin(), sorted_copy1.end());
        sorted_copy1.erase(last, sorted_copy1.end());
        copy.m_container = sorted_copy1;
        return copy;
    }

    template <class CompositorT1>
    typename unique<CompositorT1>::iterator_t
    unique<CompositorT1>::begin() const
    {
        return m_container.begin();
    }

    template <class CompositorT1>
    typename unique<CompositorT1>::iterator_t
    unique<CompositorT1>::end() const
    {
        return m_container.end();
    }

    template <class DerivedT1>
    inline unique< DerivedT1 >
    unique_g(collection_expr<DerivedT1> const& b)
    {
        return unique< DerivedT1 >(b);
    }

}
