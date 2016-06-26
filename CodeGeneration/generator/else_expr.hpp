/**
 * @class else_expr
 * @date 15/10/2012
 * @author Teddy DIDÉ
 * @version  2.0
 * @brief 
 */

#ifndef ELSE_EXPR_HPP
#define ELSE_EXPR_HPP

#include "if_generator.hpp"
#include "condition.hpp"

namespace gen {

    class else_expr 
    : public cond_expr < else_expr >
    {
    public:
        template <class T__>
        struct declare_context
        {
            typedef typename T__::context_t context_t;
            static condition<T__>& else_condition()
            {
                static condition<T__> instance;
                return instance;
            }
        };

        else_expr()
        {}
    
        template <typename DataT>
        bool
        evaluate(TYPE_CONTEXT(DataT) & c) const;

    };

    inline else_expr
    else_g();

}

#include "impl/else_expr_impl.hpp"

#endif
