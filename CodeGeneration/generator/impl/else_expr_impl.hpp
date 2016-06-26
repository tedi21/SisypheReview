
namespace gen {

    template <typename DataT>
    bool
    else_expr::evaluate(TYPE_CONTEXT(DataT) & c) const
    {
        return declare_context<DataT>::else_condition().evaluate<DataT>(c);
    }

    inline else_expr
    else_g()
    {
        return else_expr();
    }

}