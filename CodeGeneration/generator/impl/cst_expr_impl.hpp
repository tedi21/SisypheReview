
namespace gen {

    template <typename DataT>
    bool
    cst_expr::evaluate(TYPE_CONTEXT(DataT) & c) const
    {
        return m_value;
    }

}
