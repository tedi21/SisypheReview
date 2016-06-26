
namespace gen {

    template <class T>
    inline typename get_type_generator<typename callback_trait<T>::result_t,T>::type_t
    call_g(const T & f)
    {
        return typename get_type_generator<typename callback_trait<T>::result_t,T>::type_t(f);
    }

    template <class C, class T>
    inline typename get_type_generator_tpl<typename callback_trait<T>::result_t,T,C>::type_t
    callT_g(const T & f)
    {
        return typename get_type_generator_tpl<typename callback_trait<T>::result_t,T,C>::type_t(f);
    }

}