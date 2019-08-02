/**
 * @class FactoryBase
 * @date 03/02/2007
 * @author Teddy DIDÉ
 * @version 6.0
 * @brief Interface des factory, permet le polymorphisme dans le gestionnaire de factory </br> Root : La classe de Base 
 */

#ifndef FACTORY_BASE_HPP
#define FACTORY_BASE_HPP

#include <boost/call_traits.hpp>
#include <string>
#include "ParameterArray.hpp"

using namespace std;
using namespace boost;

namespace fctr {

    template<class RootT, class KeyT = string>
    class FactoryBase {
    protected:
        /// le nom identifiant de la classe
        KeyT key;

    public: 
        /** Constructeur
        @param key le nom identifiant de la classe
        */
        FactoryBase(typename call_traits<KeyT>::param_type _key);
        /// Destructeur
        virtual ~FactoryBase();
        /** retourne la clé de la classe
        @return l'identifiant de la classe
        */
        typename call_traits<KeyT>::const_reference getKey() const ;
        /** retourne l'objet créé 
        @param parameters les paramètres du constructeur
        @return l'objet créé
        */
        virtual RootT * create(const ParameterArray& parameters) const = 0;
        /** supprime l'objet créé 
        @param l'objet créé
        */
        virtual void release(RootT * obj) const = 0;
        /** clone la factory
        */
        virtual FactoryBase* clone() const = 0;
    };

    /*
     * Définitions des méthodes
     */

    // construction
    template<class RootT, class KeyT>
    FactoryBase<RootT,KeyT>::FactoryBase(typename call_traits<KeyT>::param_type _key) 
    : key(_key)
    {}

    // destruction
    template<class RootT, class KeyT>
    FactoryBase<RootT,KeyT>::~FactoryBase()
    {}

    // retourne le type de la classe
    template<class RootT, class KeyT>
    typename call_traits<KeyT>::const_reference 
    FactoryBase<RootT,KeyT>::getKey() const {
        return key;
    }

    template<class RootT, class KeyT>
    inline FactoryBase<RootT,KeyT>* 
    new_clone( const FactoryBase<RootT,KeyT>& r )
    {
        return r.clone();
    }

}

#endif
