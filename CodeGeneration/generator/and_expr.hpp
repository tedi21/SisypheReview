/**
 * @class and_expr
 * @date 10/04/2008
 * @author Teddy DIDÉ
 * @version  2.0
 * @brief 
 */

#ifndef AND_EXPR_HPP
#define AND_EXPR_HPP

#include "if_generator.hpp"

namespace gen {

    template <class CompositionT1, class CompositionT2>
    class and_expr
    : public cond_expr < and_expr<CompositionT1, CompositionT2> >
    {
    private:
        typename CompositionT1::embed_t expr1;
        typename CompositionT2::embed_t expr2;
    public:
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT2(CompositionT1, CompositionT2))

        and_expr(cond_expr<CompositionT1> const& e1, cond_expr<CompositionT2> const& e2)
        :expr1(e1.derived()), expr2(e2.derived())
        {}

        template <typename DataT>
        bool
        evaluate(TYPE_CONTEXT(DataT) & c) const;

    };

    template <class DerivedT>
    inline and_expr<cst_expr, DerivedT>
    operator&&(bool value, const cond_expr<DerivedT> & other);
    
}

#include "impl/and_expr_impl.hpp"

#endif
