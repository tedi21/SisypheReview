/**
 * @class            : Parameter
 * @date             : 12/02/2007
 * @author           : Teddy DIDÉ
 * @version          : 9.0
 * @brief            : Classes permettant d'encapsuler les paramètres pour les Factory
 */

#ifndef PARAMETER_H
#define PARAMETER_H

#include "NamedParameter.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/export.hpp>
#include <string>

namespace fctr {

    class Parameter
    {
    private:
        // Attributes
        boost::shared_ptr<ParameterBase> ptr;
        // Archive
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version){
            ar & BOOST_SERIALIZATION_NVP(ptr);
        }

    public:
        // Constructors
        Parameter()
        {}

        // Named value
        template <class KeyT, class T>
        Parameter(KeyT name, T value)
        : ptr(new NamedParameter<T,KeyT>(name, value))
        {}

        // Type
        std::string type() const
        {
             return ptr->type();
        }

        // Named Value
        template <class KeyT, class T>
        bool value(KeyT name, T& value) const
        {
            bool success = false;
            boost::shared_ptr< NamedParameter<T,KeyT> > p = boost::dynamic_pointer_cast< NamedParameter<T,KeyT> >(ptr);
            if (p && p->name() == name)
            {
                 value = p->value();
                 success = true;
            }
            return success;
        }
    };

    #define FACTORY_PARAMETER_SERIAL2(KeyT, T) \
        typedef fctr::NamedParameter<T,KeyT> BOOST_PP_CAT(NamedParameter_,T);\
        BOOST_CLASS_EXPORT(BOOST_PP_CAT(NamedParameter_,T))

    #define FACTORY_PARAMETER_SERIAL(T) \
        FACTORY_PARAMETER_SERIAL2(size_t, T)

    #define FACTORY_RETURN_PARAMETER size_t(-1)
}

#endif
