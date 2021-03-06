/*
 * IDiaEnumTablesPtrInterpreter.hpp
 *
 *
 * @date 12-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#ifndef _IDIAENUMTABLESPTR_INTERPRETER_H_
#define _IDIAENUMTABLESPTR_INTERPRETER_H_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include "Array.hpp"
#include "DiaPtr.h"
typedef CDiaPtr<IDiaEnumTables> IDiaEnumTablesPtr;
#include "IDiaTablePtrInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// Classe qui énumère les différents tables contenues dans la source de données.
	template <class EncodingT>
	class IDiaEnumTablesPtrInterpreter
	: public Base<EncodingT>
	{
	private:
		IDiaEnumTablesPtr m_object;

		void initValue(const IDiaEnumTablesPtr& object);

		IDiaEnumTablesPtr& refValue();

		const IDiaEnumTablesPtr& refValue() const;

		void tidyValue();

	public:
		IDiaEnumTablesPtrInterpreter();

		IDiaEnumTablesPtrInterpreter(const IDiaEnumTablesPtr& object);

		const IDiaEnumTablesPtr& value() const;

		void value(IDiaEnumTablesPtr const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

		// Récupère le nombre de tables.
		FACTORY_PROTOTYPE1(get_Count, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > get_Count(boost::shared_ptr< Base<EncodingT> >& pRetVal);

		// Récupère une table à l'aide d'un index ou d'une étiquette.
		FACTORY_PROTOTYPE2(itemByIndex, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > itemByIndex(const boost::shared_ptr< Base<EncodingT> >& index, boost::shared_ptr< Base<EncodingT> >& table);

		FACTORY_PROTOTYPE2(itemByName, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > itemByName(const boost::shared_ptr< Base<EncodingT> >& label, boost::shared_ptr< Base<EncodingT> >& table);

		// Récupère un nombre spécifié de tables dans la séquence d'énumération.
		FACTORY_PROTOTYPE3(next, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > next(const boost::shared_ptr< Base<EncodingT> >& celt, boost::shared_ptr< Base<EncodingT> >& rgelt, boost::shared_ptr< Base<EncodingT> >& pceltFetched);

		// Ignore un nombre spécifié de tables dans une séquence d'énumération.
		FACTORY_PROTOTYPE1(skip, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > skip(const boost::shared_ptr< Base<EncodingT> >& celt);

		// Réinitialise une séquence d'énumération au début.
		boost::shared_ptr< Base<EncodingT> > reset();

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( IDiaEnumTablesPtrInterpreter, UCS("IDiaEnumTablesPtr") );
			METHOD_KEY_REGISTER1( IDiaEnumTablesPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, get_Count, no_const_t, UCS("IDiaEnumTablesPtr::Get_Count") );
			METHOD_KEY_REGISTER2( IDiaEnumTablesPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, itemByIndex, no_const_t, UCS("IDiaEnumTablesPtr::ItemByIndex") );
			METHOD_KEY_REGISTER2( IDiaEnumTablesPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, itemByName, no_const_t, UCS("IDiaEnumTablesPtr::ItemByName") );
			METHOD_KEY_REGISTER3( IDiaEnumTablesPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, next, no_const_t, UCS("IDiaEnumTablesPtr::Next") );
			METHOD_KEY_REGISTER1( IDiaEnumTablesPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, skip, no_const_t, UCS("IDiaEnumTablesPtr::Skip") );
			METHOD_KEY_REGISTER ( IDiaEnumTablesPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, reset, no_const_t, UCS("IDiaEnumTablesPtr::Reset") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( UCS("IDiaEnumTablesPtr") );
			METHOD_KEY_UNREGISTER1( UCS("IDiaEnumTablesPtr::Get_Count") );
			METHOD_KEY_UNREGISTER2( UCS("IDiaEnumTablesPtr::ItemByIndex") );
			METHOD_KEY_UNREGISTER2( UCS("IDiaEnumTablesPtr::ItemByName") );
			METHOD_KEY_UNREGISTER3( UCS("IDiaEnumTablesPtr::Next") );
			METHOD_KEY_UNREGISTER1( UCS("IDiaEnumTablesPtr::Skip") );
			METHOD_KEY_UNREGISTER ( UCS("IDiaEnumTablesPtr::Reset") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_IDiaEnumTablesPtr(boost::shared_ptr< Base<EncodingT> > const& val, IDiaEnumTablesPtr& a);

	template <class EncodingT>
	bool reset_IDiaEnumTablesPtr(boost::shared_ptr< Base<EncodingT> >& val, IDiaEnumTablesPtr const& a);

NAMESPACE_END

#undef A
#undef C
#include "IDiaEnumTablesPtrInterpreter_impl.hpp"

#endif