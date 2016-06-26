/**
 * @class MethodBase
 * @date 03/02/2007
 * @author Teddy DIDÉ
 * @version 7.0
 * @brief Interface des Method, permet le polymorphisme dans le gestionnaire de Method </br> Root : La classe de Base 
 */

#ifndef METHOD_BASE_HPP
#define METHOD_BASE_HPP

#include <boost/call_traits.hpp>
#include <string>
#include "ParameterArray.hpp"

namespace fctr {

    template<class RootT, class KeyT = std::string>
    class MethodBase {
        /// le nom identifiant de la classe
        KeyT key;

    public: 
        /** Constructeur
        @param key le nom identifiant de la classe
        */
        MethodBase(typename call_traits<KeyT>::param_type _key);
        /// Destructeur
        virtual ~MethodBase();
        /** retourne la clé de la classe
        @return l'identifiant de la classe
        */
        typename call_traits<KeyT>::const_reference getKey() const ;
        /** invoke method
        @param parameters les paramètres de la methode
        @return retour methode
        */
        virtual ParameterArray invoke(RootT * obj, const ParameterArray& parameters) const = 0;
        /** clone la method
        */
        virtual MethodBase* clone() const = 0;
    };

    /*
     * Définitions des méthodes
     */

    // construction
    template<class RootT, class KeyT>
    MethodBase<RootT,KeyT>::MethodBase(typename call_traits<KeyT>::param_type _key) 
    : key(_key)
    {}

    // destruction
    template<class RootT, class KeyT>
    MethodBase<RootT,KeyT>::~MethodBase()
    {}

    // retourne le type de la classe
    template<class RootT, class KeyT>
    typename call_traits<KeyT>::const_reference 
    MethodBase<RootT,KeyT>::getKey() const {
        return key;
    }

    template<class RootT, class KeyT>
    inline MethodBase<RootT,KeyT>* 
    new_clone( const MethodBase<RootT,KeyT>& r )
    {
        return r.clone();
    }
}

#endif
