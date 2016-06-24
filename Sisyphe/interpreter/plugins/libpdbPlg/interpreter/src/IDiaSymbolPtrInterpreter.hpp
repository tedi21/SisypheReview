/*
 * IDiaSymbolPtrInterpreter.hpp
 *
 *
 * @date 21-06-2016
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#ifndef _IDIASYMBOLPTR_INTERPRETER_H_
#define _IDIASYMBOLPTR_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "Array.hpp"
#include "DiaPtr.h"
typedef CDiaPtr<IDiaSymbol> IDiaSymbolPtr;
#include "IDiaEnumSymbolsPtrInterpreter.hpp"
#include "SymTagEnumTypeInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// Classe représentant un symbole.
	template <class EncodingT>
	class IDiaSymbolPtrInterpreter
	: public Base<EncodingT>
	{
	private:
		IDiaSymbolPtr m_object;

		void initValue(const IDiaSymbolPtr& object);

		IDiaSymbolPtr& value();

		const IDiaSymbolPtr& value() const;

		void tidyValue();

	public:
		IDiaSymbolPtrInterpreter();

		~IDiaSymbolPtrInterpreter();

		IDiaSymbolPtrInterpreter(const IDiaSymbolPtr& object);

		IDiaSymbolPtrInterpreter(const IDiaSymbolPtrInterpreter<EncodingT>& rhs);

		IDiaSymbolPtrInterpreter<EncodingT>& operator=(const IDiaSymbolPtrInterpreter<EncodingT>& rhs);

		const IDiaSymbolPtr& getValue() const;

		void setValue(IDiaSymbolPtr const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);

		// Récupère les enfants du symbole.
		FACTORY_PROTOTYPE4(findChildren, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > findChildren(const shared_ptr< Base<EncodingT> >& symtag, const shared_ptr< Base<EncodingT> >& name, const shared_ptr< Base<EncodingT> >& compareFlags, shared_ptr< Base<EncodingT> >& ppResult);

		// Récupère les enfants du symbole.
		FACTORY_PROTOTYPE2(findChildren, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > findChildren(const shared_ptr< Base<EncodingT> >& symtag, shared_ptr< Base<EncodingT> >& ppResult);

		// Extrait le nom du symbole.
		FACTORY_PROTOTYPE1(get_name, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_name(shared_ptr< Base<EncodingT> >& pRetVal);

		// Extrait la partie de section d'un emplacement d'adresse.
		FACTORY_PROTOTYPE1(get_addressSection, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_addressSection(shared_ptr< Base<EncodingT> >& pRetVal);

		// Extrait la partie d'offset à un emplacement d'adresse.
		FACTORY_PROTOTYPE1(get_addressOffset, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_addressOffset(shared_ptr< Base<EncodingT> >& pRetVal);

		// Récupère l'adresse virtuelle relative (RVA) du symbole.
		FACTORY_PROTOTYPE1(get_relativeVirtualAddress, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_relativeVirtualAddress(shared_ptr< Base<EncodingT> >& pRetVal);

		// Récupère le symbole qui représente le type pour ce symbole.
		FACTORY_PROTOTYPE1(get_type, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_type(shared_ptr< Base<EncodingT> >& pRetVal);

		// Extrait une balise qui indique si le type de données défini par l'utilisateur est constante.
		FACTORY_PROTOTYPE1(get_constType, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_constType(shared_ptr< Base<EncodingT> >& pRetVal);

		// extrait la classification variable d'un symbole de données.
		FACTORY_PROTOTYPE1(get_dataKind, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_dataKind(shared_ptr< Base<EncodingT> >& pRetVal);

		// Extrait une balise qui indique si le type de données défini par l'utilisateur possède un constructeur ou un destructeur.
		FACTORY_PROTOTYPE1(get_constructor, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_constructor(shared_ptr< Base<EncodingT> >& pRetVal);

		// Récupère le type de base pour ce symbole.
		FACTORY_PROTOTYPE1(get_baseType, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_baseType(shared_ptr< Base<EncodingT> >& pRetVal);

		// Extrait une balise qui indique si le type de données défini par (UDT) l'utilisateur est volatile.
		FACTORY_PROTOTYPE1(get_volatileType, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_volatileType(shared_ptr< Base<EncodingT> >& pRetVal);

		// extrait une balise qui spécifie si la fonction est virtuelle.
		FACTORY_PROTOTYPE1(get_virtual, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_virtual(shared_ptr< Base<EncodingT> >& pRetVal);

		// Extrait une balise qui spécifie si la fonction ou la couche de conversion de code a été marquée comme static.
		FACTORY_PROTOTYPE1(get_isStatic, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_isStatic(shared_ptr< Base<EncodingT> >& pRetVal);

		// Spécifie si la variable distribue une valeur de retour.
		FACTORY_PROTOTYPE1(get_isReturnValue, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_isReturnValue(shared_ptr< Base<EncodingT> >& pRetVal);

		// Récupère le classifieur de type de symbole.
		FACTORY_PROTOTYPE1(get_symTag, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_symTag(shared_ptr< Base<EncodingT> >& pRetVal);

		// Récupère le nombre de bits ou d'octets de mémoire utilisés par l'objet représenté par ce symbole.
		FACTORY_PROTOTYPE1(get_length, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_length(shared_ptr< Base<EncodingT> >& pRetVal);

		// extrait une balise qui spécifie si un type pointeur est une référence.
		FACTORY_PROTOTYPE1(get_reference, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_reference(shared_ptr< Base<EncodingT> >& pRetVal);

		// Récupère le rang (nombre de dimensions) d'un tableau multidimensionnel FORTRAN.
		FACTORY_PROTOTYPE1(get_rank, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_rank(shared_ptr< Base<EncodingT> >& pRetVal);

		// Extrait la limite inférieure d'une dimension de tableau FORTRAN.
		FACTORY_PROTOTYPE1(get_lowerBound, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_lowerBound(shared_ptr< Base<EncodingT> >& pRetVal);

		// Récupère un symbole représentant la limite supérieure d'une dimension de tableau FORTRAN.
		FACTORY_PROTOTYPE1(get_upperBound, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_upperBound(shared_ptr< Base<EncodingT> >& pRetVal);

		// Récupère la valeur du fabricant d'ordinateurs (OEM) OEM du symbole.
		FACTORY_PROTOTYPE1(get_oemId, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_oemId(shared_ptr< Base<EncodingT> >& pRetVal);

		// Récupère la valeur (OEM) du symbole de fabricant d'ordinateurs OEM.
		FACTORY_PROTOTYPE1(get_oemSymbolId, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_oemSymbolId(shared_ptr< Base<EncodingT> >& pRetVal);

		// Récupère un tableau de types de compilateur-détail pour ce symbole.
		FACTORY_PROTOTYPE1(get_types, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_types(shared_ptr< Base<EncodingT> >& types);

		// Récupère les octets de données d'un symbole OEM.
		FACTORY_PROTOTYPE3(get_dataBytes, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_dataBytes(const shared_ptr< Base<EncodingT> >& cbData, shared_ptr< Base<EncodingT> >& pcbData, shared_ptr< Base<EncodingT> >& data);

		// Extrait le dossier fichiers divers un type défini par l' (UDT)utilisateur.
		FACTORY_PROTOTYPE1(get_udtKind, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_udtKind(shared_ptr< Base<EncodingT> >& pRetVal);

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( IDiaSymbolPtrInterpreter, C("IDiaSymbolPtr") );
			METHOD_KEY_REGISTER4( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, findChildren, no_const_t, C("IDiaSymbolPtr::FindChildren") );
			METHOD_KEY_REGISTER2( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, findChildren, no_const_t, C("IDiaSymbolPtr::FindChildren") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_name, no_const_t, C("IDiaSymbolPtr::Get_name") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_addressSection, no_const_t, C("IDiaSymbolPtr::Get_addressSection") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_addressOffset, no_const_t, C("IDiaSymbolPtr::Get_addressOffset") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_relativeVirtualAddress, no_const_t, C("IDiaSymbolPtr::Get_relativeVirtualAddress") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_type, no_const_t, C("IDiaSymbolPtr::Get_type") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_constType, no_const_t, C("IDiaSymbolPtr::Get_constType") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_dataKind, no_const_t, C("IDiaSymbolPtr::Get_dataKind") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_constructor, no_const_t, C("IDiaSymbolPtr::Get_constructor") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_baseType, no_const_t, C("IDiaSymbolPtr::Get_baseType") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_volatileType, no_const_t, C("IDiaSymbolPtr::Get_volatileType") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_virtual, no_const_t, C("IDiaSymbolPtr::Get_virtual") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_isStatic, no_const_t, C("IDiaSymbolPtr::Get_isStatic") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_isReturnValue, no_const_t, C("IDiaSymbolPtr::Get_isReturnValue") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_symTag, no_const_t, C("IDiaSymbolPtr::Get_symTag") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_length, no_const_t, C("IDiaSymbolPtr::Get_length") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_reference, no_const_t, C("IDiaSymbolPtr::Get_reference") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_rank, no_const_t, C("IDiaSymbolPtr::Get_rank") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_lowerBound, no_const_t, C("IDiaSymbolPtr::Get_lowerBound") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_upperBound, no_const_t, C("IDiaSymbolPtr::Get_upperBound") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_oemId, no_const_t, C("IDiaSymbolPtr::Get_oemId") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_oemSymbolId, no_const_t, C("IDiaSymbolPtr::Get_oemSymbolId") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_types, no_const_t, C("IDiaSymbolPtr::Get_types") );
			METHOD_KEY_REGISTER3( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_dataBytes, no_const_t, C("IDiaSymbolPtr::Get_dataBytes") );
			METHOD_KEY_REGISTER1( IDiaSymbolPtrInterpreter, shared_ptr< Base<EncodingT> >, get_udtKind, no_const_t, C("IDiaSymbolPtr::Get_udtKind") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("IDiaSymbolPtr") );
			METHOD_KEY_UNREGISTER4( C("IDiaSymbolPtr::FindChildren") );
			METHOD_KEY_UNREGISTER2( C("IDiaSymbolPtr::FindChildren") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_name") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_addressSection") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_addressOffset") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_relativeVirtualAddress") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_type") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_constType") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_dataKind") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_constructor") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_baseType") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_volatileType") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_virtual") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_isStatic") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_isReturnValue") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_symTag") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_length") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_reference") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_rank") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_lowerBound") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_upperBound") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_oemId") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_oemSymbolId") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_types") );
			METHOD_KEY_UNREGISTER3( C("IDiaSymbolPtr::Get_dataBytes") );
			METHOD_KEY_UNREGISTER1( C("IDiaSymbolPtr::Get_udtKind") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_IDiaSymbolPtr(shared_ptr< Base<EncodingT> > const& val, IDiaSymbolPtr& a);

	template <class EncodingT>
	bool reset_IDiaSymbolPtr(shared_ptr< Base<EncodingT> >& val, IDiaSymbolPtr const& a);

NAMESPACE_END

#undef A
#undef C
#include "IDiaSymbolPtrInterpreter_impl.hpp"

#endif