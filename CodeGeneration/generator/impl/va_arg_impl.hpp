

#define CREATE(z, n, data) \
    BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(data,n).derived()

#define PUSH(z, n, data) \
    generator_args<DataT>::args[generator_args<DataT>::level].push_back(\
        this->BOOST_PP_CAT(subj,BOOST_PP_SUB(data,n)));

namespace gen {

    #define GEN_VA_ARG_IMPL(z, n, unused)                                            \
        template < BOOST_PP_ENUM_PARAMS(n, class T) >                                \
        template <typename DataT>                                                    \
        void                                                                         \
        BOOST_PP_CAT(va_arg,n)<BOOST_PP_ENUM_PARAMS(n,T)>::generate(TYPE_CONTEXT(DataT) & context) const\
        {                                                                            \
            int save_level = generator_args<DataT>::level;                           \
            generator_args<DataT>::args.push_back(std::vector< stored_format<DataT,true> >());\
            generator_args<DataT>::level = (int)generator_args<DataT>::args.size()-1;\
            BOOST_PP_REPEAT(BOOST_PP_SUB(n,1), PUSH, BOOST_PP_SUB(n,1))              \
            subj0.generate<DataT>(context);                                          \
            generator_args<DataT>::args.pop_back();                                  \
            generator_args<DataT>::level = save_level;                               \
        }                                                                            \
                                                                                     \
        template <typename DerivedT>                                                 \
        template <BOOST_PP_ENUM_PARAMS( BOOST_PP_SUB(n,1), class T)>                 \
        BOOST_PP_CAT(va_arg,n)< DerivedT, BOOST_PP_ENUM_PARAMS( BOOST_PP_SUB(n,1), T) > \
        generator<DerivedT>::operator()( BOOST_PP_REPEAT(BOOST_PP_SUB(n,1), GENERATOR, g) ) const\
        {                                                                            \
            return BOOST_PP_CAT(va_arg,n)<DerivedT, BOOST_PP_ENUM_PARAMS(BOOST_PP_SUB(n,1),T)>\
                                    (derived(),BOOST_PP_REPEAT(BOOST_PP_SUB(n,1), CREATE, g));\
        }    

    #include <boost/preprocessor/iteration/local.hpp>

    #define BOOST_PP_LOCAL_MACRO(n)   GEN_VA_ARG_IMPL(~, n, ~)
    #define BOOST_PP_LOCAL_LIMITS     (2, GEN_VA_ARG_SIZE)
    #include BOOST_PP_LOCAL_ITERATE()

}


#undef CREATE
#undef PUSH
