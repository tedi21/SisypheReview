/* 
 * debugTypeInfoInterpreter.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGTYPEINFO_INTERPRETER_HPP_
#define _DEBUGTYPEINFO_INTERPRETER_HPP_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include "Array.hpp"

#include "cppBaseExport.hpp"
#include "cppBaseData.h"
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace entity;
using namespace boost;

template <class EncodingT>
class DebugTypeInfoInterpreter;

template <class EncodingT>
class DebugFunctionInfoInterpreter;

template <class EncodingT>
class DebugVariableInfoInterpreter;

template <class EncodingT>
class DebugTypeInfoInterpreter;

template <class EncodingT>
class DebugTypeInfoInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _DebugTypeInfo<EncodingT> > m_value;

public:
	DebugTypeInfoInterpreter();

	DebugTypeInfoInterpreter(boost::shared_ptr< _DebugTypeInfo<EncodingT> > const& value);

	FACTORY_PROTOTYPE22(DebugTypeInfoInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	DebugTypeInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& isChar,
				boost::shared_ptr< Base<EncodingT> > const& isString,
				boost::shared_ptr< Base<EncodingT> > const& isBool,
				boost::shared_ptr< Base<EncodingT> > const& isFloat,
				boost::shared_ptr< Base<EncodingT> > const& isSigned,
				boost::shared_ptr< Base<EncodingT> > const& isWide,
				boost::shared_ptr< Base<EncodingT> > const& isPointer,
				boost::shared_ptr< Base<EncodingT> > const& isReference,
				boost::shared_ptr< Base<EncodingT> > const& isArray,
				boost::shared_ptr< Base<EncodingT> > const& isConst,
				boost::shared_ptr< Base<EncodingT> > const& isVolatile,
				boost::shared_ptr< Base<EncodingT> > const& isStruct,
				boost::shared_ptr< Base<EncodingT> > const& isClass,
				boost::shared_ptr< Base<EncodingT> > const& isUnion,
				boost::shared_ptr< Base<EncodingT> > const& isInterface,
				boost::shared_ptr< Base<EncodingT> > const& isEnum,
				boost::shared_ptr< Base<EncodingT> > const& isFunction,
				boost::shared_ptr< Base<EncodingT> > const& baseName,
				boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& sizeOf,
				boost::shared_ptr< Base<EncodingT> > const& typeId,
				boost::shared_ptr< Base<EncodingT> > const& arrayDim);

	boost::shared_ptr< _DebugTypeInfo<EncodingT> > value() const;

	void value(boost::shared_ptr< _DebugTypeInfo<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getIsChar() const;

	boost::shared_ptr< Base<EncodingT> > getIsString() const;

	boost::shared_ptr< Base<EncodingT> > getIsBool() const;

	boost::shared_ptr< Base<EncodingT> > getIsFloat() const;

	boost::shared_ptr< Base<EncodingT> > getIsSigned() const;

	boost::shared_ptr< Base<EncodingT> > getIsWide() const;

	boost::shared_ptr< Base<EncodingT> > getIsPointer() const;

	boost::shared_ptr< Base<EncodingT> > getIsReference() const;

	boost::shared_ptr< Base<EncodingT> > getIsArray() const;

	boost::shared_ptr< Base<EncodingT> > getIsConst() const;

	boost::shared_ptr< Base<EncodingT> > getIsVolatile() const;

	boost::shared_ptr< Base<EncodingT> > getIsStruct() const;

	boost::shared_ptr< Base<EncodingT> > getIsClass() const;

	boost::shared_ptr< Base<EncodingT> > getIsUnion() const;

	boost::shared_ptr< Base<EncodingT> > getIsInterface() const;

	boost::shared_ptr< Base<EncodingT> > getIsEnum() const;

	boost::shared_ptr< Base<EncodingT> > getIsFunction() const;

	boost::shared_ptr< Base<EncodingT> > getBaseName() const;

	boost::shared_ptr< Base<EncodingT> > getName() const;

	boost::shared_ptr< Base<EncodingT> > getSizeOf() const;

	boost::shared_ptr< Base<EncodingT> > getTypeId() const;

	boost::shared_ptr< Base<EncodingT> > getArrayDim() const;

	boost::shared_ptr< Base<EncodingT> > getPrimitiveType();

	FACTORY_PROTOTYPE1(setPrimitiveType, In< boost::shared_ptr< Base<EncodingT> > >)
	void setPrimitiveType(boost::shared_ptr< Base<EncodingT> > const& primitiveType);

	FACTORY_PROTOTYPE1(setIsChar, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsChar(boost::shared_ptr< Base<EncodingT> > const& isChar);

	FACTORY_PROTOTYPE1(setIsString, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsString(boost::shared_ptr< Base<EncodingT> > const& isString);

	FACTORY_PROTOTYPE1(setIsBool, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsBool(boost::shared_ptr< Base<EncodingT> > const& isBool);

	FACTORY_PROTOTYPE1(setIsFloat, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsFloat(boost::shared_ptr< Base<EncodingT> > const& isFloat);

	FACTORY_PROTOTYPE1(setIsSigned, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsSigned(boost::shared_ptr< Base<EncodingT> > const& isSigned);

	FACTORY_PROTOTYPE1(setIsWide, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsWide(boost::shared_ptr< Base<EncodingT> > const& isWide);

	FACTORY_PROTOTYPE1(setIsPointer, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsPointer(boost::shared_ptr< Base<EncodingT> > const& isPointer);

	FACTORY_PROTOTYPE1(setIsReference, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsReference(boost::shared_ptr< Base<EncodingT> > const& isReference);

	FACTORY_PROTOTYPE1(setIsArray, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsArray(boost::shared_ptr< Base<EncodingT> > const& isArray);

	FACTORY_PROTOTYPE1(setIsConst, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst);

	FACTORY_PROTOTYPE1(setIsVolatile, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsVolatile(boost::shared_ptr< Base<EncodingT> > const& isVolatile);

	FACTORY_PROTOTYPE1(setIsStruct, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsStruct(boost::shared_ptr< Base<EncodingT> > const& isStruct);

	FACTORY_PROTOTYPE1(setIsClass, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsClass(boost::shared_ptr< Base<EncodingT> > const& isClass);

	FACTORY_PROTOTYPE1(setIsUnion, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsUnion(boost::shared_ptr< Base<EncodingT> > const& isUnion);

	FACTORY_PROTOTYPE1(setIsInterface, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsInterface(boost::shared_ptr< Base<EncodingT> > const& isInterface);

	FACTORY_PROTOTYPE1(setIsEnum, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsEnum(boost::shared_ptr< Base<EncodingT> > const& isEnum);

	FACTORY_PROTOTYPE1(setIsFunction, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsFunction(boost::shared_ptr< Base<EncodingT> > const& isFunction);

	FACTORY_PROTOTYPE1(setBaseName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setBaseName(boost::shared_ptr< Base<EncodingT> > const& baseName);

	FACTORY_PROTOTYPE1(setName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setName(boost::shared_ptr< Base<EncodingT> > const& name);

	FACTORY_PROTOTYPE1(setSizeOf, In< boost::shared_ptr< Base<EncodingT> > >)
	void setSizeOf(boost::shared_ptr< Base<EncodingT> > const& sizeOf);

	FACTORY_PROTOTYPE1(setTypeId, In< boost::shared_ptr< Base<EncodingT> > >)
	void setTypeId(boost::shared_ptr< Base<EncodingT> > const& typeId);

	FACTORY_PROTOTYPE1(setArrayDim, In< boost::shared_ptr< Base<EncodingT> > >)
	void setArrayDim(boost::shared_ptr< Base<EncodingT> > const& arrayDim);

	boost::shared_ptr< Base<EncodingT> > hasPrimitiveType() const;

	void removePrimitiveType();

	FACTORY_PROTOTYPE1(removeRichType, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeRichType(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(removeDebugFunctionInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(removeDebugVariableInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE2(insertRichType, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertRichType(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& richType);

	FACTORY_PROTOTYPE2(insertDebugFunctionInfo, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugFunctionInfo);

	FACTORY_PROTOTYPE2(insertDebugVariableInfo, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugVariableInfo);

	FACTORY_PROTOTYPE1(getRichType, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getRichType(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(getDebugFunctionInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(getDebugVariableInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	void clearRichTypes();

	void clearDebugFunctionInfos();

	void clearDebugVariableInfos();

	boost::shared_ptr< Base<EncodingT> > hasRichTypes() const;

	boost::shared_ptr< Base<EncodingT> > hasDebugFunctionInfos() const;

	boost::shared_ptr< Base<EncodingT> > hasDebugVariableInfos() const;

	boost::shared_ptr< Base<EncodingT> > richTypesCount() const;

	boost::shared_ptr< Base<EncodingT> > debugFunctionInfosCount() const;

	boost::shared_ptr< Base<EncodingT> > debugVariableInfosCount() const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( DebugTypeInfoInterpreter, UCS("DebugTypeInfo") );
		CLASS_KEY_REGISTER22( DebugTypeInfoInterpreter, UCS("DebugTypeInfo") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setPrimitiveType, no_const_t, UCS("DebugTypeInfo::PrimitiveType") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getPrimitiveType, no_const_t, UCS("DebugTypeInfo::PrimitiveType") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasPrimitiveType, const_t, UCS("DebugTypeInfo::HasPrimitiveType") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, void, removePrimitiveType, no_const_t, UCS("DebugTypeInfo::removePrimitiveType") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, UCS("DebugTypeInfo::Identifier") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsChar, const_t, UCS("DebugTypeInfo::IsChar") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsChar, no_const_t, UCS("DebugTypeInfo::IsChar") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsString, const_t, UCS("DebugTypeInfo::IsString") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsString, no_const_t, UCS("DebugTypeInfo::IsString") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsBool, const_t, UCS("DebugTypeInfo::IsBool") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsBool, no_const_t, UCS("DebugTypeInfo::IsBool") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsFloat, const_t, UCS("DebugTypeInfo::IsFloat") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsFloat, no_const_t, UCS("DebugTypeInfo::IsFloat") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsSigned, const_t, UCS("DebugTypeInfo::IsSigned") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsSigned, no_const_t, UCS("DebugTypeInfo::IsSigned") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsWide, const_t, UCS("DebugTypeInfo::IsWide") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsWide, no_const_t, UCS("DebugTypeInfo::IsWide") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsPointer, const_t, UCS("DebugTypeInfo::IsPointer") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsPointer, no_const_t, UCS("DebugTypeInfo::IsPointer") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsReference, const_t, UCS("DebugTypeInfo::IsReference") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsReference, no_const_t, UCS("DebugTypeInfo::IsReference") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsArray, const_t, UCS("DebugTypeInfo::IsArray") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsArray, no_const_t, UCS("DebugTypeInfo::IsArray") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsConst, const_t, UCS("DebugTypeInfo::IsConst") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsConst, no_const_t, UCS("DebugTypeInfo::IsConst") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsVolatile, const_t, UCS("DebugTypeInfo::IsVolatile") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsVolatile, no_const_t, UCS("DebugTypeInfo::IsVolatile") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsStruct, const_t, UCS("DebugTypeInfo::IsStruct") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsStruct, no_const_t, UCS("DebugTypeInfo::IsStruct") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsClass, const_t, UCS("DebugTypeInfo::IsClass") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsClass, no_const_t, UCS("DebugTypeInfo::IsClass") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsUnion, const_t, UCS("DebugTypeInfo::IsUnion") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsUnion, no_const_t, UCS("DebugTypeInfo::IsUnion") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsInterface, const_t, UCS("DebugTypeInfo::IsInterface") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsInterface, no_const_t, UCS("DebugTypeInfo::IsInterface") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsEnum, const_t, UCS("DebugTypeInfo::IsEnum") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsEnum, no_const_t, UCS("DebugTypeInfo::IsEnum") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsFunction, const_t, UCS("DebugTypeInfo::IsFunction") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setIsFunction, no_const_t, UCS("DebugTypeInfo::IsFunction") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getBaseName, const_t, UCS("DebugTypeInfo::BaseName") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setBaseName, no_const_t, UCS("DebugTypeInfo::BaseName") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getName, const_t, UCS("DebugTypeInfo::Name") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setName, no_const_t, UCS("DebugTypeInfo::Name") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getSizeOf, const_t, UCS("DebugTypeInfo::SizeOf") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setSizeOf, no_const_t, UCS("DebugTypeInfo::SizeOf") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getTypeId, const_t, UCS("DebugTypeInfo::TypeId") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setTypeId, no_const_t, UCS("DebugTypeInfo::TypeId") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getArrayDim, const_t, UCS("DebugTypeInfo::ArrayDim") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, setArrayDim, no_const_t, UCS("DebugTypeInfo::ArrayDim") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, removeRichType, no_const_t, UCS("DebugTypeInfo::removeRichTypes") );
		METHOD_KEY_REGISTER2( DebugTypeInfoInterpreter, void, insertRichType, no_const_t, UCS("DebugTypeInfo::RichTypes") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getRichType, no_const_t, UCS("DebugTypeInfo::RichTypes") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, void, clearRichTypes, no_const_t, UCS("DebugTypeInfo::ClearRichTypes") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasRichTypes, const_t, UCS("DebugTypeInfo::HasRichTypes") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, richTypesCount, const_t, UCS("DebugTypeInfo::RichTypesCount") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, removeDebugFunctionInfo, no_const_t, UCS("DebugTypeInfo::removeDebugFunctionInfos") );
		METHOD_KEY_REGISTER2( DebugTypeInfoInterpreter, void, insertDebugFunctionInfo, no_const_t, UCS("DebugTypeInfo::DebugFunctionInfos") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugFunctionInfo, no_const_t, UCS("DebugTypeInfo::DebugFunctionInfos") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, void, clearDebugFunctionInfos, no_const_t, UCS("DebugTypeInfo::ClearDebugFunctionInfos") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasDebugFunctionInfos, const_t, UCS("DebugTypeInfo::HasDebugFunctionInfos") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, debugFunctionInfosCount, const_t, UCS("DebugTypeInfo::DebugFunctionInfosCount") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, void, removeDebugVariableInfo, no_const_t, UCS("DebugTypeInfo::removeDebugVariableInfos") );
		METHOD_KEY_REGISTER2( DebugTypeInfoInterpreter, void, insertDebugVariableInfo, no_const_t, UCS("DebugTypeInfo::DebugVariableInfos") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugVariableInfo, no_const_t, UCS("DebugTypeInfo::DebugVariableInfos") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, void, clearDebugVariableInfos, no_const_t, UCS("DebugTypeInfo::ClearDebugVariableInfos") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasDebugVariableInfos, const_t, UCS("DebugTypeInfo::HasDebugVariableInfos") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, debugVariableInfosCount, const_t, UCS("DebugTypeInfo::DebugVariableInfosCount") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("DebugTypeInfo") );
		CLASS_KEY_UNREGISTER22( UCS("DebugTypeInfo") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::PrimitiveType") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::PrimitiveType") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::HasPrimitiveType") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::removePrimitiveType") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::Identifier") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsChar") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsChar") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsString") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsString") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsBool") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsBool") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsFloat") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsFloat") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsSigned") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsSigned") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsWide") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsWide") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsPointer") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsPointer") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsReference") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsReference") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsArray") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsArray") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsConst") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsConst") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsVolatile") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsVolatile") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsStruct") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsStruct") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsClass") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsClass") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsUnion") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsUnion") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsInterface") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsInterface") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsEnum") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsEnum") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::IsFunction") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::IsFunction") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::BaseName") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::BaseName") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::Name") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::Name") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::SizeOf") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::SizeOf") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::TypeId") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::TypeId") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::ArrayDim") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::ArrayDim") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::removeRichTypes") );
		METHOD_KEY_UNREGISTER2( UCS("DebugTypeInfo::RichTypes") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::RichTypes") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::ClearRichTypes") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::HasRichTypes") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::RichTypesCount") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::removeDebugFunctionInfos") );
		METHOD_KEY_UNREGISTER2( UCS("DebugTypeInfo::DebugFunctionInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::DebugFunctionInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::ClearDebugFunctionInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::HasDebugFunctionInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::DebugFunctionInfosCount") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::removeDebugVariableInfos") );
		METHOD_KEY_UNREGISTER2( UCS("DebugTypeInfo::DebugVariableInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugTypeInfo::DebugVariableInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::ClearDebugVariableInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::HasDebugVariableInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugTypeInfo::DebugVariableInfosCount") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_debugTypeInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugTypeInfo<EncodingT> >& o);

template <class EncodingT>
bool reset_debugTypeInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugTypeInfo<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "debugTypeInfoInterpreter_impl.hpp"

#endif
