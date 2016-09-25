/*
 * SymTagEnumTypeInterpreter.hpp
 *
 *
 * @date 03-09-2016
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#ifndef _SYMTAGENUMTYPE_INTERPRETER_H_
#define _SYMTAGENUMTYPE_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "Array.hpp"
typedef enum SymTagEnum SymTagEnumType;

NAMESPACE_BEGIN(interp)

template <class EncodingT>
bool check_SymTagEnumType(boost::shared_ptr< Base<EncodingT> > const& val, SymTagEnumType& s);

NAMESPACE_END

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// Spécifie le type de symbole.
	template <class EncodingT>
	class SymTagEnumTypeInterpreter
	: public Base<EncodingT>
	{
	private:

		void tidyValue();

	public:
		SymTagEnumTypeInterpreter();

		~SymTagEnumTypeInterpreter();

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

		boost::shared_ptr< Base<EncodingT> > getSymTagNull() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagExe() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagCompiland() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagCompilandDetails() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagCompilandEnv() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagFunction() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagBlock() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagData() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagAnnotation() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagLabel() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagPublicSymbol() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagUDT() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagEnum() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagFunctionType() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagPointerType() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagArrayType() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagBaseType() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagTypedef() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagBaseClass() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagFriend() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagFunctionArgType() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagFuncDebugStart() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagFuncDebugEnd() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagUsingNamespace() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagVTableShape() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagVTable() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagCustom() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagThunk() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagCustomType() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagManagedType() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagDimension() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagCallSite() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagInlineSite() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagBaseInterface() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagVectorType() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagMatrixType() const;

		boost::shared_ptr< Base<EncodingT> > getSymTagHLSLType() const;

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( SymTagEnumTypeInterpreter, C("SymTagEnumType") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagNull, const_t, C("SymTagEnumType::SymTagNull") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagExe, const_t, C("SymTagEnumType::SymTagExe") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagCompiland, const_t, C("SymTagEnumType::SymTagCompiland") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagCompilandDetails, const_t, C("SymTagEnumType::SymTagCompilandDetails") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagCompilandEnv, const_t, C("SymTagEnumType::SymTagCompilandEnv") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagFunction, const_t, C("SymTagEnumType::SymTagFunction") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagBlock, const_t, C("SymTagEnumType::SymTagBlock") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagData, const_t, C("SymTagEnumType::SymTagData") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagAnnotation, const_t, C("SymTagEnumType::SymTagAnnotation") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagLabel, const_t, C("SymTagEnumType::SymTagLabel") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagPublicSymbol, const_t, C("SymTagEnumType::SymTagPublicSymbol") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagUDT, const_t, C("SymTagEnumType::SymTagUDT") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagEnum, const_t, C("SymTagEnumType::SymTagEnum") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagFunctionType, const_t, C("SymTagEnumType::SymTagFunctionType") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagPointerType, const_t, C("SymTagEnumType::SymTagPointerType") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagArrayType, const_t, C("SymTagEnumType::SymTagArrayType") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagBaseType, const_t, C("SymTagEnumType::SymTagBaseType") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagTypedef, const_t, C("SymTagEnumType::SymTagTypedef") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagBaseClass, const_t, C("SymTagEnumType::SymTagBaseClass") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagFriend, const_t, C("SymTagEnumType::SymTagFriend") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagFunctionArgType, const_t, C("SymTagEnumType::SymTagFunctionArgType") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagFuncDebugStart, const_t, C("SymTagEnumType::SymTagFuncDebugStart") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagFuncDebugEnd, const_t, C("SymTagEnumType::SymTagFuncDebugEnd") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagUsingNamespace, const_t, C("SymTagEnumType::SymTagUsingNamespace") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagVTableShape, const_t, C("SymTagEnumType::SymTagVTableShape") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagVTable, const_t, C("SymTagEnumType::SymTagVTable") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagCustom, const_t, C("SymTagEnumType::SymTagCustom") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagThunk, const_t, C("SymTagEnumType::SymTagThunk") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagCustomType, const_t, C("SymTagEnumType::SymTagCustomType") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagManagedType, const_t, C("SymTagEnumType::SymTagManagedType") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagDimension, const_t, C("SymTagEnumType::SymTagDimension") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagCallSite, const_t, C("SymTagEnumType::SymTagCallSite") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagInlineSite, const_t, C("SymTagEnumType::SymTagInlineSite") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagBaseInterface, const_t, C("SymTagEnumType::SymTagBaseInterface") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagVectorType, const_t, C("SymTagEnumType::SymTagVectorType") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagMatrixType, const_t, C("SymTagEnumType::SymTagMatrixType") );
			METHOD_KEY_REGISTER ( SymTagEnumTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSymTagHLSLType, const_t, C("SymTagEnumType::SymTagHLSLType") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("SymTagEnumType") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagNull") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagExe") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagCompiland") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagCompilandDetails") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagCompilandEnv") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagFunction") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagBlock") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagData") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagAnnotation") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagLabel") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagPublicSymbol") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagUDT") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagEnum") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagFunctionType") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagPointerType") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagArrayType") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagBaseType") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagTypedef") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagBaseClass") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagFriend") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagFunctionArgType") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagFuncDebugStart") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagFuncDebugEnd") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagUsingNamespace") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagVTableShape") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagVTable") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagCustom") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagThunk") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagCustomType") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagManagedType") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagDimension") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagCallSite") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagInlineSite") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagBaseInterface") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagVectorType") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagMatrixType") );
			METHOD_KEY_UNREGISTER ( C("SymTagEnumType::SymTagHLSLType") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "SymTagEnumTypeInterpreter_impl.hpp"

#endif