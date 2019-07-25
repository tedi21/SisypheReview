#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppFunctionInterpreter<EncodingT>::CppFunctionInterpreter()
{
	m_value = boost::make_shared< _CppFunction<EncodingT> >();
}

template <class EncodingT>
CppFunctionInterpreter<EncodingT>::CppFunctionInterpreter(boost::shared_ptr< _CppFunction<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
CppFunctionInterpreter<EncodingT>::CppFunctionInterpreter(boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& accessSpecifier,
				boost::shared_ptr< Base<EncodingT> > const& returnType,
				boost::shared_ptr< Base<EncodingT> > const& isConst,
				boost::shared_ptr< Base<EncodingT> > const& isVirtual,
				boost::shared_ptr< Base<EncodingT> > const& isVirtualPure,
				boost::shared_ptr< Base<EncodingT> > const& isStatic,
				boost::shared_ptr< Base<EncodingT> > const& isOperator,
				boost::shared_ptr< Base<EncodingT> > const& isDestructor,
				boost::shared_ptr< Base<EncodingT> > const& isConstructor,
				boost::shared_ptr< Base<EncodingT> > const& isVariadic,
				boost::shared_ptr< Base<EncodingT> > const& isTemplate,
				boost::shared_ptr< Base<EncodingT> > const& isInline,
				boost::shared_ptr< Base<EncodingT> > const& isConstexpr,
				boost::shared_ptr< Base<EncodingT> > const& isOverride,
				boost::shared_ptr< Base<EncodingT> > const& isFinal,
				boost::shared_ptr< Base<EncodingT> > const& isNoexcept,
				boost::shared_ptr< Base<EncodingT> > const& signature,
				boost::shared_ptr< Base<EncodingT> > const& decLineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startDecBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthDecBlock,
				boost::shared_ptr< Base<EncodingT> > const& linesCount,
				boost::shared_ptr< Base<EncodingT> > const& complexity,
				boost::shared_ptr< Base<EncodingT> > const& defLineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startDefBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthDefBlock)
{
	typename EncodingT::string_t nativeName;
	typename EncodingT::string_t nativeAccessSpecifier;
	typename EncodingT::string_t nativeReturnType;
	long long nativeIsConst;
	long long nativeIsVirtual;
	long long nativeIsVirtualPure;
	long long nativeIsStatic;
	long long nativeIsOperator;
	long long nativeIsDestructor;
	long long nativeIsConstructor;
	long long nativeIsVariadic;
	long long nativeIsTemplate;
	long long nativeIsInline;
	long long nativeIsConstexpr;
	long long nativeIsOverride;
	long long nativeIsFinal;
	long long nativeIsNoexcept;
	typename EncodingT::string_t nativeSignature;
	long long nativeDecLineNumber;
	long long nativeStartDecBlock;
	long long nativeLengthDecBlock;
	long long nativeLinesCount;
	long long nativeComplexity;
	long long nativeDefLineNumber;
	long long nativeStartDefBlock;
	long long nativeLengthDefBlock;
	if (check_string<EncodingT>(name, nativeName) &&
		check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier) &&
		check_string<EncodingT>(returnType, nativeReturnType) &&
		check_numeric_i(isConst, nativeIsConst) &&
		check_numeric_i(isVirtual, nativeIsVirtual) &&
		check_numeric_i(isVirtualPure, nativeIsVirtualPure) &&
		check_numeric_i(isStatic, nativeIsStatic) &&
		check_numeric_i(isOperator, nativeIsOperator) &&
		check_numeric_i(isDestructor, nativeIsDestructor) &&
		check_numeric_i(isConstructor, nativeIsConstructor) &&
		check_numeric_i(isVariadic, nativeIsVariadic) &&
		check_numeric_i(isTemplate, nativeIsTemplate) &&
		check_numeric_i(isInline, nativeIsInline) &&
		check_numeric_i(isConstexpr, nativeIsConstexpr) &&
		check_numeric_i(isOverride, nativeIsOverride) &&
		check_numeric_i(isFinal, nativeIsFinal) &&
		check_numeric_i(isNoexcept, nativeIsNoexcept) &&
		check_string<EncodingT>(signature, nativeSignature) &&
		check_numeric_i(decLineNumber, nativeDecLineNumber) &&
		check_numeric_i(startDecBlock, nativeStartDecBlock) &&
		check_numeric_i(lengthDecBlock, nativeLengthDecBlock) &&
		check_numeric_i(linesCount, nativeLinesCount) &&
		check_numeric_i(complexity, nativeComplexity) &&
		check_numeric_i(defLineNumber, nativeDefLineNumber) &&
		check_numeric_i(startDefBlock, nativeStartDefBlock) &&
		check_numeric_i(lengthDefBlock, nativeLengthDefBlock))
	{
		m_value = boost::make_shared< _CppFunction<EncodingT> >(nativeName,
				nativeAccessSpecifier,
				nativeReturnType,
				nativeIsConst,
				nativeIsVirtual,
				nativeIsVirtualPure,
				nativeIsStatic,
				nativeIsOperator,
				nativeIsDestructor,
				nativeIsConstructor,
				nativeIsVariadic,
				nativeIsTemplate,
				nativeIsInline,
				nativeIsConstexpr,
				nativeIsOverride,
				nativeIsFinal,
				nativeIsNoexcept,
				nativeSignature,
				nativeDecLineNumber,
				nativeStartDecBlock,
				nativeLengthDecBlock,
				nativeLinesCount,
				nativeComplexity,
				nativeDefLineNumber,
				nativeStartDefBlock,
				nativeLengthDefBlock);
	}
}

template <class EncodingT>
boost::shared_ptr< _CppFunction<EncodingT> > CppFunctionInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::value(boost::shared_ptr< _CppFunction<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getAccessSpecifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getAccessSpecifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getReturnType() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getReturnType()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsConst() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsConst()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsVirtual() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsVirtual()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsVirtualPure() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsVirtualPure()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsStatic() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsStatic()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsOperator() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsOperator()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsDestructor() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsDestructor()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsConstructor() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsConstructor()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsVariadic() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsVariadic()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsTemplate() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsTemplate()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsInline() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsInline()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsConstexpr() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsConstexpr()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsOverride() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsOverride()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsFinal() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsFinal()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsNoexcept() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsNoexcept()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getSignature() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getSignature()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getDecLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getDecLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getStartDecBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getStartDecBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getLengthDecBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLengthDecBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getLinesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLinesCount()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getComplexity() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getComplexity()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getDefLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getDefLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getStartDefBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getStartDefBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getLengthDefBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLengthDefBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppDeclarationFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(m_value->getCppDeclarationFile()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppDefinitionFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(m_value->getCppDefinitionFile()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppClass()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppClassInterpreter<EncodingT>(m_value->getCppClass()) );
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setCppDeclarationFile(boost::shared_ptr< Base<EncodingT> > const& cppDeclarationFile)
{
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppDeclarationFile;
	if (check_cppFile(cppDeclarationFile, nativeCppDeclarationFile))
	{
		m_value->setCppDeclarationFile(nativeCppDeclarationFile);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setCppDefinitionFile(boost::shared_ptr< Base<EncodingT> > const& cppDefinitionFile)
{
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppDefinitionFile;
	if (check_cppFile(cppDefinitionFile, nativeCppDefinitionFile))
	{
		m_value->setCppDefinitionFile(nativeCppDefinitionFile);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		m_value->setName(nativeName);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setCppClass(boost::shared_ptr< Base<EncodingT> > const& cppClass)
{
	boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
	if (check_cppClass(cppClass, nativeCppClass))
	{
		m_value->setCppClass(nativeCppClass);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setAccessSpecifier(boost::shared_ptr< Base<EncodingT> > const& accessSpecifier)
{
	typename EncodingT::string_t nativeAccessSpecifier;
	if (check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier))
	{
		m_value->setAccessSpecifier(nativeAccessSpecifier);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setReturnType(boost::shared_ptr< Base<EncodingT> > const& returnType)
{
	typename EncodingT::string_t nativeReturnType;
	if (check_string<EncodingT>(returnType, nativeReturnType))
	{
		m_value->setReturnType(nativeReturnType);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst)
{
	long long nativeIsConst;
	if (check_numeric_i(isConst, nativeIsConst))
	{
		m_value->setIsConst(nativeIsConst);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsVirtual(boost::shared_ptr< Base<EncodingT> > const& isVirtual)
{
	long long nativeIsVirtual;
	if (check_numeric_i(isVirtual, nativeIsVirtual))
	{
		m_value->setIsVirtual(nativeIsVirtual);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsVirtualPure(boost::shared_ptr< Base<EncodingT> > const& isVirtualPure)
{
	long long nativeIsVirtualPure;
	if (check_numeric_i(isVirtualPure, nativeIsVirtualPure))
	{
		m_value->setIsVirtualPure(nativeIsVirtualPure);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsStatic(boost::shared_ptr< Base<EncodingT> > const& isStatic)
{
	long long nativeIsStatic;
	if (check_numeric_i(isStatic, nativeIsStatic))
	{
		m_value->setIsStatic(nativeIsStatic);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsOperator(boost::shared_ptr< Base<EncodingT> > const& isOperator)
{
	long long nativeIsOperator;
	if (check_numeric_i(isOperator, nativeIsOperator))
	{
		m_value->setIsOperator(nativeIsOperator);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsDestructor(boost::shared_ptr< Base<EncodingT> > const& isDestructor)
{
	long long nativeIsDestructor;
	if (check_numeric_i(isDestructor, nativeIsDestructor))
	{
		m_value->setIsDestructor(nativeIsDestructor);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsConstructor(boost::shared_ptr< Base<EncodingT> > const& isConstructor)
{
	long long nativeIsConstructor;
	if (check_numeric_i(isConstructor, nativeIsConstructor))
	{
		m_value->setIsConstructor(nativeIsConstructor);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsVariadic(boost::shared_ptr< Base<EncodingT> > const& isVariadic)
{
	long long nativeIsVariadic;
	if (check_numeric_i(isVariadic, nativeIsVariadic))
	{
		m_value->setIsVariadic(nativeIsVariadic);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsTemplate(boost::shared_ptr< Base<EncodingT> > const& isTemplate)
{
	long long nativeIsTemplate;
	if (check_numeric_i(isTemplate, nativeIsTemplate))
	{
		m_value->setIsTemplate(nativeIsTemplate);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsInline(boost::shared_ptr< Base<EncodingT> > const& isInline)
{
	long long nativeIsInline;
	if (check_numeric_i(isInline, nativeIsInline))
	{
		m_value->setIsInline(nativeIsInline);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsConstexpr(boost::shared_ptr< Base<EncodingT> > const& isConstexpr)
{
	long long nativeIsConstexpr;
	if (check_numeric_i(isConstexpr, nativeIsConstexpr))
	{
		m_value->setIsConstexpr(nativeIsConstexpr);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsOverride(boost::shared_ptr< Base<EncodingT> > const& isOverride)
{
	long long nativeIsOverride;
	if (check_numeric_i(isOverride, nativeIsOverride))
	{
		m_value->setIsOverride(nativeIsOverride);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsFinal(boost::shared_ptr< Base<EncodingT> > const& isFinal)
{
	long long nativeIsFinal;
	if (check_numeric_i(isFinal, nativeIsFinal))
	{
		m_value->setIsFinal(nativeIsFinal);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsNoexcept(boost::shared_ptr< Base<EncodingT> > const& isNoexcept)
{
	long long nativeIsNoexcept;
	if (check_numeric_i(isNoexcept, nativeIsNoexcept))
	{
		m_value->setIsNoexcept(nativeIsNoexcept);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setSignature(boost::shared_ptr< Base<EncodingT> > const& signature)
{
	typename EncodingT::string_t nativeSignature;
	if (check_string<EncodingT>(signature, nativeSignature))
	{
		m_value->setSignature(nativeSignature);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setDecLineNumber(boost::shared_ptr< Base<EncodingT> > const& decLineNumber)
{
	long long nativeDecLineNumber;
	if (check_numeric_i(decLineNumber, nativeDecLineNumber))
	{
		m_value->setDecLineNumber(nativeDecLineNumber);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setStartDecBlock(boost::shared_ptr< Base<EncodingT> > const& startDecBlock)
{
	long long nativeStartDecBlock;
	if (check_numeric_i(startDecBlock, nativeStartDecBlock))
	{
		m_value->setStartDecBlock(nativeStartDecBlock);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setLengthDecBlock(boost::shared_ptr< Base<EncodingT> > const& lengthDecBlock)
{
	long long nativeLengthDecBlock;
	if (check_numeric_i(lengthDecBlock, nativeLengthDecBlock))
	{
		m_value->setLengthDecBlock(nativeLengthDecBlock);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setLinesCount(boost::shared_ptr< Base<EncodingT> > const& linesCount)
{
	long long nativeLinesCount;
	if (check_numeric_i(linesCount, nativeLinesCount))
	{
		m_value->setLinesCount(nativeLinesCount);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setComplexity(boost::shared_ptr< Base<EncodingT> > const& complexity)
{
	long long nativeComplexity;
	if (check_numeric_i(complexity, nativeComplexity))
	{
		m_value->setComplexity(nativeComplexity);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setDefLineNumber(boost::shared_ptr< Base<EncodingT> > const& defLineNumber)
{
	long long nativeDefLineNumber;
	if (check_numeric_i(defLineNumber, nativeDefLineNumber))
	{
		m_value->setDefLineNumber(nativeDefLineNumber);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setStartDefBlock(boost::shared_ptr< Base<EncodingT> > const& startDefBlock)
{
	long long nativeStartDefBlock;
	if (check_numeric_i(startDefBlock, nativeStartDefBlock))
	{
		m_value->setStartDefBlock(nativeStartDefBlock);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setLengthDefBlock(boost::shared_ptr< Base<EncodingT> > const& lengthDefBlock)
{
	long long nativeLengthDefBlock;
	if (check_numeric_i(lengthDefBlock, nativeLengthDefBlock))
	{
		m_value->setLengthDefBlock(nativeLengthDefBlock);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppDeclarationFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppDeclarationFile()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppDefinitionFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppDefinitionFile()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppClass() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppClass()) );
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::removeCppDeclarationFile()
{
	m_value->eraseCppDeclarationFile();
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::removeCppDefinitionFile()
{
	m_value->eraseCppDefinitionFile();
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::removeCppClass()
{
	m_value->eraseCppClass();
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::removeCppParameter(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppParameter(m_value->getCppParametersBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::removeCppVariable(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppVariable(m_value->getCppVariablesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::insertCppParameter(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppParameter)
{
	size_t nativePosition;
	boost::shared_ptr< _CppParameter<EncodingT> > nativeCppParameter;
	if (check_numeric_i(n, nativePosition) &&
		check_cppParameter(cppParameter, nativeCppParameter))
	{
		m_value->insertCppParameter(m_value->getCppParametersBeginning()+nativePosition, nativeCppParameter);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::insertCppVariable(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppVariable)
{
	size_t nativePosition;
	boost::shared_ptr< _CppVariable<EncodingT> > nativeCppVariable;
	if (check_numeric_i(n, nativePosition) &&
		check_cppVariable(cppVariable, nativeCppVariable))
	{
		m_value->insertCppVariable(m_value->getCppVariablesBeginning()+nativePosition, nativeCppVariable);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppParameter(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppParameterInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new CppParameterInterpreter<EncodingT>(m_value->getCppParameterAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppVariable(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppVariableInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new CppVariableInterpreter<EncodingT>(m_value->getCppVariableAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::clearCppParameters()
{
	m_value->clearCppParameters();
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::clearCppVariables()
{
	m_value->clearCppVariables();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppParameters() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppParametersEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppVariables() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppVariablesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::cppParametersCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppParametersSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::cppVariablesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppVariablesSize()));
}

template <class EncodingT>
typename EncodingT::string_t CppFunctionInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppFunctionInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t CppFunctionInterpreter<EncodingT>::getClassName() const
{
	return C("CppFunction");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppFunction"), method, args, ret) ||
			tryInvoke(this, C("Base"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in CppFunction, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppFunction(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppFunction<EncodingT> >& o)
{
	boost::shared_ptr< CppFunctionInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppFunctionInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppFunction expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cppFunction(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppFunction<EncodingT> > const& o)
{
	boost::shared_ptr< CppFunctionInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppFunctionInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppFunction expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

