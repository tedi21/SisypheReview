/**
 * @class callback_trait
 * @date 05/06/2010
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_CALLBACK_TRAIT_HPP
#define GEN_CALLBACK_TRAIT_HPP

#include <boost/type_traits.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#ifndef GEN_MAX_SIZE
#  define GEN_MAX_SIZE 5
#endif

namespace gen {
    ///////////////////////////////////////////////////////////////////////////
    //
    //  callback trait
    //
    ///////////////////////////////////////////////////////////////////////////

    template<typename Function> struct callback_function_trait;
    template<typename Class> struct callback_method_trait;

    #define CALLBACK_TRAIT(z, n, unused)                                    \
        template<    typename R                                             \
                    BOOST_PP_COMMA_IF(n)                                    \
                    BOOST_PP_ENUM_PARAMS(n, typename T)>                    \
        struct callback_function_trait<R (*)(BOOST_PP_ENUM_PARAMS(n,T))>    \
        {                                                                   \
          typedef R result_t;                                               \
          typedef BOOST_PP_CAT(T,BOOST_PP_SUB(n,1)) arg_t;                  \
          enum { arity = n };                                               \
        };                                                                  \
                                                                            \
        template<    typename Class, typename R                             \
                    BOOST_PP_COMMA_IF(n)                                    \
                    BOOST_PP_ENUM_PARAMS(n, typename T)>                    \
        struct callback_method_trait<R (Class::*)(BOOST_PP_ENUM_PARAMS(n,T)) const>\
        {                                                                   \
          typedef R result_t;                                               \
          typedef BOOST_PP_CAT(T,BOOST_PP_SUB(n,1)) arg_t;                  \
          enum { arity = n };                                               \
        };                                                                  \
        template<    typename Class, typename R                             \
                    BOOST_PP_COMMA_IF(n)                                    \
                    BOOST_PP_ENUM_PARAMS(n, typename T)>                    \
        struct callback_method_trait<R (Class::*)(BOOST_PP_ENUM_PARAMS(n,T))>\
        {                                                                   \
          typedef R result_t;                                               \
          typedef BOOST_PP_CAT(T,BOOST_PP_SUB(n,1)) arg_t;                  \
          enum { arity = n };                                               \
        };                                                                  \

    #define BOOST_PP_LOCAL_MACRO(n)   CALLBACK_TRAIT(~, n, ~)
    #define BOOST_PP_LOCAL_LIMITS     (1, GEN_MAX_SIZE)
    #include BOOST_PP_LOCAL_ITERATE()
    #undef CALLBACK_TRAIT

    template< typename R >
    struct callback_function_trait<R (*)()>
    {
      typedef R result_t;
      typedef void arg_t;
      enum { arity = 0 };
    };

    template< typename Class, typename R >
    struct callback_method_trait<R (Class::*)() const>
    {
      typedef R result_t;
      typedef void arg_t;
      enum { arity = 0 };
    };

    template< typename Class, typename R >
    struct callback_method_trait<R (Class::*)()>
    {
      typedef R result_t;
      typedef void arg_t;
      enum { arity = 0 };
    };

    template<typename T>
    struct callback_functor_trait
    {
		BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,&T::operator())
		typedef typename nested::type method_pointer_t;

        typedef typename callback_method_trait<method_pointer_t>::result_t result_t;
        typedef typename callback_method_trait<method_pointer_t>::arg_t arg_t;
        enum { arity = callback_method_trait<method_pointer_t>::arity };
    };

    template<typename Function> 
    struct is_pointer_function
    {
        enum {value = false};
    };

    #define IS_POINTER_FUNCTION_TRAIT(z, n, unused)                         \
        template<    typename R                                             \
                    BOOST_PP_COMMA_IF(n)                                    \
                    BOOST_PP_ENUM_PARAMS(n, typename T)>                    \
        struct is_pointer_function<R (*)(BOOST_PP_ENUM_PARAMS(n,T))>        \
        {                                                                   \
          enum {value = true};                                              \
        };                                                                  \

    #define BOOST_PP_LOCAL_MACRO(n)   IS_POINTER_FUNCTION_TRAIT(~, n, ~)
    #define BOOST_PP_LOCAL_LIMITS     (1, GEN_MAX_SIZE)
    #include BOOST_PP_LOCAL_ITERATE()
    #undef IS_POINTER_FUNCTION_TRAIT

    template<typename R>
    struct is_pointer_function<R (*)()>
    {
        enum {value = true};
    };

    template <bool false_, class F>
    struct get_argument {
        typedef typename callback_functor_trait<F>::arg_t arg_t;
        typedef typename callback_functor_trait<F>::result_t result_t;
        enum { arity = callback_functor_trait<F>::arity };
    };
    template <class F>
    struct get_argument<true, F> {
        typedef typename callback_function_trait<F>::arg_t arg_t;
        typedef typename callback_function_trait<F>::result_t result_t;
        enum { arity = callback_function_trait<F>::arity };
    };

    template<class T1>
    struct callback_trait
    {
        typedef T1 functor_t;
        typedef typename get_argument<is_pointer_function<T1>::value,T1>::arg_t arg_t;
        typedef typename get_argument<is_pointer_function<T1>::value,T1>::result_t result_t;
        enum { arity = get_argument<is_pointer_function<T1>::value,T1>::arity };
    };
}

#endif