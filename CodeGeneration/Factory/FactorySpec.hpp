#define n BOOST_PP_ITERATION()

namespace fctr {

#if n
    template<class RootT, class T, class PrototypeT, class KeyT = std::string, class ParameterPolicyT = IndexedParameterPolicy>
    class BOOST_PP_CAT(Factory,n)
    : public FactoryBase<RootT,KeyT>,
      public ParameterPolicyT
#else
    template<class RootT, class T, class KeyT = std::string>
    class BOOST_PP_CAT(Factory,n)
    : public FactoryBase<RootT,KeyT>
#endif
    {
    public:
        /** Constructeur
         @param key le nom de la classe à créer
        */
        BOOST_PP_CAT(Factory,n)(typename boost::call_traits<KeyT>::param_type key)
        :FactoryBase<RootT,KeyT>(key)
        {}
        /** Instancie un nouvel objet de la classe indiquée
        @param parameters les paramètres du constructeur
        @return l'objet créé
        */
        RootT * create(const ParameterArray& parameters) const;
        /** supprime l'objet créé
        @param l'objet créé
        */
        void release(RootT * obj) const;
        /** clone la factory
        */
        FactoryBase<RootT,KeyT>* clone() const;
    };

#define FACTORY_PARAMETER(z, n, data)                                       \
        PARAMETER_VALUE(PrototypeT,BOOST_PP_ADD(n,1)) BOOST_PP_CAT(data,n); \
        success = success &&                                                \
        ReadParameter<PARAMETER_TYPE(PrototypeT,BOOST_PP_ADD(n,1))>::Apply(*this,parameters,n,BOOST_PP_CAT(data,n));

    // instancie des nouveaux objets de la classe indiquée
#if n 
    template<class RootT, class T, class PrototypeT, class KeyT, class ParameterPolicyT>
    RootT * BOOST_PP_CAT(Factory,n)<RootT,T,PrototypeT,KeyT,ParameterPolicyT>::create(const ParameterArray& parameters) const {
        bool success = true;
        BOOST_PP_REPEAT(n, FACTORY_PARAMETER, param)
        if (success) return new T(BOOST_PP_ENUM_PARAMS(n, param));
        else return NULL;
    }
#else
    template<class RootT, class T, class KeyT>
    RootT * BOOST_PP_CAT(Factory,n)<RootT,T,KeyT>::create(const ParameterArray& parameters) const {
        return new T();
    }
#endif

#undef FACTORY_PARAMETER

#if n 
    template<class RootT, class T, class PrototypeT, class KeyT, class ParameterPolicyT>
    void BOOST_PP_CAT(Factory,n)<RootT,T,PrototypeT,KeyT,ParameterPolicyT>::release(RootT * obj) const
#else
    template<class RootT, class T, class KeyT>
    void BOOST_PP_CAT(Factory,n)<RootT,T,KeyT>::release(RootT * obj) const
#endif
    {
        if (obj) {
            delete ((T*) obj);
            obj = NULL;
        }
    }

#if n 
    template<class RootT, class T, class PrototypeT, class KeyT, class ParameterPolicyT>
    FactoryBase<RootT,KeyT>* BOOST_PP_CAT(Factory,n)<RootT,T,PrototypeT,KeyT,ParameterPolicyT>::clone() const
    {
        return new BOOST_PP_CAT(Factory,n)<RootT,T,PrototypeT,KeyT,ParameterPolicyT>(*this);
    }
#else
    template<class RootT, class T, class KeyT>
    FactoryBase<RootT,KeyT>* BOOST_PP_CAT(Factory,n)<RootT,T,KeyT>::clone() const
    {
        return new BOOST_PP_CAT(Factory,n)<RootT,T,KeyT>(*this);
    }
#endif

// namespace fctr
}

#undef n
