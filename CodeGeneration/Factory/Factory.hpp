/**
 * @class           : Factory
 * @date            : 03/02/2007
 * @author          : Teddy DID�
 * @version         : 9.0
 * @brief           : La classe permet de cr�er des instances de la classe indiqu�e.
 *                    Root : La classe de Base, T : la classe � instancier
 */

#ifndef FACTORY_H
#define FACTORY_H

#include "FactoryBase.hpp"
#include "Prototype.hpp"

#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#define BOOST_PP_ITERATION_LIMITS (0, FCTR_MAX_SIZE)
#define BOOST_PP_FILENAME_1       "FactorySpec.hpp"
#include BOOST_PP_ITERATE()

namespace fctr {
    //////////////////////////////////////////////////////////////////
    //                Factory Constructeur Tableau                  //
    //////////////////////////////////////////////////////////////////
    typedef Prototype1< In<size_t> > PrototypeArray;
    /// Classe qui permet de cr�er un objet de la classe indiqu�e
    template<class RootT, class T, class PrototypeT = PrototypeArray, class KeyT = std::string, class ParameterPolicyT = IndexedParameterPolicy>
    class FactoryArray 
    : public FactoryBase<RootT,KeyT>,
      public ParameterPolicyT
    {
    public:
        /** Constructeur
         @param key le nom de la classe � cr�er
        */
        FactoryArray(typename boost::call_traits<KeyT>::param_type key)
        :FactoryBase<RootT,KeyT>(key)
        {}
        /** Instancie un nouvel objet de la classe indiqu�e
        @param parameters les param�tres du constructeur
        @return l'objet cr��
        */
        RootT * create(const ParameterArray& parameters) const;
        /** supprime l'objet cr��
        @param l'objet cr��
        */
        void release(RootT * obj) const;
        /** clone la factory
        */
        FactoryBase<RootT,KeyT>* clone() const;
    };

    // instancie des nouveaux objets de la classe indiqu�e
    template<class RootT, class T, class PrototypeT, class KeyT, class ParameterPolicyT>
    RootT * FactoryArray<RootT,T,PrototypeT,KeyT,ParameterPolicyT>::create(const ParameterArray& parameters) const {
        PARAMETER_VALUE(PrototypeT, 1) count;
        if (getParameter(parameters, 0, count)) {
            return new T[count];
        }
        return NULL;
    }

    template<class RootT, class T, class PrototypeT, class KeyT, class ParameterPolicyT>
    void FactoryArray<RootT,T,PrototypeT,KeyT,ParameterPolicyT>::release(RootT * obj) const {
        if (obj) {
            delete[] ((T*) obj);
            obj = NULL;
        }
    }

    template<class RootT, class T, class PrototypeT, class KeyT, class ParameterPolicyT>
    FactoryBase<RootT,KeyT>* FactoryArray<RootT,T,PrototypeT,KeyT,ParameterPolicyT>::clone() const {
        return new FactoryArray<RootT,T,PrototypeT,KeyT,ParameterPolicyT>(*this);
    }

    //////////////////////////////////////////////////////////////////
    //                Factory AUTO REGISTRATION                        //
    //////////////////////////////////////////////////////////////////
    template <class ClassT>
    class FactoryRegistration
    {
    private:
        template <class T>
        struct EncapsulatedRegistration {
            EncapsulatedRegistration(){
                T::register_class();
            }
            ~EncapsulatedRegistration(){
                T::unregister_class();
            }
        };
    public:
        typedef EncapsulatedRegistration<ClassT> type;
        static const EncapsulatedRegistration<ClassT> registrationInstance;
    };

    template<class T>
    const typename FactoryRegistration<T>::type FactoryRegistration<T>::registrationInstance;

    #define FACTORY_EXPORT_FILE(T, FILE__)  \
        FactoryRegistration< T >::type const & BOOST_PP_CAT(BOOST_PP_CAT(FactoryRegistration,FILE__),__LINE__) = FactoryRegistration< T >::registrationInstance;

    #define FACTORY_EXPORT(T)  \
        FACTORY_EXPORT_FILE(T, _)

}

#endif
