/**
 * @class            : Prototype
 * @date             : 01/04/2011
 * @author           : Teddy DIDÉ
 * @version          : 9.0
 * @brief            : Classes permettant d'encapsuler les types des paramètres pour les Factory
 */

#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <string>
#include <boost/call_traits.hpp>

#ifndef FCTR_MAX_SIZE
#  define FCTR_MAX_SIZE 10
#endif

namespace fctr {

    template <class PrototypeT, int I, bool _false>
    struct IsParameterType {
        typedef typename IsParameterType<typename PrototypeT::parent_t,I,I==PrototypeT::parent_t::Index>::parameter_t parameter_t;
    };

    template <class PrototypeT, int I>
    struct IsParameterType<PrototypeT,I,true> {
        typedef typename PrototypeT::parameter_t parameter_t;
    };

    template <class PrototypeT, int I>
    struct ParameterType {
        typedef typename IsParameterType<PrototypeT,I,I==PrototypeT::Index>::parameter_t parameter_t;
    };

    template <class T>
    struct In {
        typedef T value_t;
        typedef typename boost::call_traits<T>::param_type param_t;
    };        

    template <class T>
    struct Out {
        typedef T value_t;
        typedef typename boost::call_traits<T>::reference param_t;
    };

    template <class T>
    struct InOut {
        typedef T value_t;
        typedef typename boost::call_traits<T>::reference param_t;
    };

    template <class T>
    struct ReadParameter
    {
        template <class MethodT>
        static bool Apply(const MethodT& method, const ParameterArray& parameters, size_t index, typename T::value_t& value)
        {
            return true;
        }
    };

    template <class T>
    struct ReadParameter< In<T> >
    {
        template <class MethodT>
        static bool Apply(const MethodT& method, const ParameterArray& parameters, size_t index, T& value)
        {
            return method.getParameter(parameters, index, value);
        }
    };

    template <class T>
    struct ReadParameter< InOut<T> >
    {
        template <class MethodT>
        static bool Apply(const MethodT& method, const ParameterArray& parameters, size_t index, T& value)
        {
            return method.getParameter(parameters, index, value);
        }
    };

    template <class T>
    struct WriteParameter
    {
        template <class MethodT>
        static void Apply(const MethodT&, ParameterArray&, size_t, const typename T::value_t&)
        {}
    };

    template <class T>
    struct WriteParameter< Out<T> >
    {
        template <class MethodT>
        static void Apply(const MethodT& method, ParameterArray& parameters, size_t index, const T& value)
        {
            method.addParameter(parameters, index, value);
        }
    };

    template <class T>
    struct WriteParameter< InOut<T> >
    {
        template <class MethodT>
        static void Apply(const MethodT& method, ParameterArray& parameters, size_t index, const T& value)
        {
            method.addParameter(parameters, index, value);
        }
    };
}

#define PARAMETER_TYPE(Prototype,i)    \
    typename ParameterType<Prototype,i>::parameter_t

#define PARAMETER_VALUE(Prototype,i)    \
    PARAMETER_TYPE(Prototype,i)::value_t

#define PARAMETER_CALL_TYPE(Prototype,i) \
    PARAMETER_TYPE(Prototype,i)::param_t

#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#define BOOST_PP_ITERATION_LIMITS (0, FCTR_MAX_SIZE)
#define BOOST_PP_FILENAME_1       "PrototypeSpec.hpp"
#include BOOST_PP_ITERATE()

#endif
