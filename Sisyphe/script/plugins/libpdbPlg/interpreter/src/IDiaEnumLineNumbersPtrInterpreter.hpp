/*
 * IDiaEnumLineNumbersPtrInterpreter.hpp
 *
 *
 * @date 21-06-2016
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#ifndef _IDIAENUMLINENUMBERSPTR_INTERPRETER_H_
#define _IDIAENUMLINENUMBERSPTR_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "Array.hpp"
#include "DiaPtr.h"
typedef CDiaPtr<IDiaEnumLineNumbers> IDiaEnumLineNumbersPtr;
#include "IDiaLineNumberPtrInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// Classe qui énumère les différents numéros de ligne contenus dans la source de données.
	template <class EncodingT>
	class IDiaEnumLineNumbersPtrInterpreter
	: public Base<EncodingT>
	{
	private:
		IDiaEnumLineNumbersPtr m_object;

		void initValue(const IDiaEnumLineNumbersPtr& object);

		IDiaEnumLineNumbersPtr& value();

		const IDiaEnumLineNumbersPtr& value() const;

		void tidyValue();

	public:
		IDiaEnumLineNumbersPtrInterpreter();

		~IDiaEnumLineNumbersPtrInterpreter();

		IDiaEnumLineNumbersPtrInterpreter(const IDiaEnumLineNumbersPtr& object);

		IDiaEnumLineNumbersPtrInterpreter(const IDiaEnumLineNumbersPtrInterpreter<EncodingT>& rhs);

		IDiaEnumLineNumbersPtrInterpreter<EncodingT>& operator=(const IDiaEnumLineNumbersPtrInterpreter<EncodingT>& rhs);

		const IDiaEnumLineNumbersPtr& getValue() const;

		void setValue(IDiaEnumLineNumbersPtr const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);

		// Récupère le nombre de symboles.
		FACTORY_PROTOTYPE1(get_Count, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > get_Count(shared_ptr< Base<EncodingT> >& pRetVal);

		// Récupère un symbole au moyen d'un index.
		FACTORY_PROTOTYPE2(item, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > item(const shared_ptr< Base<EncodingT> >& index, shared_ptr< Base<EncodingT> >& symbol);

		// Récupère un nombre spécifié de symboles dans la séquence d'énumération.
		FACTORY_PROTOTYPE3(next, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > next(const shared_ptr< Base<EncodingT> >& celt, shared_ptr< Base<EncodingT> >& rgelt, shared_ptr< Base<EncodingT> >& pceltFetched);

		// Ignore un nombre spécifié de symboles dans une séquence d'énumération.
		FACTORY_PROTOTYPE1(skip, In< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > skip(const shared_ptr< Base<EncodingT> >& celt);

		// Réinitialise une séquence d'énumération au début.
		shared_ptr< Base<EncodingT> > reset();

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( IDiaEnumLineNumbersPtrInterpreter, C("IDiaEnumLineNumbersPtr") );
			METHOD_KEY_REGISTER1( IDiaEnumLineNumbersPtrInterpreter, shared_ptr< Base<EncodingT> >, get_Count, no_const_t, C("IDiaEnumLineNumbersPtr::Get_Count") );
			METHOD_KEY_REGISTER2( IDiaEnumLineNumbersPtrInterpreter, shared_ptr< Base<EncodingT> >, item, no_const_t, C("IDiaEnumLineNumbersPtr::Item") );
			METHOD_KEY_REGISTER3( IDiaEnumLineNumbersPtrInterpreter, shared_ptr< Base<EncodingT> >, next, no_const_t, C("IDiaEnumLineNumbersPtr::Next") );
			METHOD_KEY_REGISTER1( IDiaEnumLineNumbersPtrInterpreter, shared_ptr< Base<EncodingT> >, skip, no_const_t, C("IDiaEnumLineNumbersPtr::Skip") );
			METHOD_KEY_REGISTER ( IDiaEnumLineNumbersPtrInterpreter, shared_ptr< Base<EncodingT> >, reset, no_const_t, C("IDiaEnumLineNumbersPtr::Reset") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("IDiaEnumLineNumbersPtr") );
			METHOD_KEY_UNREGISTER1( C("IDiaEnumLineNumbersPtr::Get_Count") );
			METHOD_KEY_UNREGISTER2( C("IDiaEnumLineNumbersPtr::Item") );
			METHOD_KEY_UNREGISTER3( C("IDiaEnumLineNumbersPtr::Next") );
			METHOD_KEY_UNREGISTER1( C("IDiaEnumLineNumbersPtr::Skip") );
			METHOD_KEY_UNREGISTER ( C("IDiaEnumLineNumbersPtr::Reset") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_IDiaEnumLineNumbersPtr(shared_ptr< Base<EncodingT> > const& val, IDiaEnumLineNumbersPtr& a);

	template <class EncodingT>
	bool reset_IDiaEnumLineNumbersPtr(shared_ptr< Base<EncodingT> >& val, IDiaEnumLineNumbersPtr const& a);

NAMESPACE_END

#undef A
#undef C
#include "IDiaEnumLineNumbersPtrInterpreter_impl.hpp"

#endif