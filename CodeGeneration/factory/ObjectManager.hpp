/**
 * @class ObjectManager
 * @date 06/09/2008
 * @author Teddy DIDÉ
 * @version 1.0
 * @brief Gestionnaire de Object </br> Root : La classe de Base
 */

#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

#include <boost/ptr_container/ptr_map.hpp>
#include <boost/call_traits.hpp>
#include <string>
#include "FactoryExport.hpp"
#include "UnRegisteredObjectException.hpp"
#include "convert.hpp"

using namespace std;
using namespace boost;

namespace fctr {

// Classe qui permet d'instancier les classes dérivées d'une classe commune
template<class RootT, class KeyT = string>
class ObjectManager {
private :
    /// redéfinition des types
	typedef ptr_map<KeyT,RootT> obj_map_t;
    typedef typename obj_map_t::iterator obj_iterator_t;

    /// singleton
    static ObjectManager * objectManager;
    /// Constructeur
    ObjectManager();
    /// Destructeur
    ~ObjectManager();

    /// stockage des infos
    obj_map_t obj_map;

public:
    /// enregistrement d'une classe dérivée
    FACTORY_API void registerObject(typename call_traits<KeyT>::value_type key, RootT * obj);
    /// suppression de l'enregistrement
    FACTORY_API void unRegisterObject(typename call_traits<KeyT>::param_type _key);
    /** retourne un objet correspondant au type key
     @param key l'identifiant de l'objet
     @return l'objet correspondant à l'identifiant key
     */
    FACTORY_API RootT * getObject(typename call_traits<KeyT>::param_type key);
    /** retourne si un objet correspond au type key
     @param key l'identifiant de l'objet
     @return l'objet correspondant à l'identifiant key a été trouvé
     */
    FACTORY_API bool existKey(typename call_traits<KeyT>::param_type key);
    /** retourne le gestionnaire de factory
     @return le gestionnaire
     */
    FACTORY_API static ObjectManager<RootT,KeyT> * getInstance();
};

/*
 * Définitions des méthodes
 */
#if !defined(HAS_FACTORY_DLL) || defined(BUILD_FACTORY_DLL)

// Constructeur
template<class RootT, class KeyT>
ObjectManager<RootT,KeyT>::ObjectManager()
{}

// Destructeur
template<class RootT, class KeyT>
ObjectManager<RootT,KeyT>::~ObjectManager() {
    obj_map.clear();
}

// enregistrement d'une classe dérivée
template<class RootT, class KeyT>
void ObjectManager<RootT,KeyT>::registerObject(typename call_traits<KeyT>::value_type key, RootT * obj) {
    obj_map.insert(key, obj);
}

// suppression de l'enregistrement
template<class RootT, class KeyT>
void ObjectManager<RootT,KeyT>::unRegisterObject(typename call_traits<KeyT>::param_type _key) {
    obj_iterator_t i = obj_map.find(_key);
    if (i == obj_map.end())
        throw UnRegisteredObjectException(ToString::parse(_key).c_str());
    obj_map.erase(i);
}

// instancie un objet correspondant au type
template<class RootT, class KeyT>
RootT *
ObjectManager<RootT,KeyT>::getObject(typename call_traits<KeyT>::param_type key) {
    obj_iterator_t i = obj_map.find(key);
    if (i == obj_map.end())
        throw UnRegisteredObjectException(ToString::parse(key).c_str());
    return i->second;
}

template<class RootT, class KeyT>
bool
ObjectManager<RootT,KeyT>::existKey(typename call_traits<KeyT>::param_type key) {
    obj_iterator_t i = obj_map.find(key);
    return i!=obj_map.end();
}

template<class RootT, class KeyT>
ObjectManager<RootT,KeyT> * ObjectManager<RootT,KeyT>::objectManager = NULL;

template<class RootT, class KeyT>
ObjectManager<RootT,KeyT> * ObjectManager<RootT,KeyT>::getInstance(){
    if (objectManager == NULL){
        objectManager = new ObjectManager<RootT,KeyT>();
    }
    return objectManager;
}

#endif // !defined(HAS_FACTORY_DLL) || defined(BUILD_FACTORY_DLL)

}

#endif
