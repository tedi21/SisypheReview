/**
 * @class ClassManager
 * @date 03/02/2007
 * @author Teddy DIDÉ
 * @version 8.0
 * @brief Gestionnaire de Class </br> Root : La classe de Base 
 */

#ifndef CLASS_MANAGER_HPP
#define CLASS_MANAGER_HPP

#include <boost/ptr_container/ptr_map.hpp>
#include <boost/call_traits.hpp>
#include <string>
#include "FactoryExport.hpp"
#include "UnRegisteredClassException.hpp"
#include "ParameterArray.hpp"
#include "FactoryBase.hpp"
#include "MethodBase.hpp"
#include "convert.hpp"

using namespace std;
using namespace boost;

namespace fctr {

    // Classe qui permet d'instancier les classes dérivées d'une classe commune
    template<class RootT, class KeyT = string>
    class ClassManager {
    private :
        /// redéfinition des types
        typedef FactoryBase<RootT,KeyT> FactoryBase_t;
		typedef ptr_map<KeyT, FactoryBase_t> fact_map_t;
        typedef typename fact_map_t::const_iterator const_fact_iterator_t;
        typedef typename fact_map_t::iterator fact_iterator_t;

        typedef MethodBase<RootT,KeyT> MethodBase_t;
		typedef ptr_map<KeyT, MethodBase_t> meth_map_t;
        typedef typename meth_map_t::const_iterator const_meth_iterator_t;
        typedef typename meth_map_t::iterator meth_iterator_t;

        /// singleton
        static ClassManager * classManager;
        /// Constructeur
        ClassManager();
        /// Destructeur
        ~ClassManager();

        /// stockage des infos
		fact_map_t fact_map;
        meth_map_t meth_map;

    public:
        /// enregistrement d'une classe dérivée
        FACTORY_API void registerClass(FactoryBase_t * fb);
        /// enregistrement d'une methode
        FACTORY_API void registerMethod(MethodBase_t * tb);
        /// suppression de l'enregistrement 
        FACTORY_API void unRegisterClass(typename call_traits<KeyT>::param_type _key);
        /// suppression de l'enregistrement
        FACTORY_API void unRegisterMethod(typename call_traits<KeyT>::param_type _key);
        /** instancie un objet correspondant au type key
         @param key l'identifiant de la classe 
         @param parameters les paramètres du constructeur
         @return la classe instancié correspondant à l'identifiant key
         */
        FACTORY_API RootT * create(typename call_traits<KeyT>::param_type key, const ParameterArray& parameters) const;
        /** instancie un objet correspondant au type key
         @param key l'identifiant de la classe 
         @return la classe instancié correspondant à l'identifiant key
         */
        FACTORY_API RootT * create(typename call_traits<KeyT>::param_type key) const;
        /** supprime un objet
         @param key l'identifiant de la classe 
         @param obj la classe instancié correspondant à l'identifiant key
         */
        FACTORY_API void release(typename call_traits<KeyT>::param_type key, RootT * obj) const;
        /** invoque une méthode correspondant au type key
         @param key l'identifiant de la méthode 
         @param obj l'objet
         @param parameters les paramètres de la méthode
         @return le retour de la méthode
         */
        FACTORY_API ParameterArray invoke(typename call_traits<KeyT>::param_type key, RootT * obj, const ParameterArray& parameters) const;
        /** invoque une méthode correspondant au type key
         @param key l'identifiant de la méthode 
         @param obj l'objet
         @return le retour de la méthode
         */
        FACTORY_API ParameterArray invoke(typename call_traits<KeyT>::param_type key, RootT * obj) const;
        /** retourne le gestionnaire de factory
         @return le gestionnaire
         */
        FACTORY_API static ClassManager<RootT,KeyT> * getInstance();
    };

    /*
     * Définitions des méthodes
     */

#if !defined(HAS_FACTORY_DLL) || defined(BUILD_FACTORY_DLL) 
    // Constructeur
    template<class RootT, class KeyT>
    ClassManager<RootT,KeyT>::ClassManager() 
    {}

    // Destructeur
    template<class RootT, class KeyT>
    ClassManager<RootT,KeyT>::~ClassManager() {
        fact_map.clear();
        //meth_map.clear();
    }

    // enregistrement d'une classe dérivée
    template<class RootT, class KeyT>
    void ClassManager<RootT,KeyT>::registerClass(FactoryBase_t * fb) {
        KeyT key = fb->getKey();
        fact_map.insert(key, fb);
    }

    template<class RootT, class KeyT>
    void ClassManager<RootT,KeyT>::registerMethod(MethodBase_t * tb) {
        KeyT key = tb->getKey();
        meth_map.insert(key, tb);
    }

    // suppression de l'enregistrement 
    template<class RootT, class KeyT>
    void ClassManager<RootT,KeyT>::unRegisterClass(typename call_traits<KeyT>::param_type _key) {
        fact_iterator_t i = fact_map.find(_key);
        if (i == fact_map.end())
            throw UnRegisteredClassException(ToString::parse(_key).c_str());
        fact_map.erase(i);
    }

    template<class RootT, class KeyT>
    void ClassManager<RootT,KeyT>::unRegisterMethod(typename call_traits<KeyT>::param_type _key) {
        meth_iterator_t i = meth_map.find(_key);
        if (i == meth_map.end())
            throw UnRegisteredClassException(ToString::parse(_key).c_str());
        meth_map.erase(i);
    }

    // instancie un objet correspondant au type
    template<class RootT, class KeyT>
    RootT *
    ClassManager<RootT,KeyT>::create(typename call_traits<KeyT>::param_type key, const ParameterArray& parameters) const {
        const_fact_iterator_t i = fact_map.find(key);
        if (i == fact_map.end())
            throw UnRegisteredClassException(ToString::parse(key).c_str());
        return i->second->create(parameters);
    }

    template<class RootT, class KeyT>
    RootT *
    ClassManager<RootT,KeyT>::create(typename call_traits<KeyT>::param_type key) const {
        ParameterArray unused;
        return create(key, unused);
    }

    // suppression de l'objet
    template<class RootT, class KeyT>
    void 
    ClassManager<RootT,KeyT>::release(typename call_traits<KeyT>::param_type key, RootT * obj) const {
        const_fact_iterator_t i = fact_map.find(key);
        if (i == fact_map.end())
            throw UnRegisteredClassException(ToString::parse(key).c_str());
        i->second->release(obj);
    }

    // invocation d'une méthode
    template<class RootT, class KeyT>
    ParameterArray
    ClassManager<RootT,KeyT>::invoke(typename call_traits<KeyT>::param_type key, RootT * obj, const ParameterArray& parameters) const {
        const_meth_iterator_t i = meth_map.find(key);
        if (i == meth_map.end())
            throw UnRegisteredClassException(ToString::parse(key).c_str());
        return i->second->invoke(obj, parameters);
    }

    template<class RootT, class KeyT>
    ParameterArray
    ClassManager<RootT,KeyT>::invoke(typename call_traits<KeyT>::param_type key, RootT * obj) const {
        ParameterArray unused;
        return invoke(key, obj, unused);
    }

    // singleton
    template<class RootT, class KeyT>
    ClassManager<RootT,KeyT> * ClassManager<RootT,KeyT>::classManager = NULL;

    template<class RootT, class KeyT>
    ClassManager<RootT,KeyT> * ClassManager<RootT,KeyT>::getInstance(){
        if (classManager == NULL){
            classManager = new ClassManager<RootT,KeyT>();
        }
        return classManager;
    }

#endif

}

#endif
