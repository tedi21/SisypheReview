/**
 * @class cst_expr
 * @date 10/04/2008
 * @author Teddy DIDÉ
 * @version  2.0
 * @brief 
 */

#ifndef CST_EXPR_HPP
#define CST_EXPR_HPP

#include "if_generator.hpp"

namespace gen {

    class cst_expr
    : public cond_expr < cst_expr >
    {
    private:
        bool m_value;
    public:
        DECLARE_EMPTY_CONTEXT()

        cst_expr(bool val)
        :m_value(val)
        {}

        template <typename DataT>
        bool
        evaluate(TYPE_CONTEXT(DataT) & c) const;

    };
}

#include "impl/cst_expr_impl.hpp"

#endif
