/**
 * @class or_expr
 * @date 10/04/2008
 * @author Teddy DIDÉ
 * @version  2.0
 * @brief 
 */

#ifndef OR_EXPR_HPP
#define OR_EXPR_HPP

#include "if_generator.hpp"

namespace gen {

    template <class CompositorT1, class CompositorT2>
    class or_expr
    : public cond_expr < or_expr<CompositorT1, CompositorT2> >
    {
    private:
        typename CompositorT1::embed_t expr1;
        typename CompositorT2::embed_t expr2;
    public:
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT2(CompositorT1, CompositorT2))

        or_expr(cond_expr<CompositorT1> const& e1, cond_expr<CompositorT2> const& e2)
        :expr1(e1.derived()), expr2(e2.derived())
        {}

        template <typename DataT>
        bool
        evaluate(TYPE_CONTEXT(DataT) & c) const;

    };

    template <class DerivedT>
    inline or_expr<cst_expr, DerivedT>
    operator||(bool value, const cond_expr<DerivedT> & other);

}

#include "impl/or_expr_impl.hpp"

#endif
