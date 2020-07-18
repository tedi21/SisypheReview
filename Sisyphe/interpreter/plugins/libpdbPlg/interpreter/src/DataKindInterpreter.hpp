/*
 * DataKindInterpreter.hpp
 *
 *
 * @date 12-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#ifndef _DATAKIND_INTERPRETER_H_
#define _DATAKIND_INTERPRETER_H_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include "Array.hpp"


#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// indique la portée particulière d'une valeur de données.
	template <class EncodingT>
	class DataKindInterpreter
	: public Base<EncodingT>
	{
	private:

	public:
		DataKindInterpreter();

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

		boost::shared_ptr< Base<EncodingT> > getDataIsUnknown() const;

		boost::shared_ptr< Base<EncodingT> > getDataIsLocal() const;

		boost::shared_ptr< Base<EncodingT> > getDataIsStaticLocal() const;

		boost::shared_ptr< Base<EncodingT> > getDataIsParam() const;

		boost::shared_ptr< Base<EncodingT> > getDataIsObjectPtr() const;

		boost::shared_ptr< Base<EncodingT> > getDataIsFileStatic() const;

		boost::shared_ptr< Base<EncodingT> > getDataIsGlobal() const;

		boost::shared_ptr< Base<EncodingT> > getDataIsMember() const;

		boost::shared_ptr< Base<EncodingT> > getDataIsStaticMember() const;

		boost::shared_ptr< Base<EncodingT> > getDataIsConstant() const;

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( DataKindInterpreter, UCS("DataKind") );
			METHOD_KEY_REGISTER ( DataKindInterpreter, boost::shared_ptr< Base<EncodingT> >, getDataIsUnknown, const_t, UCS("DataKind::DataIsUnknown") );
			METHOD_KEY_REGISTER ( DataKindInterpreter, boost::shared_ptr< Base<EncodingT> >, getDataIsLocal, const_t, UCS("DataKind::DataIsLocal") );
			METHOD_KEY_REGISTER ( DataKindInterpreter, boost::shared_ptr< Base<EncodingT> >, getDataIsStaticLocal, const_t, UCS("DataKind::DataIsStaticLocal") );
			METHOD_KEY_REGISTER ( DataKindInterpreter, boost::shared_ptr< Base<EncodingT> >, getDataIsParam, const_t, UCS("DataKind::DataIsParam") );
			METHOD_KEY_REGISTER ( DataKindInterpreter, boost::shared_ptr< Base<EncodingT> >, getDataIsObjectPtr, const_t, UCS("DataKind::DataIsObjectPtr") );
			METHOD_KEY_REGISTER ( DataKindInterpreter, boost::shared_ptr< Base<EncodingT> >, getDataIsFileStatic, const_t, UCS("DataKind::DataIsFileStatic") );
			METHOD_KEY_REGISTER ( DataKindInterpreter, boost::shared_ptr< Base<EncodingT> >, getDataIsGlobal, const_t, UCS("DataKind::DataIsGlobal") );
			METHOD_KEY_REGISTER ( DataKindInterpreter, boost::shared_ptr< Base<EncodingT> >, getDataIsMember, const_t, UCS("DataKind::DataIsMember") );
			METHOD_KEY_REGISTER ( DataKindInterpreter, boost::shared_ptr< Base<EncodingT> >, getDataIsStaticMember, const_t, UCS("DataKind::DataIsStaticMember") );
			METHOD_KEY_REGISTER ( DataKindInterpreter, boost::shared_ptr< Base<EncodingT> >, getDataIsConstant, const_t, UCS("DataKind::DataIsConstant") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( UCS("DataKind") );
			METHOD_KEY_UNREGISTER ( UCS("DataKind::DataIsUnknown") );
			METHOD_KEY_UNREGISTER ( UCS("DataKind::DataIsLocal") );
			METHOD_KEY_UNREGISTER ( UCS("DataKind::DataIsStaticLocal") );
			METHOD_KEY_UNREGISTER ( UCS("DataKind::DataIsParam") );
			METHOD_KEY_UNREGISTER ( UCS("DataKind::DataIsObjectPtr") );
			METHOD_KEY_UNREGISTER ( UCS("DataKind::DataIsFileStatic") );
			METHOD_KEY_UNREGISTER ( UCS("DataKind::DataIsGlobal") );
			METHOD_KEY_UNREGISTER ( UCS("DataKind::DataIsMember") );
			METHOD_KEY_UNREGISTER ( UCS("DataKind::DataIsStaticMember") );
			METHOD_KEY_UNREGISTER ( UCS("DataKind::DataIsConstant") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "DataKindInterpreter_impl.hpp"

#endif