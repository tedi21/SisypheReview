#define n BOOST_PP_ITERATION()

namespace fctr {

#if n
    template <  BOOST_PP_ENUM_PARAMS(n, class T)>
    struct BOOST_PP_CAT(Prototype,n)
#if n-1
    : BOOST_PP_CAT(Prototype,BOOST_PP_SUB(n,1))<BOOST_PP_ENUM_PARAMS(BOOST_PP_SUB(n,1),T)>
#endif
    {
#if n-1
        typedef BOOST_PP_CAT(Prototype,BOOST_PP_SUB(n,1))<BOOST_PP_ENUM_PARAMS(BOOST_PP_SUB(n,1),T)>
                parent_t;
#else
        typedef void parent_t;
#endif
        typedef BOOST_PP_CAT(T,BOOST_PP_SUB(n,1)) parameter_t;
        typedef typename parameter_t::value_t value_t;
        enum { Index = n };
};
#endif

// namespace fctr
}

#undef n
