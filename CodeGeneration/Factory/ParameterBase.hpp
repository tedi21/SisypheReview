/**
 * @class            : ParameterBase
 * @date             : 12/02/2007
 * @author           : Teddy DIDÉ
 * @version          : 9.0
 * @brief            : Classes permettant d'encapsuler les paramètres pour les Factory
 */

#ifndef PARAMETER_BASE_H
#define PARAMETER_BASE_H

#include <typeinfo>
#include <string>
#include <boost/serialization/serialization.hpp>

namespace fctr {

    class ParameterBase
    {
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        {}

    public:
        virtual ~ParameterBase() {}
        virtual std::string type() const = 0;
    };

}

#endif
