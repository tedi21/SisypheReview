/**
 * @class if_expr
 * @date 10/04/2008
 * @author Teddy DIDÉ
 * @version  2.0
 * @brief 
 */

#ifndef IF_EXPR_HPP
#define IF_EXPR_HPP

#include "if_generator.hpp"
#include "actor.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  if_expr class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename FunctorT, typename ContextT = no_context>
    class if_expr 
    : public actor_base<FunctorT,ContextT, cond_expr < if_expr<FunctorT,ContextT> > >
    {
    private:
        typedef actor_base<FunctorT,ContextT, cond_expr < if_expr<FunctorT,ContextT> > > actor_base_t;

        FunctorT m_expr;

    public:
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(actor_base_t))

        if_expr(FunctorT const& e)
        :m_expr(e)
        {}
    
        template <typename DataT>
        bool
        evaluate(TYPE_CONTEXT(DataT) & c) const;
    };

    template <class T>
    inline if_expr<T>
    if_g(const T & f);

    template <class ContextT, class FunctorT>
    inline if_expr<FunctorT,ContextT>
    ifT_g(const FunctorT & f);

}

#include "impl/if_expr_impl.hpp"

#endif
