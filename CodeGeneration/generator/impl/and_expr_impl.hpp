
namespace gen {

    template <class CompositorT1, class CompositorT2>
    template <typename DataT>
    bool
    and_expr<CompositorT1,CompositorT2>::evaluate(TYPE_CONTEXT(DataT) & c) const
    {
        return expr1.template evaluate<DataT>(c) &&
               expr2.template evaluate<DataT>(c);
    }

    template <class DerivedT>
    inline and_expr<cst_expr, DerivedT>
    operator&&(bool value, const cond_expr<DerivedT> & other)
    {
        return and_expr<cst_expr, DerivedT>(cst_expr(value), other);
    }

}
