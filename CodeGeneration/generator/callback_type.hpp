/**
 * @class callback_trait
 * @date 29/06/2010
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_CALLBACK_TYPE_HPP
#define GEN_CALLBACK_TYPE_HPP

#include "if_expr.hpp"
#include "actor.hpp"
#include "marker.hpp"
#include "callback_trait.hpp"

namespace gen {

    template <class R, class T>
    struct get_type_generator
    {
        typedef actor<T> type_t;
    };

    template <class T>
    struct get_type_generator<bool,T> 
    {
        typedef if_expr<T> type_t;
    };

    template <class T, class C>
    struct get_type_generator<range<C>,T> 
    {
        typedef marker<T> type_t;
    };

    template <class T>
    inline typename get_type_generator<typename callback_trait<T>::result_t,T>::type_t
    call_g(const T & f);

    template <class R, class T, class C>
    struct get_type_generator_tpl
    {
        typedef actor<T,C> type_t;
    };

    template <class T, class C>
    struct get_type_generator_tpl<bool,T,C> 
    {
        typedef if_expr<T,C> type_t;
    };

    template <class T, class C1, class C2>
    struct get_type_generator_tpl<range<C1>,T,C2> 
    {
        typedef marker<T,C2> type_t;
    };

    template <class C, class T>
    inline typename get_type_generator_tpl<typename callback_trait<T>::result_t,T,C>::type_t
    callT_g(const T & f);

}

#include "impl/callback_type_impl.hpp"

#endif
