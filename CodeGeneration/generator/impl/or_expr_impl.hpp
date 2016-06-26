
namespace gen {

    template <class CompositorT1, class CompositorT2>
    template <typename DataT>
    bool
    or_expr<CompositorT1,CompositorT2>::evaluate(TYPE_CONTEXT(DataT) & c) const
    {
        return    expr1.evaluate<DataT>(c) ||
                expr2.evaluate<DataT>(c);
    }

    template <class DerivedT>
    inline or_expr<cst_expr, DerivedT>
    operator||(bool value, const cond_expr<DerivedT> & other)
    {
        return or_expr<cst_expr, DerivedT>(cst_expr(value), other);
    }

}
