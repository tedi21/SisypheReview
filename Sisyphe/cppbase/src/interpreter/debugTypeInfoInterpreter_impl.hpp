#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugTypeInfoInterpreter<EncodingT>::DebugTypeInfoInterpreter()
{
	m_value = boost::make_shared< _DebugTypeInfo<EncodingT> >();
}

template <class EncodingT>
DebugTypeInfoInterpreter<EncodingT>::DebugTypeInfoInterpreter(boost::shared_ptr< _DebugTypeInfo<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
DebugTypeInfoInterpreter<EncodingT>::DebugTypeInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& isChar,
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
				boost::shared_ptr< Base<EncodingT> > const& arrayDim)
{
	long long nativeIsChar;
	long long nativeIsString;
	long long nativeIsBool;
	long long nativeIsFloat;
	long long nativeIsSigned;
	long long nativeIsWide;
	long long nativeIsPointer;
	long long nativeIsReference;
	long long nativeIsArray;
	long long nativeIsConst;
	long long nativeIsVolatile;
	long long nativeIsStruct;
	long long nativeIsClass;
	long long nativeIsUnion;
	long long nativeIsInterface;
	long long nativeIsEnum;
	long long nativeIsFunction;
	typename EncodingT::string_t nativeBaseName;
	typename EncodingT::string_t nativeName;
	long long nativeSizeOf;
	long long nativeTypeId;
	long long nativeArrayDim;
	if (check_numeric_i(isChar, nativeIsChar) &&
		check_numeric_i(isString, nativeIsString) &&
		check_numeric_i(isBool, nativeIsBool) &&
		check_numeric_i(isFloat, nativeIsFloat) &&
		check_numeric_i(isSigned, nativeIsSigned) &&
		check_numeric_i(isWide, nativeIsWide) &&
		check_numeric_i(isPointer, nativeIsPointer) &&
		check_numeric_i(isReference, nativeIsReference) &&
		check_numeric_i(isArray, nativeIsArray) &&
		check_numeric_i(isConst, nativeIsConst) &&
		check_numeric_i(isVolatile, nativeIsVolatile) &&
		check_numeric_i(isStruct, nativeIsStruct) &&
		check_numeric_i(isClass, nativeIsClass) &&
		check_numeric_i(isUnion, nativeIsUnion) &&
		check_numeric_i(isInterface, nativeIsInterface) &&
		check_numeric_i(isEnum, nativeIsEnum) &&
		check_numeric_i(isFunction, nativeIsFunction) &&
		check_string<EncodingT>(baseName, nativeBaseName) &&
		check_string<EncodingT>(name, nativeName) &&
		check_numeric_i(sizeOf, nativeSizeOf) &&
		check_numeric_i(typeId, nativeTypeId) &&
		check_numeric_i(arrayDim, nativeArrayDim))
	{
		m_value = boost::make_shared< _DebugTypeInfo<EncodingT> >(nativeIsChar,
				nativeIsString,
				nativeIsBool,
				nativeIsFloat,
				nativeIsSigned,
				nativeIsWide,
				nativeIsPointer,
				nativeIsReference,
				nativeIsArray,
				nativeIsConst,
				nativeIsVolatile,
				nativeIsStruct,
				nativeIsClass,
				nativeIsUnion,
				nativeIsInterface,
				nativeIsEnum,
				nativeIsFunction,
				nativeBaseName,
				nativeName,
				nativeSizeOf,
				nativeTypeId,
				nativeArrayDim);
	}
}

template <class EncodingT>
boost::shared_ptr< _DebugTypeInfo<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::value(boost::shared_ptr< _DebugTypeInfo<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsChar() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsChar()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsString() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsString()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsBool() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsBool()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsFloat() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsFloat()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsSigned() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsSigned()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsWide() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsWide()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsPointer() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsPointer()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsReference() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsReference()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsArray() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsArray()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsConst() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsConst()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsVolatile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsVolatile()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsStruct() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsStruct()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsClass() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsClass()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsUnion() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsUnion()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsInterface() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsInterface()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsEnum() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsEnum()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getIsFunction() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsFunction()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getBaseName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getBaseName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getSizeOf() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getSizeOf()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getTypeId() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getTypeId()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getArrayDim() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getArrayDim()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getPrimitiveType()
{
	return boost::shared_ptr< Base<EncodingT> >( new DebugTypeInfoInterpreter<EncodingT>(m_value->getPrimitiveType()) );
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setPrimitiveType(boost::shared_ptr< Base<EncodingT> > const& primitiveType)
{
	boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativePrimitiveType;
	if (check_debugTypeInfo(primitiveType, nativePrimitiveType))
	{
		m_value->setPrimitiveType(nativePrimitiveType);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsChar(boost::shared_ptr< Base<EncodingT> > const& isChar)
{
	long long nativeIsChar;
	if (check_numeric_i(isChar, nativeIsChar))
	{
		m_value->setIsChar(nativeIsChar);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsString(boost::shared_ptr< Base<EncodingT> > const& isString)
{
	long long nativeIsString;
	if (check_numeric_i(isString, nativeIsString))
	{
		m_value->setIsString(nativeIsString);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsBool(boost::shared_ptr< Base<EncodingT> > const& isBool)
{
	long long nativeIsBool;
	if (check_numeric_i(isBool, nativeIsBool))
	{
		m_value->setIsBool(nativeIsBool);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsFloat(boost::shared_ptr< Base<EncodingT> > const& isFloat)
{
	long long nativeIsFloat;
	if (check_numeric_i(isFloat, nativeIsFloat))
	{
		m_value->setIsFloat(nativeIsFloat);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsSigned(boost::shared_ptr< Base<EncodingT> > const& isSigned)
{
	long long nativeIsSigned;
	if (check_numeric_i(isSigned, nativeIsSigned))
	{
		m_value->setIsSigned(nativeIsSigned);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsWide(boost::shared_ptr< Base<EncodingT> > const& isWide)
{
	long long nativeIsWide;
	if (check_numeric_i(isWide, nativeIsWide))
	{
		m_value->setIsWide(nativeIsWide);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsPointer(boost::shared_ptr< Base<EncodingT> > const& isPointer)
{
	long long nativeIsPointer;
	if (check_numeric_i(isPointer, nativeIsPointer))
	{
		m_value->setIsPointer(nativeIsPointer);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsReference(boost::shared_ptr< Base<EncodingT> > const& isReference)
{
	long long nativeIsReference;
	if (check_numeric_i(isReference, nativeIsReference))
	{
		m_value->setIsReference(nativeIsReference);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsArray(boost::shared_ptr< Base<EncodingT> > const& isArray)
{
	long long nativeIsArray;
	if (check_numeric_i(isArray, nativeIsArray))
	{
		m_value->setIsArray(nativeIsArray);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst)
{
	long long nativeIsConst;
	if (check_numeric_i(isConst, nativeIsConst))
	{
		m_value->setIsConst(nativeIsConst);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsVolatile(boost::shared_ptr< Base<EncodingT> > const& isVolatile)
{
	long long nativeIsVolatile;
	if (check_numeric_i(isVolatile, nativeIsVolatile))
	{
		m_value->setIsVolatile(nativeIsVolatile);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsStruct(boost::shared_ptr< Base<EncodingT> > const& isStruct)
{
	long long nativeIsStruct;
	if (check_numeric_i(isStruct, nativeIsStruct))
	{
		m_value->setIsStruct(nativeIsStruct);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsClass(boost::shared_ptr< Base<EncodingT> > const& isClass)
{
	long long nativeIsClass;
	if (check_numeric_i(isClass, nativeIsClass))
	{
		m_value->setIsClass(nativeIsClass);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsUnion(boost::shared_ptr< Base<EncodingT> > const& isUnion)
{
	long long nativeIsUnion;
	if (check_numeric_i(isUnion, nativeIsUnion))
	{
		m_value->setIsUnion(nativeIsUnion);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsInterface(boost::shared_ptr< Base<EncodingT> > const& isInterface)
{
	long long nativeIsInterface;
	if (check_numeric_i(isInterface, nativeIsInterface))
	{
		m_value->setIsInterface(nativeIsInterface);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsEnum(boost::shared_ptr< Base<EncodingT> > const& isEnum)
{
	long long nativeIsEnum;
	if (check_numeric_i(isEnum, nativeIsEnum))
	{
		m_value->setIsEnum(nativeIsEnum);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setIsFunction(boost::shared_ptr< Base<EncodingT> > const& isFunction)
{
	long long nativeIsFunction;
	if (check_numeric_i(isFunction, nativeIsFunction))
	{
		m_value->setIsFunction(nativeIsFunction);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setBaseName(boost::shared_ptr< Base<EncodingT> > const& baseName)
{
	typename EncodingT::string_t nativeBaseName;
	if (check_string<EncodingT>(baseName, nativeBaseName))
	{
		m_value->setBaseName(nativeBaseName);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		m_value->setName(nativeName);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setSizeOf(boost::shared_ptr< Base<EncodingT> > const& sizeOf)
{
	long long nativeSizeOf;
	if (check_numeric_i(sizeOf, nativeSizeOf))
	{
		m_value->setSizeOf(nativeSizeOf);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setTypeId(boost::shared_ptr< Base<EncodingT> > const& typeId)
{
	long long nativeTypeId;
	if (check_numeric_i(typeId, nativeTypeId))
	{
		m_value->setTypeId(nativeTypeId);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::setArrayDim(boost::shared_ptr< Base<EncodingT> > const& arrayDim)
{
	long long nativeArrayDim;
	if (check_numeric_i(arrayDim, nativeArrayDim))
	{
		m_value->setArrayDim(nativeArrayDim);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::hasPrimitiveType() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullPrimitiveType()) );
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::removePrimitiveType()
{
	m_value->erasePrimitiveType();
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::removeRichType(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseRichType(m_value->getRichTypesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::removeDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseDebugFunctionInfo(m_value->getDebugFunctionInfosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::removeDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseDebugVariableInfo(m_value->getDebugVariableInfosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::insertRichType(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& richType)
{
	size_t nativePosition;
	boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeRichType;
	if (check_numeric_i(n, nativePosition) &&
		check_debugTypeInfo(richType, nativeRichType))
	{
		m_value->insertRichType(m_value->getRichTypesBeginning()+nativePosition, nativeRichType);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::insertDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugFunctionInfo)
{
	size_t nativePosition;
	boost::shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
	if (check_numeric_i(n, nativePosition) &&
		check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo))
	{
		m_value->insertDebugFunctionInfo(m_value->getDebugFunctionInfosBeginning()+nativePosition, nativeDebugFunctionInfo);
	}
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::insertDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugVariableInfo)
{
	size_t nativePosition;
	boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
	if (check_numeric_i(n, nativePosition) &&
		check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
	{
		m_value->insertDebugVariableInfo(m_value->getDebugVariableInfosBeginning()+nativePosition, nativeDebugVariableInfo);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getRichType(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugTypeInfoInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new DebugTypeInfoInterpreter<EncodingT>(m_value->getRichTypeAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugFunctionInfoInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new DebugFunctionInfoInterpreter<EncodingT>(m_value->getDebugFunctionInfoAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::getDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugVariableInfoInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new DebugVariableInfoInterpreter<EncodingT>(m_value->getDebugVariableInfoAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::clearRichTypes()
{
	m_value->clearRichTypes();
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::clearDebugFunctionInfos()
{
	m_value->clearDebugFunctionInfos();
}


template <class EncodingT>
void DebugTypeInfoInterpreter<EncodingT>::clearDebugVariableInfos()
{
	m_value->clearDebugVariableInfos();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::hasRichTypes() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isRichTypesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::hasDebugFunctionInfos() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isDebugFunctionInfosEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::hasDebugVariableInfos() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isDebugVariableInfosEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::richTypesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getRichTypesSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::debugFunctionInfosCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getDebugFunctionInfosSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::debugVariableInfosCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getDebugVariableInfosSize()));
}

template <class EncodingT>
typename EncodingT::string_t DebugTypeInfoInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugTypeInfoInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t DebugTypeInfoInterpreter<EncodingT>::getClassName() const
{
	return UCS("DebugTypeInfo");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugTypeInfo"), method, args, ret) ||
			tryInvoke(this, UCS("Base"), method, args, ret))
		{
			find_parameter(ret, FACTORY_RETURN_PARAMETER, obj);
			for (size_t i = 0; i < params.size(); ++i)
			{
				find_parameter(ret, i, params[i]);
			}
		}
		else
		{
			Category* logger = &Category::getInstance(LOGNAME);
			logger->errorStream() << "Unexpected call in DebugTypeInfo, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_debugTypeInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugTypeInfo<EncodingT> >& o)
{
	boost::shared_ptr< DebugTypeInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugTypeInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugTypeInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_debugTypeInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugTypeInfo<EncodingT> > const& o)
{
	boost::shared_ptr< DebugTypeInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugTypeInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugTypeInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

