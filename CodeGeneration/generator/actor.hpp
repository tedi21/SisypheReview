/**
 * @class actor
 * @date 20/01/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_ACTOR_HPP
#define GEN_ACTOR_HPP

#include "generator.hpp"
#include "callback_trait.hpp"
#include <boost/mpl/int.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector.hpp>
namespace mpl = boost::mpl; // namespace alias

namespace gen {
    ///////////////////////////////////////////////////////////////////////////////////////
    //  traits allowing to retrieve context argument
    ///////////////////////////////////////////////////////////////////////////////////////

    template<typename C> 
    struct is_context
    {
        enum {value = false};
    };

    template<typename R, typename P>
    struct is_context<context<R,P> >
    {
        enum {value = true};
    };

    template<typename C>
    struct is_context<empty_context<C> >
    {
        enum {value = true};
    };

    template <bool false_, class A, class R>
    struct get_context
    {
        BOOST_MPL_ASSERT_MSG( false, TYPE_NOT_FOUND, (A));
    };

    template <bool false_, class R>
    struct get_context<false_, void, R>
    {
        typedef typename R::context_t context_t;
    };

    template <class C, class R>
    struct get_context<true, C, R> 
    {
        typedef C context_t;
    };

    ///////////////////////////////////////////////////////////////////////////////////////
    //  policies allowing to apply context argument
    ///////////////////////////////////////////////////////////////////////////////////////
    template <bool _false, class A, int arity>
    struct actor_context_policy;

    #define CAST(z, n, data) \
        typedef typename BOOST_PP_CAT(parent_t,BOOST_PP_ADD(BOOST_PP_SUB(data,n),1))::parent_t    \
                BOOST_PP_CAT(parent_t,BOOST_PP_SUB(data,n));                      \
        BOOST_PP_CAT(parent_t,BOOST_PP_SUB(data,n)) &                             \
        BOOST_PP_CAT(p,BOOST_PP_SUB(data,n)) = c;                                

    #define VALUE(z, n, data) \
        BOOST_PP_CAT(p,BOOST_PP_ADD(n,1)).current(),

    #define ACTOR_POLICY(z, n, unused)                                             \
        template <bool _false, class A>                                            \
        struct actor_context_policy<_false, A, n>                                  \
        {                                                                          \
            static typename A::result_t apply(typename A::functor_t & f, typename A::context_t & c)\
            {                                                                      \
                typedef typename A::context_t    BOOST_PP_CAT(parent_t,n);         \
                BOOST_PP_REPEAT(BOOST_PP_SUB(n,1), CAST, BOOST_PP_SUB(n,1))        \
                return f(BOOST_PP_REPEAT(BOOST_PP_SUB(n,1), VALUE, ~) c.current());\
            }                                                                      \
        };

    #define BOOST_PP_LOCAL_MACRO(n)   ACTOR_POLICY(~, n, ~)
    #define BOOST_PP_LOCAL_LIMITS     (1, GEN_MAX_SIZE)
    #include BOOST_PP_LOCAL_ITERATE()
    #undef ACTOR_POLICY
    #undef VALUE
    #undef CAST

    template <bool _false, class A>
    struct actor_context_policy<_false, A, 0>
    {
        static typename A::result_t apply(typename A::functor_t & f, typename A::context_t &)
        {
            return f();
        }
    };

    template <class A>
    struct actor_context_policy<true, A, 1>
    {
           static typename A::result_t apply(typename A::functor_t & f, typename A::context_t & c)
           {
                return f(c);
           }
    };

    ///////////////////////////////////////////////////////////////////////////////////////
    //  traits for Functor and Data types
    ///////////////////////////////////////////////////////////////////////////////////////
    template<class T1, class T2>
    struct actor_trait
    : callback_trait<T1>
    {
        typedef typename boost::remove_reference<typename callback_trait<T1>::arg_t>::type    const_value_t;
        typedef typename boost::remove_const<const_value_t>::type    value_t;
        typedef typename get_context<is_context<value_t>::value,value_t,T2>::context_t context_t;
    };

    template <class T1, class T2>
    struct actor_policy
    {
        static typename actor_trait<T1,T2>::result_t apply(T1 & f, typename actor_trait<T1,T2>::context_t & c)
        {
             return actor_context_policy<
                 is_context<typename actor_trait<T1,T2>::value_t>::value,
                 actor_trait<T1,T2>,
                 actor_trait<T1,T2>::arity
             >::apply(f,c);
        }     
    };

    ///////////////////////////////////////////////////////////////////////////////////////
    //  traits for Functor and Context types
    ///////////////////////////////////////////////////////////////////////////////////////
    template <class T1, class T2>
    struct actor_tpl_trait
    : callback_trait<T1>
    {
        typedef typename boost::remove_reference<typename callback_trait<T1>::arg_t>::type    const_value_t;
        typedef typename boost::remove_const<const_value_t>::type    value_t;
        typedef T2 context_t;
    };

    template <class T1, class T2>
    struct actor_tpl_policy
    {
        static typename actor_tpl_trait<T1,T2>::result_t apply(T1 & f, typename actor_tpl_trait<T1,T2>::context_t & c)
        {
             return actor_context_policy<
                 is_context<typename actor_tpl_trait<T1,T2>::value_t>::value,
                 actor_tpl_trait<T1,T2>,
                 actor_tpl_trait<T1,T2>::arity
             >::apply(f,c);
        }     
    };

    ///////////////////////////////////////////////////////////////////////////////////////
    //  macros
    ///////////////////////////////////////////////////////////////////////////////////////   
     #define ACTOR_TYPE(Functor, Context)         \
        namespace gen {                           \
        template <class DataT>                    \
        struct actor_trait<Functor, DataT>        \
        : callback_trait<Functor>                 \
        {                                         \
            typedef typename boost::remove_reference<typename callback_trait<Functor>::arg_t>::type    const_value_t;\
            typedef typename boost::remove_const<const_value_t>::type    value_t;\
            typedef Context         context_t;    \
        };                                        \
        }

    #define DECLARE_FUNCTOR_CONTEXT(Functor)\
        template <class DataT>           \
        struct declare_context           \
        {                                \
            typedef typename actor_trait<Functor,DataT>::context_t context_t;\
        };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  actor_base class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct no_context;

    template <class FunctorT, class DataT, class ContextT>
    struct actor_base_policy
    {
        static typename actor_tpl_trait<FunctorT,ContextT>::result_t apply(FunctorT & f, typename actor_tpl_trait<FunctorT,ContextT>::context_t & c)
        {
             return actor_tpl_policy<FunctorT,ContextT>::apply(f,c);
        }
    };

    template <class FunctorT, class DataT>
    struct actor_base_policy<FunctorT,DataT,no_context>
    {
        static typename actor_trait<FunctorT,DataT>::result_t apply(FunctorT & f, typename actor_trait<FunctorT,DataT>::context_t & c)
        {
             return actor_policy<FunctorT,DataT>::apply(f,c);
        }
    };


    template <typename FunctorT, typename ContextT, typename BaseT>
    struct actor_base 
    : BaseT
    {
        DECLARE_CONTEXT(ContextT)
    };

    template <typename FunctorT, typename BaseT>
    struct actor_base<FunctorT, no_context, BaseT>
    : BaseT
    {
        DECLARE_FUNCTOR_CONTEXT(FunctorT)
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  actor class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename FunctorT, typename ContextT = no_context>
    class actor 
    : public actor_base<FunctorT,ContextT, generator< actor<FunctorT,ContextT> > >
    {
    private:
        typedef actor_base<FunctorT,ContextT, generator< actor<FunctorT,ContextT> > > actor_base_t;

        FunctorT m_funct;

    public:
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(actor_base_t))

        typedef actor_generator_category        generator_category_t;
        typedef actor<FunctorT,ContextT>        self_t;

        actor(FunctorT const& f) : m_funct(f){}

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };

    template <typename FunctorT>
    inline actor<FunctorT>
    act_g(FunctorT const& f);

    template <typename ContextT, typename FunctorT>
    inline actor<FunctorT,ContextT>
    actT_g(FunctorT const& f);

    ///////////////////////////////////////////////////////////////////////////////////////
    //  preimplemented functor
    ///////////////////////////////////////////////////////////////////////////////////////  

    #define DECLARE_STR_VALUE_ACCESS(StringT, ContextT, FunctorName)    \
        struct FunctorName                                              \
        {                                                               \
            StringT operator()(const ContextT& c) const;                \
        };

    #define DECLARE_WVALUE_ACCESS(ContextT, FunctorName)                \
        DECLARE_STR_VALUE_ACCESS(std::wstring, ContextT, FunctorName)

    #define DECLARE_VALUE_ACCESS(ContextT, FunctorName)                 \
        DECLARE_STR_VALUE_ACCESS(std::string, ContextT, FunctorName)

    #define IMPLEMENT_STR_VALUE_ACCESS(StringT, ContextT, FunctorName, Getter)  \
        StringT FunctorName::operator()(const ContextT& c) const                \
        {                                                                       \
            return fctr::Convert<StringT>::parse(c.current()->Getter);          \
        }

    #define IMPLEMENT_WVALUE_ACCESS(ContextT, FunctorName, Getter)              \
        IMPLEMENT_STR_VALUE_ACCESS(std::wstring, ContextT, FunctorName, Getter)

    #define IMPLEMENT_VALUE_ACCESS(ContextT, FunctorName, Getter)               \
        IMPLEMENT_STR_VALUE_ACCESS(std::string, ContextT, FunctorName, Getter)
}

#include "impl/actor_impl.hpp"

#endif
