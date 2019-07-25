
namespace gen {

    template <class CompositorT>
    template <typename DataT>
    bool
    neg_expr<CompositorT>::evaluate(TYPE_CONTEXT(DataT) & c) const
    {
        return !expr.template evaluate<DataT>(c);
    }

}
