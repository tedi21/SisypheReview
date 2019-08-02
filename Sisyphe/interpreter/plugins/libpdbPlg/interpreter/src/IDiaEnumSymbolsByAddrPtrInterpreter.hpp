/*
 * IDiaEnumSymbolsByAddrPtrInterpreter.hpp
 *
 *
 * @date 02-08-2019
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#ifndef _IDIAENUMSYMBOLSBYADDRPTR_INTERPRETER_H_
#define _IDIAENUMSYMBOLSBYADDRPTR_INTERPRETER_H_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include "Array.hpp"
#include "DiaPtr.h"
typedef CDiaPtr<IDiaEnumSymbolsByAddr> IDiaEnumSymbolsByAddrPtr;

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// Classe qui énumère par l'adresse que différents symboles auront contenue dans la source de données.
	template <class EncodingT>
	class IDiaEnumSymbolsByAddrPtrInterpreter
	: public Base<EncodingT>
	{
	private:
		IDiaEnumSymbolsByAddrPtr m_object;

		void initValue(const IDiaEnumSymbolsByAddrPtr& object);

		IDiaEnumSymbolsByAddrPtr& refValue();

		const IDiaEnumSymbolsByAddrPtr& refValue() const;

		void tidyValue();

	public:
		IDiaEnumSymbolsByAddrPtrInterpreter();

		IDiaEnumSymbolsByAddrPtrInterpreter(const IDiaEnumSymbolsByAddrPtr& object);

		const IDiaEnumSymbolsByAddrPtr& value() const;

		void value(IDiaEnumSymbolsByAddrPtr const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

		// Positionne l'énumérateur en effectuant une recherche par le nombre de sections et l'offset d'image.
		FACTORY_PROTOTYPE3(symbolByAddr, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > symbolByAddr(const boost::shared_ptr< Base<EncodingT> >& isect, const boost::shared_ptr< Base<EncodingT> >& offsect, boost::shared_ptr< Base<EncodingT> >& ppsymbol);

		// Positionne l'énumérateur en effectuant une recherche par l'adresse virtuelle associée (RVA).
		FACTORY_PROTOTYPE2(symbolByRVA, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > symbolByRVA(const boost::shared_ptr< Base<EncodingT> >& relativeVirtualAddress, boost::shared_ptr< Base<EncodingT> >& ppsymbol);

		// Récupère les symboles ci-dessous dans l'ordre par l'adresse.
		FACTORY_PROTOTYPE3(next, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > next(const boost::shared_ptr< Base<EncodingT> >& celt, boost::shared_ptr< Base<EncodingT> >& rgelt, boost::shared_ptr< Base<EncodingT> >& pceltFetched);

		// Récupère les symboles précédents dans l'ordre par l'adresse.
		FACTORY_PROTOTYPE3(prev, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > prev(const boost::shared_ptr< Base<EncodingT> >& celt, boost::shared_ptr< Base<EncodingT> >& rgelt, boost::shared_ptr< Base<EncodingT> >& pceltFetched);

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( IDiaEnumSymbolsByAddrPtrInterpreter, UCS("IDiaEnumSymbolsByAddrPtr") );
			METHOD_KEY_REGISTER3( IDiaEnumSymbolsByAddrPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, symbolByAddr, no_const_t, UCS("IDiaEnumSymbolsByAddrPtr::SymbolByAddr") );
			METHOD_KEY_REGISTER2( IDiaEnumSymbolsByAddrPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, symbolByRVA, no_const_t, UCS("IDiaEnumSymbolsByAddrPtr::SymbolByRVA") );
			METHOD_KEY_REGISTER3( IDiaEnumSymbolsByAddrPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, next, no_const_t, UCS("IDiaEnumSymbolsByAddrPtr::Next") );
			METHOD_KEY_REGISTER3( IDiaEnumSymbolsByAddrPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, prev, no_const_t, UCS("IDiaEnumSymbolsByAddrPtr::Prev") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( UCS("IDiaEnumSymbolsByAddrPtr") );
			METHOD_KEY_UNREGISTER3( UCS("IDiaEnumSymbolsByAddrPtr::SymbolByAddr") );
			METHOD_KEY_UNREGISTER2( UCS("IDiaEnumSymbolsByAddrPtr::SymbolByRVA") );
			METHOD_KEY_UNREGISTER3( UCS("IDiaEnumSymbolsByAddrPtr::Next") );
			METHOD_KEY_UNREGISTER3( UCS("IDiaEnumSymbolsByAddrPtr::Prev") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_IDiaEnumSymbolsByAddrPtr(boost::shared_ptr< Base<EncodingT> > const& val, IDiaEnumSymbolsByAddrPtr& a);

	template <class EncodingT>
	bool reset_IDiaEnumSymbolsByAddrPtr(boost::shared_ptr< Base<EncodingT> >& val, IDiaEnumSymbolsByAddrPtr const& a);

NAMESPACE_END

#undef A
#undef C
#include "IDiaEnumSymbolsByAddrPtrInterpreter_impl.hpp"

#endif