
namespace gen {

    template <typename FunctorT, typename ContextT>
    template <typename DataT>
    inline void
    actor<FunctorT,ContextT>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        FunctorT funct = m_funct;
        str_g(actor_base_policy<FunctorT,DataT,ContextT>::apply(funct, context))    
            .generate<DataT>(context);
    }

    template <typename FunctorT>
    inline actor<FunctorT>
    act_g(FunctorT const& f)
    { 
        return actor<FunctorT>(f); 
    }

    template <typename ContextT, typename FunctorT>
    inline actor<FunctorT,ContextT>
    actT_g(FunctorT const& f)
    {
        return actor<FunctorT,ContextT>(f); 
    }

}
