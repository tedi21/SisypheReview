/**
 * @class neg_expr
 * @date 10/04/2008
 * @author Teddy DIDÉ
 * @version  2.0
 * @brief 
 */

#ifndef NEG_EXPR_HPP
#define NEG_EXPR_HPP

#include "if_generator.hpp"

namespace gen {

    template <class CompositorT>
    class neg_expr
    : public cond_expr < neg_expr<CompositorT> >
    {
    private:
        typename CompositorT::embed_t expr;

    public:
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(CompositorT))

        neg_expr(cond_expr<CompositorT> const& e)
        :expr(e.derived())
        {}

        template <typename DataT>
        bool
        evaluate(TYPE_CONTEXT(DataT) & c) const;

    };
    
}

#include "impl/neg_expr_impl.hpp"

#endif
