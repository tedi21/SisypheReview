/**
 * @class            : NamedParameter
 * @date             : 12/02/2007
 * @author           : Teddy DIDÉ
 * @version          : 9.0
 * @brief            : Classes permettant d'encapsuler les paramètres pour les Factory
 */

#ifndef NAMED_PARAMETER_H
#define NAMED_PARAMETER_H

#include "ParameterBase.hpp"
#include <boost/call_traits.hpp>
#include <boost/serialization/void_cast.hpp>

namespace fctr {

    template<class T, class KeyT = std::string>
    class NamedParameter
    : public ParameterBase
    {
    private:
        // Attribute
        T parameter;
        KeyT parameter_name;
        // Archive
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version){
            // method 2 : explicitly register base/derived relationship
            boost::serialization::void_cast_register< NamedParameter, ParameterBase >(
                static_cast<NamedParameter *>(NULL),
                static_cast<ParameterBase *>(NULL)
            );
            ar & BOOST_SERIALIZATION_NVP(parameter_name);
            ar & BOOST_SERIALIZATION_NVP(parameter);
        }

    public:
        // Constructors
        NamedParameter(typename boost::call_traits<KeyT>::param_type name, typename boost::call_traits<T>::param_type p)
        : parameter(p), parameter_name(name)
        {}

        NamedParameter()
        {}

        // Accessors
        void value(typename boost::call_traits<KeyT>::param_type name, typename boost::call_traits<T>::param_type p)
        {
            parameter_name = name;
            parameter = p;
        }

        typename boost::call_traits<T>::const_reference value() const
        {
             return parameter;
        }

        std::string type() const
        {
             return typeid(parameter).name();
        }

        typename boost::call_traits<KeyT>::const_reference name() const
        {
             return parameter_name;
        }
    };

}

#endif
