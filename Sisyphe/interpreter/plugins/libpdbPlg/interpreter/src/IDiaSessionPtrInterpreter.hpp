/*
 * IDiaSessionPtrInterpreter.hpp
 *
 *
 * @date 21-06-2016
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#ifndef _IDIASESSIONPTR_INTERPRETER_H_
#define _IDIASESSIONPTR_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "Array.hpp"
#include "DiaPtr.h"
typedef CDiaPtr<IDiaSession> IDiaSessionPtr;
#include "IDiaSymbolPtrInterpreter.hpp"
#include "IDiaEnumLineNumbersPtrInterpreter.hpp"
#include "IDiaEnumSourceFilesPtrInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// Classe permettant de fournir un contexte de requête pour des symboles de débogage.
	template <class EncodingT>
	class IDiaSessionPtrInterpreter
	: public Base<EncodingT>
	{
	private:
		IDiaSessionPtr m_object;

		void initValue(const IDiaSessionPtr& object);

		IDiaSessionPtr& value();

		const IDiaSessionPtr& value() const;

		void tidyValue();

	public:
		IDiaSessionPtrInterpreter();

		~IDiaSessionPtrInterpreter();

		IDiaSessionPtrInterpreter(const IDiaSessionPtr& object);

		IDiaSessionPtrInterpreter(const IDiaSessionPtrInterpreter<EncodingT>& rhs);

		IDiaSessionPtrInterpreter<EncodingT>& operator=(const IDiaSessionPtrInterpreter<EncodingT>& rhs);

		const IDiaSessionPtr& getValue() const;

		void setValue(IDiaSessionPtr const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);

		// Extrait une référence de la portée globale.
		FACTORY_PROTOTYPE1(get_globalScope, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_globalScope(shared_ptr< Base<EncodingT> >& pRetVal);

		// Définit l'adresse de charge du fichier exécutable qui correspond aux symboles dans ce magasin de symboles.
		FACTORY_PROTOTYPE1(put_loadAddress, In< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > put_loadAddress(const shared_ptr< Base<EncodingT> >& pNewVal);

		// Récupère les lignes d'un module spécifié qui contient une adresse virtuelle relative spécifiée (RVA).
		FACTORY_PROTOTYPE3(findLinesByRVA, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > findLinesByRVA(const shared_ptr< Base<EncodingT> >& rva, const shared_ptr< Base<EncodingT> >& length, shared_ptr< Base<EncodingT> >& ppResult);

		// Détermine les numéros de ligne du module (compiland) que le numéro de ligne spécifié dans un fichier source se trouve dans ou approche.
		FACTORY_PROTOTYPE5(findLinesByLinenum, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > findLinesByLinenum(const shared_ptr< Base<EncodingT> >& compiland, const shared_ptr< Base<EncodingT> >& file, const shared_ptr< Base<EncodingT> >& linenum, const shared_ptr< Base<EncodingT> >& column, shared_ptr< Base<EncodingT> >& ppResult);

		// Récupère les numéros de ligne dans les ID spécifiés de module (compiland) et du fichier source.
		FACTORY_PROTOTYPE3(findLines, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > findLines(const shared_ptr< Base<EncodingT> >& compiland, const shared_ptr< Base<EncodingT> >& file, shared_ptr< Base<EncodingT> >& ppResult);

		// Récupère les fichiers sources par le module et le nom.
		FACTORY_PROTOTYPE4(findFile, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > findFile(const shared_ptr< Base<EncodingT> >& pCompiland, const shared_ptr< Base<EncodingT> >& name, const shared_ptr< Base<EncodingT> >& option, shared_ptr< Base<EncodingT> >& ppResult);

		// Récupère les fichiers sources par le module.
		FACTORY_PROTOTYPE2(findFile, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > findFile(const shared_ptr< Base<EncodingT> >& pCompiland, shared_ptr< Base<EncodingT> >& ppResult);

		// Récupère les fichiers sources par le nom.
		FACTORY_PROTOTYPE3(findFile, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > findFile(const shared_ptr< Base<EncodingT> >& name, const shared_ptr< Base<EncodingT> >& option, shared_ptr< Base<EncodingT> >& ppResult);

		// Récupère tous les fichiers sources.
		FACTORY_PROTOTYPE1(findFile, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > findFile(shared_ptr< Base<EncodingT> >& ppResult);

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( IDiaSessionPtrInterpreter, C("IDiaSessionPtr") );
			METHOD_KEY_REGISTER1( IDiaSessionPtrInterpreter, shared_ptr< Base<EncodingT> >, get_globalScope, no_const_t, C("IDiaSessionPtr::Get_globalScope") );
			METHOD_KEY_REGISTER1( IDiaSessionPtrInterpreter, shared_ptr< Base<EncodingT> >, put_loadAddress, no_const_t, C("IDiaSessionPtr::Put_loadAddress") );
			METHOD_KEY_REGISTER3( IDiaSessionPtrInterpreter, shared_ptr< Base<EncodingT> >, findLinesByRVA, no_const_t, C("IDiaSessionPtr::FindLinesByRVA") );
			METHOD_KEY_REGISTER5( IDiaSessionPtrInterpreter, shared_ptr< Base<EncodingT> >, findLinesByLinenum, no_const_t, C("IDiaSessionPtr::FindLinesByLinenum") );
			METHOD_KEY_REGISTER3( IDiaSessionPtrInterpreter, shared_ptr< Base<EncodingT> >, findLines, no_const_t, C("IDiaSessionPtr::FindLines") );
			METHOD_KEY_REGISTER4( IDiaSessionPtrInterpreter, shared_ptr< Base<EncodingT> >, findFile, no_const_t, C("IDiaSessionPtr::FindFile") );
			METHOD_KEY_REGISTER2( IDiaSessionPtrInterpreter, shared_ptr< Base<EncodingT> >, findFile, no_const_t, C("IDiaSessionPtr::FindFile") );
			METHOD_KEY_REGISTER3( IDiaSessionPtrInterpreter, shared_ptr< Base<EncodingT> >, findFile, no_const_t, C("IDiaSessionPtr::FindFile") );
			METHOD_KEY_REGISTER1( IDiaSessionPtrInterpreter, shared_ptr< Base<EncodingT> >, findFile, no_const_t, C("IDiaSessionPtr::FindFile") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("IDiaSessionPtr") );
			METHOD_KEY_UNREGISTER1( C("IDiaSessionPtr::Get_globalScope") );
			METHOD_KEY_UNREGISTER1( C("IDiaSessionPtr::Put_loadAddress") );
			METHOD_KEY_UNREGISTER3( C("IDiaSessionPtr::FindLinesByRVA") );
			METHOD_KEY_UNREGISTER5( C("IDiaSessionPtr::FindLinesByLinenum") );
			METHOD_KEY_UNREGISTER3( C("IDiaSessionPtr::FindLines") );
			METHOD_KEY_UNREGISTER4( C("IDiaSessionPtr::FindFile") );
			METHOD_KEY_UNREGISTER2( C("IDiaSessionPtr::FindFile") );
			METHOD_KEY_UNREGISTER3( C("IDiaSessionPtr::FindFile") );
			METHOD_KEY_UNREGISTER1( C("IDiaSessionPtr::FindFile") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_IDiaSessionPtr(shared_ptr< Base<EncodingT> > const& val, IDiaSessionPtr& a);

	template <class EncodingT>
	bool reset_IDiaSessionPtr(shared_ptr< Base<EncodingT> >& val, IDiaSessionPtr const& a);

NAMESPACE_END

#undef A
#undef C
#include "IDiaSessionPtrInterpreter_impl.hpp"

#endif