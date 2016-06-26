
namespace gen {

    template <typename FunctorT, typename ContextT>
    template <typename DataT>
    inline bool
    if_expr<FunctorT,ContextT>::evaluate(TYPE_CONTEXT(DataT) & c) const
    {
        FunctorT expr = m_expr;
        return actor_base_policy<FunctorT,DataT,ContextT>::apply(expr,c);
    }

    template <class T>
    inline if_expr<T>
    if_g(const T & f)
    {
        return if_expr<T>(f);
    }

    template <class ContextT, class FunctorT>
    inline if_expr<FunctorT,ContextT>
    ifT_g(const FunctorT & f)
    {
        return if_expr<FunctorT,ContextT>(f);
    }

}
