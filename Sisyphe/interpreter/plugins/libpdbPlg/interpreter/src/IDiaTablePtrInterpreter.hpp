/*
 * IDiaTablePtrInterpreter.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#ifndef _IDIATABLEPTR_INTERPRETER_H_
#define _IDIATABLEPTR_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "Base.hpp"
#include "Array.hpp"
#include "DiaPtr.h"
typedef CDiaPtr<IDiaTable> IDiaTablePtr;

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// Énumère une table de source de données de diamètre.
	template <class EncodingT>
	class IDiaTablePtrInterpreter
	: public Base<EncodingT>
	{
	private:
		IDiaTablePtr m_object;

		void initValue(const IDiaTablePtr& object);

		IDiaTablePtr& refValue();

		const IDiaTablePtr& refValue() const;

		void tidyValue();

	public:
		IDiaTablePtrInterpreter();

		~IDiaTablePtrInterpreter();

		IDiaTablePtrInterpreter(const IDiaTablePtr& object);

		IDiaTablePtrInterpreter(const IDiaTablePtrInterpreter<EncodingT>& rhs);

		IDiaTablePtrInterpreter<EncodingT>& operator=(const IDiaTablePtrInterpreter<EncodingT>& rhs);

		const IDiaTablePtr& value() const;

		void value(IDiaTablePtr const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

		// Extrait le nom de la table.
		FACTORY_PROTOTYPE1(get_name, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > get_name(boost::shared_ptr< Base<EncodingT> >& pRetVal);

		// Récupère le nombre de fichiers sources.
		FACTORY_PROTOTYPE1(get_Count, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > get_Count(boost::shared_ptr< Base<EncodingT> >& pRetVal);

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( IDiaTablePtrInterpreter, C("IDiaTablePtr") );
			METHOD_KEY_REGISTER1( IDiaTablePtrInterpreter, boost::shared_ptr< Base<EncodingT> >, get_name, no_const_t, C("IDiaTablePtr::Get_name") );
			METHOD_KEY_REGISTER1( IDiaTablePtrInterpreter, boost::shared_ptr< Base<EncodingT> >, get_Count, no_const_t, C("IDiaTablePtr::Get_Count") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("IDiaTablePtr") );
			METHOD_KEY_UNREGISTER1( C("IDiaTablePtr::Get_name") );
			METHOD_KEY_UNREGISTER1( C("IDiaTablePtr::Get_Count") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_IDiaTablePtr(boost::shared_ptr< Base<EncodingT> > const& val, IDiaTablePtr& a);

	template <class EncodingT>
	bool reset_IDiaTablePtr(boost::shared_ptr< Base<EncodingT> >& val, IDiaTablePtr const& a);

NAMESPACE_END

#undef A
#undef C
#include "IDiaTablePtrInterpreter_impl.hpp"

#endif