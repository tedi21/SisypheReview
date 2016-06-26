#define n BOOST_PP_ITERATION()

namespace fctr {

#define METHOD_PROTOTYPE(z, n, data) PARAMETER_CALL_TYPE(PrototypeT,BOOST_PP_ADD(n,1))

#if n
    template <class RootT, class ClassT, class ReturnT, class PrototypeT, class ConstT, class KeyT = std::string, class ParameterPolicyT = IndexedParameterPolicy>
    class BOOST_PP_CAT(Method,n)
    : public MethodBase<RootT,KeyT>,
      public ParameterPolicyT
#else
    template <class RootT, class ClassT, class ReturnT, class ConstT, class KeyT = std::string>
    class BOOST_PP_CAT(Method,n)
    : public MethodBase<RootT,KeyT>
#endif
    {
    private:
        template <class T>
        friend struct ReadParameter;
        template <class T>
        friend struct WriteParameter;
#if n
        // ptr method
        typedef ReturnT(ClassT::*method_t)(BOOST_PP_ENUM(n, METHOD_PROTOTYPE, ~));
        method_t ptrMethod;
#else
        // ptr method
        typedef ReturnT(ClassT::*method_t)();
        method_t ptrMethod;
#endif

    public:
        /** Constructeur
         @param key le nom de la classe à créer
        */
        BOOST_PP_CAT(Method,n)(typename call_traits<KeyT>::param_type key, method_t ptr)
        :MethodBase<RootT,KeyT>(key), ptrMethod(ptr)
        {}

        /** Invoque une methode
        @param parameters les paramètres de la méthode
        @return l'objet créé
        */
        virtual ParameterArray invoke(RootT * obj, const ParameterArray& parameters) const;
        /** Clone la method
        */
        MethodBase<RootT,KeyT>* clone() const;
    };

#undef METHOD_PROTOTYPE

#define METHOD_PARAMETER(z, n, data)                                        \
        PARAMETER_VALUE(PrototypeT,BOOST_PP_ADD(n,1)) BOOST_PP_CAT(data,n); \
        success = success &&                                                \
        ReadParameter<PARAMETER_TYPE(PrototypeT,BOOST_PP_ADD(n,1))>::Apply(*this,parameters,n,BOOST_PP_CAT(data,n));

#define METHOD_VALUE(z, n, data) BOOST_PP_CAT(data,n)

#define METHOD_RETURN(z, n, data)                                           \
        WriteParameter<PARAMETER_TYPE(PrototypeT,BOOST_PP_ADD(n,1))>::Apply(*this,out,n,BOOST_PP_CAT(data,n));

#if n
    template <class RootT, class ClassT, class ReturnT, class PrototypeT, class ConstT, class KeyT, class ParameterPolicyT>
    ParameterArray BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,PrototypeT,ConstT,KeyT,ParameterPolicyT>::invoke(RootT * obj, const ParameterArray& parameters) const
    {
        ParameterArray out;
        bool success = true;
        BOOST_PP_REPEAT(n, METHOD_PARAMETER, param)
        if (success) 
        {
            out.push_back(Parameter(FACTORY_RETURN_PARAMETER, (static_cast<ClassT*>(obj)->*ptrMethod)(BOOST_PP_ENUM(n, METHOD_VALUE, param))));
            BOOST_PP_REPEAT(n, METHOD_RETURN, param)
        }
        return out;
    }
#else
    template <class RootT, class ClassT, class ReturnT, class ConstT, class KeyT>
    ParameterArray BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,ConstT,KeyT>::invoke(RootT * obj, const ParameterArray& parameters) const
    {
        ParameterArray out;
        out.push_back(Parameter(FACTORY_RETURN_PARAMETER, (static_cast<ClassT*>(obj)->*ptrMethod)()));
        return out;
    }
#endif

#undef METHOD_PARAMETER
#undef METHOD_VALUE
#undef METHOD_RETURN

#if n
    template <class RootT, class ClassT, class ReturnT, class PrototypeT, class ConstT, class KeyT, class ParameterPolicyT>
    MethodBase<RootT,KeyT>* BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,PrototypeT,ConstT,KeyT,ParameterPolicyT>::clone() const
    {
        return new BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,PrototypeT,ConstT,KeyT,ParameterPolicyT>(*this);
    }
#else
    template <class RootT, class ClassT, class ReturnT, class ConstT, class KeyT>
    MethodBase<RootT,KeyT>* BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,ConstT,KeyT>::clone() const
    {
        return new BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,ConstT,KeyT>(*this);
    }
#endif

// VOID SPECIALIZATION

#define METHOD_PROTOTYPE(z, n, data) PARAMETER_CALL_TYPE(PrototypeT,BOOST_PP_ADD(n,1))

#if n
    template <class RootT, class ClassT, class PrototypeT, class ConstT, class KeyT, class ParameterPolicyT>
    class BOOST_PP_CAT(Method,n)<RootT,ClassT,void,PrototypeT,ConstT,KeyT,ParameterPolicyT>
    : public MethodBase<RootT,KeyT>,
      public ParameterPolicyT
#else
    template <class RootT, class ClassT, class ConstT, class KeyT>
    class BOOST_PP_CAT(Method,n)<RootT,ClassT,void,ConstT,KeyT>
    : public MethodBase<RootT,KeyT>
#endif
    {
    private:
        template <class T>
        friend struct ReadParameter;
        template <class T>
        friend struct WriteParameter;
#if n
        // ptr method
        typedef void(ClassT::*method_t)(BOOST_PP_ENUM(n, METHOD_PROTOTYPE, ~));
        method_t ptrMethod;
#else
        // ptr method
        typedef void(ClassT::*method_t)();
        method_t ptrMethod;
#endif

    public:
        /** Constructeur
         @param key le nom de la classe à créer
        */
        BOOST_PP_CAT(Method,n)(typename call_traits<KeyT>::param_type key, method_t ptr)
        :MethodBase<RootT,KeyT>(key), ptrMethod(ptr)
        {}

        /** Invoque une methode
        @param parameters les paramètres de la méthode
        @return l'objet créé
        */
        virtual ParameterArray invoke(RootT * obj, const ParameterArray& parameters) const;
        /** Clone la method
        */
        MethodBase<RootT,KeyT>* clone() const;
    };

#undef METHOD_PROTOTYPE

#define METHOD_PARAMETER(z, n, data)                                        \
        PARAMETER_VALUE(PrototypeT,BOOST_PP_ADD(n,1)) BOOST_PP_CAT(data,n); \
        success = success &&                                                \
        ReadParameter<PARAMETER_TYPE(PrototypeT,BOOST_PP_ADD(n,1))>::Apply(*this,parameters,n,BOOST_PP_CAT(data,n));

#define METHOD_VALUE(z, n, data) BOOST_PP_CAT(data,n)

#define METHOD_RETURN(z, n, data)                                           \
        WriteParameter<PARAMETER_TYPE(PrototypeT,BOOST_PP_ADD(n,1))>::Apply(*this,out,n,BOOST_PP_CAT(data,n));

#if n
    template <class RootT, class ClassT, class PrototypeT, class ConstT, class KeyT, class ParameterPolicyT>
    ParameterArray BOOST_PP_CAT(Method,n)<RootT,ClassT,void,PrototypeT,ConstT,KeyT,ParameterPolicyT>::invoke(RootT * obj, const ParameterArray& parameters) const
    {
        ParameterArray out;
        bool success = true;
        BOOST_PP_REPEAT(n, METHOD_PARAMETER, param)
        if (success) 
        {
            (static_cast<ClassT*>(obj)->*ptrMethod)(BOOST_PP_ENUM(n, METHOD_VALUE, param));
            BOOST_PP_REPEAT(n, METHOD_RETURN, param)
        }
        return out;
    }
#else
    template <class RootT, class ClassT, class ConstT, class KeyT>
    ParameterArray BOOST_PP_CAT(Method,n)<RootT,ClassT,void,ConstT,KeyT>::invoke(RootT * obj, const ParameterArray& parameters) const
    {
        ParameterArray out;
        (static_cast<ClassT*>(obj)->*ptrMethod)();
        return out;
    }
#endif

#undef METHOD_PARAMETER
#undef METHOD_VALUE
#undef METHOD_RETURN

#if n
    template <class RootT, class ClassT, class PrototypeT, class ConstT, class KeyT, class ParameterPolicyT>
    MethodBase<RootT,KeyT>* BOOST_PP_CAT(Method,n)<RootT,ClassT,void,PrototypeT,ConstT,KeyT,ParameterPolicyT>::clone() const
    {
        return new BOOST_PP_CAT(Method,n)<RootT,ClassT,void,PrototypeT,ConstT,KeyT,ParameterPolicyT>(*this);
    }
#else
    template <class RootT, class ClassT, class ConstT, class KeyT>
    MethodBase<RootT,KeyT>* BOOST_PP_CAT(Method,n)<RootT,ClassT,void,ConstT,KeyT>::clone() const
    {
        return new BOOST_PP_CAT(Method,n)<RootT,ClassT,void,ConstT,KeyT>(*this);
    }
#endif

// END VOID SPECIALIZATION

// CONST SPECIALIZATION

#define METHOD_PROTOTYPE(z, n, data) PARAMETER_CALL_TYPE(PrototypeT,BOOST_PP_ADD(n,1))

#if n
    template <class RootT, class ClassT, class ReturnT, class PrototypeT, class KeyT, class ParameterPolicyT>
    class BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,PrototypeT,const_t,KeyT,ParameterPolicyT>
    : public MethodBase<RootT,KeyT>,
      public ParameterPolicyT
#else
    template <class RootT, class ClassT, class ReturnT, class KeyT>
    class BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,const_t,KeyT>
    : public MethodBase<RootT,KeyT>
#endif
    {
    private:
        template <class T>
        friend struct ReadParameter;
        template <class T>
        friend struct WriteParameter;
#if n
        // ptr method
        typedef ReturnT(ClassT::*method_t)(BOOST_PP_ENUM(n, METHOD_PROTOTYPE, ~))const;
        method_t ptrMethod;
#else
        // ptr method
        typedef ReturnT(ClassT::*method_t)()const;
        method_t ptrMethod;
#endif

    public:
        /** Constructeur
         @param key le nom de la classe à créer
        */
        BOOST_PP_CAT(Method,n)(typename call_traits<KeyT>::param_type key, method_t ptr)
        :MethodBase<RootT,KeyT>(key), ptrMethod(ptr)
        {}

        /** Invoque une methode
        @param parameters les paramètres de la méthode
        @return l'objet créé
        */
        virtual ParameterArray invoke(RootT * obj, const ParameterArray& parameters) const;
        /** Clone la method
        */
        MethodBase<RootT,KeyT>* clone() const;
    };

#undef METHOD_PROTOTYPE

#define METHOD_PARAMETER(z, n, data)                                        \
        PARAMETER_VALUE(PrototypeT,BOOST_PP_ADD(n,1)) BOOST_PP_CAT(data,n); \
        success = success &&                                                \
        ReadParameter<PARAMETER_TYPE(PrototypeT,BOOST_PP_ADD(n,1))>::Apply(*this,parameters,n,BOOST_PP_CAT(data,n));

#define METHOD_VALUE(z, n, data) BOOST_PP_CAT(data,n)

#define METHOD_RETURN(z, n, data)                                           \
        WriteParameter<PARAMETER_TYPE(PrototypeT,BOOST_PP_ADD(n,1))>::Apply(*this,out,n,BOOST_PP_CAT(data,n));

#if n
    template <class RootT, class ClassT, class ReturnT, class PrototypeT, class KeyT, class ParameterPolicyT>
    ParameterArray BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,PrototypeT,const_t,KeyT,ParameterPolicyT>::invoke(RootT * obj, const ParameterArray& parameters) const
    {
        ParameterArray out;
        bool success = true;
        BOOST_PP_REPEAT(n, METHOD_PARAMETER, param)
        if (success) 
        {
            out.push_back(Parameter(FACTORY_RETURN_PARAMETER, (static_cast<ClassT*>(obj)->*ptrMethod)(BOOST_PP_ENUM(n, METHOD_VALUE, param))));
            BOOST_PP_REPEAT(n, METHOD_RETURN, param)
        }
        return out;
    }
#else
    template <class RootT, class ClassT, class ReturnT, class KeyT>
    ParameterArray BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,const_t,KeyT>::invoke(RootT * obj, const ParameterArray& parameters) const
    {
        ParameterArray out;
        out.push_back(Parameter(FACTORY_RETURN_PARAMETER, (static_cast<ClassT*>(obj)->*ptrMethod)()));
        return out;
    }
#endif

#undef METHOD_PARAMETER
#undef METHOD_VALUE
#undef METHOD_RETURN

#if n
    template <class RootT, class ClassT, class ReturnT, class PrototypeT, class KeyT, class ParameterPolicyT>
    MethodBase<RootT,KeyT>* BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,PrototypeT,const_t,KeyT,ParameterPolicyT>::clone() const
    {
        return new BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,PrototypeT,const_t,KeyT,ParameterPolicyT>(*this);
    }
#else
    template <class RootT, class ClassT, class ReturnT, class KeyT>
    MethodBase<RootT,KeyT>* BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,const_t,KeyT>::clone() const
    {
        return new BOOST_PP_CAT(Method,n)<RootT,ClassT,ReturnT,const_t,KeyT>(*this);
    }
#endif

// VOID SPECIALIZATION

#define METHOD_PROTOTYPE(z, n, data) PARAMETER_CALL_TYPE(PrototypeT,BOOST_PP_ADD(n,1))

#if n
    template <class RootT, class ClassT, class PrototypeT, class KeyT, class ParameterPolicyT>
    class BOOST_PP_CAT(Method,n)<RootT,ClassT,void,PrototypeT,const_t,KeyT,ParameterPolicyT>
    : public MethodBase<RootT,KeyT>,
      public ParameterPolicyT
#else
    template <class RootT, class ClassT, class KeyT>
    class BOOST_PP_CAT(Method,n)<RootT,ClassT,void,const_t,KeyT>
    : public MethodBase<RootT,KeyT>
#endif
    {
    private:
        template <class T>
        friend struct ReadParameter;
        template <class T>
        friend struct WriteParameter;
#if n
        // ptr method
        typedef void(ClassT::*method_t)(BOOST_PP_ENUM(n, METHOD_PROTOTYPE, ~))const;
        method_t ptrMethod;
#else
        // ptr method
        typedef void(ClassT::*method_t)()const;
        method_t ptrMethod;
#endif

    public:
        /** Constructeur
         @param key le nom de la classe à créer
        */
        BOOST_PP_CAT(Method,n)(typename call_traits<KeyT>::param_type key, method_t ptr)
        :MethodBase<RootT,KeyT>(key), ptrMethod(ptr)
        {}

        /** Invoque une methode
        @param parameters les paramètres de la méthode
        @return l'objet créé
        */
        virtual ParameterArray invoke(RootT * obj, const ParameterArray& parameters) const;
        /** Clone la method
        */
        MethodBase<RootT,KeyT>* clone() const;
    };

#undef METHOD_PROTOTYPE

#define METHOD_PARAMETER(z, n, data)                                        \
        PARAMETER_VALUE(PrototypeT,BOOST_PP_ADD(n,1)) BOOST_PP_CAT(data,n); \
        success = success &&                                                \
        ReadParameter<PARAMETER_TYPE(PrototypeT,BOOST_PP_ADD(n,1))>::Apply(*this,parameters,n,BOOST_PP_CAT(data,n));

#define METHOD_VALUE(z, n, data) BOOST_PP_CAT(data,n)

#define METHOD_RETURN(z, n, data)                                           \
        WriteParameter<PARAMETER_TYPE(PrototypeT,BOOST_PP_ADD(n,1))>::Apply(*this,out,n,BOOST_PP_CAT(data,n));

#if n
    template <class RootT, class ClassT, class PrototypeT, class KeyT, class ParameterPolicyT>
    ParameterArray BOOST_PP_CAT(Method,n)<RootT,ClassT,void,PrototypeT,const_t,KeyT,ParameterPolicyT>::invoke(RootT * obj, const ParameterArray& parameters) const
    {
        ParameterArray out;
        bool success = true;
        BOOST_PP_REPEAT(n, METHOD_PARAMETER, param)
        if (success) 
        {
            (static_cast<ClassT*>(obj)->*ptrMethod)(BOOST_PP_ENUM(n, METHOD_VALUE, param));
            BOOST_PP_REPEAT(n, METHOD_RETURN, param)
        }
        return out;
    }
#else
    template <class RootT, class ClassT, class KeyT>
    ParameterArray BOOST_PP_CAT(Method,n)<RootT,ClassT,void,const_t,KeyT>::invoke(RootT * obj, const ParameterArray& parameters) const
    {
        ParameterArray out;
        (static_cast<ClassT*>(obj)->*ptrMethod)();
        return out;
    }
#endif

#undef METHOD_PARAMETER
#undef METHOD_VALUE
#undef METHOD_RETURN

#if n
    template <class RootT, class ClassT, class PrototypeT, class KeyT, class ParameterPolicyT>
    MethodBase<RootT,KeyT>* BOOST_PP_CAT(Method,n)<RootT,ClassT,void,PrototypeT,const_t,KeyT,ParameterPolicyT>::clone() const
    {
        return new BOOST_PP_CAT(Method,n)<RootT,ClassT,void,PrototypeT,const_t,KeyT,ParameterPolicyT>(*this);
    }
#else
    template <class RootT, class ClassT, class KeyT>
    MethodBase<RootT,KeyT>* BOOST_PP_CAT(Method,n)<RootT,ClassT,void,const_t,KeyT>::clone() const
    {
        return new BOOST_PP_CAT(Method,n)<RootT,ClassT,void,const_t,KeyT>(*this);
    }
#endif

// END VOID SPECIALIZATION
// END CONST SPECIALIZATION

// namespace fctr
}

#undef n
