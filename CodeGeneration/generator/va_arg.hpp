/**
 * @class va_arg
 * @date 16/12/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief
 */

#ifndef GEN_VA_ARG_HPP
#define GEN_VA_ARG_HPP

#include "stored_format.hpp"
#include <vector>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>

#define PARAM_TYPE(z, n, data) typedef typename boost::call_traits<BOOST_PP_CAT(T,n)>::param_type       BOOST_PP_CAT(param_t,n);
#define RETURN_TYPE(z, n, data) typedef typename boost::call_traits<BOOST_PP_CAT(T,n)>::const_reference BOOST_PP_CAT(return_t,n);
#define SUBJECT_TYPE(z, n, data) typedef BOOST_PP_CAT(T,n)                                              BOOST_PP_CAT(subject_t,n);
#define EMBED_TYPE(z, n, data) typedef typename BOOST_PP_CAT(T,n)::embed_t                              BOOST_PP_CAT(subject_embed_t,n);
#define CONSTRUCTOR(z, n, data) BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(param_t,n) BOOST_PP_CAT(data,n)
#define ATTRIBUTE(z, n, data) BOOST_PP_CAT(subject_embed_t,n) BOOST_PP_CAT(data,n);
#define INIT(z, n, data) BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(subj,n)(BOOST_PP_CAT(data,n))
#define GENERATOR(z, n, data) BOOST_PP_COMMA_IF(n) generator<BOOST_PP_CAT(T,n)> const& BOOST_PP_CAT(data,n)

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  va_arg class
    //
    //      Handles expressions of the form:
    //
    //          a(b)
    //
    //      where a and b are generators.
    //
    ///////////////////////////////////////////////////////////////////////////

    #define GEN_VA_ARG(z, n, unused)                                               \
        template < BOOST_PP_ENUM_PARAMS(n, class T) >                              \
        class BOOST_PP_CAT(va_arg,n)                                               \
        : public generator< BOOST_PP_CAT(va_arg,n)<BOOST_PP_ENUM_PARAMS(n, T) > >  \
        {                                                                          \
        public:                                                                    \
            typedef BOOST_PP_CAT(va_arg,n)<BOOST_PP_ENUM_PARAMS(n, T)>      self_t;\
            BOOST_PP_REPEAT(n, PARAM_TYPE, ~)                                      \
            BOOST_PP_REPEAT(n, RETURN_TYPE, ~)                                     \
            BOOST_PP_REPEAT(n, SUBJECT_TYPE, ~)                                    \
            BOOST_PP_REPEAT(n, EMBED_TYPE, ~)                                      \
                                                                                   \
            DECLARE_EMPTY_CONTEXT()                                                \
                                                                                   \
            BOOST_PP_CAT(va_arg,n)(BOOST_PP_REPEAT(n, CONSTRUCTOR, g))             \
            : BOOST_PP_REPEAT(n, INIT, g) {}                                       \
                                                                                   \
            template <typename DataT>                                              \
            void                                                                   \
            generate(TYPE_CONTEXT(DataT) & context) const;                         \
                                                                                   \
        public:                                                                    \
            BOOST_PP_REPEAT(n, ATTRIBUTE, subj)                                    \
        };

    #include <boost/preprocessor/iteration/local.hpp>

    #define BOOST_PP_LOCAL_MACRO(n)   GEN_VA_ARG(~, n, ~)
    #define BOOST_PP_LOCAL_LIMITS     (2, GEN_VA_ARG_SIZE)
    #include BOOST_PP_LOCAL_ITERATE()

    ///////////////////////////////////////////////////////////////////////
    //
    //  generator arguments
    //
    ///////////////////////////////////////////////////////////////////////

    template <class DataT>
    struct generator_args {
        static std::vector< std::vector< stored_format<DataT,true> > > args;
        static int level;
    };

    template <class DataT>
    std::vector< std::vector< stored_format<DataT,true> > > generator_args<DataT>::args;

    template <class DataT>
    int generator_args<DataT>::level = -1;

}

#include "impl/va_arg_impl.hpp"

#undef PARAM_TYPE
#undef RETURN_TYPE
#undef SUBJECT_TYPE
#undef EMBED_TYPE
#undef CONSTRUCTOR
#undef ATTRIBUTE
#undef INIT
#undef GENERATOR

#endif


