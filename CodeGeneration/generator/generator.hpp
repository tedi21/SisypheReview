/**
 * @class generator
 * @date 20/01/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief
 */

#ifndef GEN_GENERATOR_HPP
#define GEN_GENERATOR_HPP

#include "generator_info.hpp"
#include "generator_exception.hpp"

#include <boost/functional/hash.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#ifndef GEN_VA_ARG_SIZE
#  define GEN_VA_ARG_SIZE 10
#endif

namespace gen {

    // forward declaration
    template <typename IteratorT>
    class range;

    template <typename S, typename LimitsT>
    class loop;

    template<typename DerivedT>
    struct collection_expr;

    template<typename DerivedT>
    struct marker_expr;

    template <class LimitT>
    class limits;

    template <typename S, typename CondT>
    struct if_generator;

    template<typename DerivedT>
    struct cond_expr;

    class cst_expr;

    #define BOOST_PP_LOCAL_MACRO(n)                      \
        template < BOOST_PP_ENUM_PARAMS(n, class T) >    \
        class BOOST_PP_CAT(va_arg,n);
    #define BOOST_PP_LOCAL_LIMITS     (2, GEN_VA_ARG_SIZE)
    #include BOOST_PP_LOCAL_ITERATE()

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Generator categories
    //
    //      Helper template classes to distinguish different types of
    //      generators. The following categories are the most generic. More
    //      specific types may inherit from these. Each generator has a typedef
    //      generator_category_t that defines its category. By default, if one
    //      is not specified, it will inherit from the base generator class
    //      which typedefs its generator_category_t as generator_parser_category.
    //
    //          - plain generator has nothing special
    //          - binary generator has subject a and b (e.g. sequence)
    //          - unary generator has single subject  (e.g. kleene star)
    //          - actor generator has an attached action generator
    //
    ///////////////////////////////////////////////////////////////////////////

    struct plain_generator_category {};
    struct binary_generator_category : plain_generator_category {};
    struct unary_generator_category  : plain_generator_category {};
    struct actor_generator_category  : unary_generator_category {};

    template <typename DerivedT>
    struct generator
    {
        typedef DerivedT                    embed_t;
        typedef DerivedT                    derived_t;
        typedef plain_generator_category    generator_category_t;

        generator()
        {}

        DerivedT& derived()
        {
            return *static_cast<DerivedT*>(this);
        }

        DerivedT const& derived() const
        {
            return *static_cast<DerivedT const*>(this);
        }

        template <class T>
        loop< DerivedT, T >
        operator[](collection_expr<T> const& l) const;

        template <class T>
        loop< DerivedT, limits<T> >
        operator[](marker_expr<T> const& l) const;

        template <class T>
        if_generator< DerivedT, T >
        operator[](cond_expr<T> const& c) const;

        if_generator< DerivedT, cst_expr >
        operator[](bool b) const;

    #define GEN_VA_ARG_PARAM(z, n, data)                            \
        BOOST_PP_COMMA_IF(n)                                        \
        generator<BOOST_PP_CAT(T,n)> const& BOOST_PP_CAT(g,n)

    #define BOOST_PP_LOCAL_MACRO(n)                                                     \
        template <BOOST_PP_ENUM_PARAMS( BOOST_PP_SUB(n,1), class T)>                    \
        BOOST_PP_CAT(va_arg,n)< DerivedT, BOOST_PP_ENUM_PARAMS( BOOST_PP_SUB(n,1), T) > \
        operator()( BOOST_PP_REPEAT(BOOST_PP_SUB(n,1), GEN_VA_ARG_PARAM, ~) ) const;
    #define BOOST_PP_LOCAL_LIMITS     (2, GEN_VA_ARG_SIZE)
    #include BOOST_PP_LOCAL_ITERATE()
    #undef GEN_VA_ARG_PARAM

    };

    ///////////////////////////////////////////////////////////////////////
    //
    //  abstract_generator class
    //
    ///////////////////////////////////////////////////////////////////////
    template <typename DataT>
    struct abstract_generator
    {
        DECLARE_EMPTY_CONTEXT()

        abstract_generator() {}
        virtual ~abstract_generator() {}

        virtual void
        do_generate_virtual(TYPE_CONTEXT(DataT) & context) const /*throw(std::bad_cast)*/ = 0;

        virtual abstract_generator*
        clone() const = 0;
    };

    template <typename DataT>
    inline abstract_generator<DataT>*
    new_clone( const abstract_generator<DataT>& a )
    {
        return a.clone();
    }

    ///////////////////////////////////////////////////////////////////////
    //
    //  concrete_generator class
    //
    ///////////////////////////////////////////////////////////////////////
    template <typename GeneratorT, typename DataT>
    struct concrete_generator : abstract_generator<DataT>
    {
        DECLARE_EMPTY_CONTEXT()
        typedef typename GeneratorT::template declare_context<DataT>::context_t    required_context_t;

        concrete_generator(GeneratorT const& g) : g(g) {}
        virtual ~concrete_generator() {}

        virtual void
        do_generate_virtual(TYPE_CONTEXT(DataT) & context) const /*throw(std::bad_cast)*/
        {
            try 
            {
                required_context_t& required_context = dynamic_cast<required_context_t&>(context);
                g.generate<DataT>(required_context);
            }
            catch (std::bad_cast &)
            {
                throw generator_exception<typename DataT::char_t>(context.str());
            }
        }

        virtual abstract_generator<DataT>*
        clone() const
        {
            return new concrete_generator(g);
        }

        typename GeneratorT::embed_t g;
    };

}

#include "impl/generator_impl.hpp"

#endif
