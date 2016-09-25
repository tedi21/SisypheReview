#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppFunctionInterpreter<EncodingT>::CppFunctionInterpreter()
{
	setValue( boost::shared_ptr< _CppFunction<EncodingT> > (new _CppFunction<EncodingT>()) );
}

template <class EncodingT>
CppFunctionInterpreter<EncodingT>::CppFunctionInterpreter(boost::shared_ptr< _CppFunction<EncodingT> > const& value)
{
	setValue(value);
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
				boost::shared_ptr< Base<EncodingT> > const& signature,
				boost::shared_ptr< Base<EncodingT> > const& startDecBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthDecBlock,
				boost::shared_ptr< Base<EncodingT> > const& decLineNumber,
				boost::shared_ptr< Base<EncodingT> > const& linesCount,
				boost::shared_ptr< Base<EncodingT> > const& complexity,
				boost::shared_ptr< Base<EncodingT> > const& defLineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startDefBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthDefBlock)
{
	typename EncodingT::string_t nativeName;
	typename EncodingT::string_t nativeAccessSpecifier;
	typename EncodingT::string_t nativeReturnType;
	int nativeIsConst;
	int nativeIsVirtual;
	int nativeIsVirtualPure;
	int nativeIsStatic;
	int nativeIsOperator;
	int nativeIsDestructor;
	int nativeIsConstructor;
	int nativeIsVariadic;
	typename EncodingT::string_t nativeSignature;
	int nativeStartDecBlock;
	int nativeLengthDecBlock;
	int nativeDecLineNumber;
	int nativeLinesCount;
	int nativeComplexity;
	int nativeDefLineNumber;
	int nativeStartDefBlock;
	int nativeLengthDefBlock;
	if (check_string<EncodingT>(name, nativeName) &&
		check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier) &&
		check_string<EncodingT>(returnType, nativeReturnType) &&
		check_numeric(isConst, nativeIsConst) &&
		check_numeric(isVirtual, nativeIsVirtual) &&
		check_numeric(isVirtualPure, nativeIsVirtualPure) &&
		check_numeric(isStatic, nativeIsStatic) &&
		check_numeric(isOperator, nativeIsOperator) &&
		check_numeric(isDestructor, nativeIsDestructor) &&
		check_numeric(isConstructor, nativeIsConstructor) &&
		check_numeric(isVariadic, nativeIsVariadic) &&
		check_string<EncodingT>(signature, nativeSignature) &&
		check_numeric(startDecBlock, nativeStartDecBlock) &&
		check_numeric(lengthDecBlock, nativeLengthDecBlock) &&
		check_numeric(decLineNumber, nativeDecLineNumber) &&
		check_numeric(linesCount, nativeLinesCount) &&
		check_numeric(complexity, nativeComplexity) &&
		check_numeric(defLineNumber, nativeDefLineNumber) &&
		check_numeric(startDefBlock, nativeStartDefBlock) &&
		check_numeric(lengthDefBlock, nativeLengthDefBlock))
	{
		setValue(boost::shared_ptr< _CppFunction<EncodingT> >(new _CppFunction<EncodingT>(nativeName,
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
				nativeSignature,
				nativeStartDecBlock,
				nativeLengthDecBlock,
				nativeDecLineNumber,
				nativeLinesCount,
				nativeComplexity,
				nativeDefLineNumber,
				nativeStartDefBlock,
				nativeLengthDefBlock)));
	}
}

template <class EncodingT>
CppFunctionInterpreter<EncodingT>::~CppFunctionInterpreter()
{}

template <class EncodingT>
boost::shared_ptr< _CppFunction<EncodingT> > CppFunctionInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setValue(boost::shared_ptr< _CppFunction<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getAccessSpecifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getAccessSpecifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getReturnType() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getReturnType()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsConst() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsConst()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsVirtual() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsVirtual()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsVirtualPure() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsVirtualPure()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsStatic() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsStatic()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsOperator() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsOperator()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsDestructor() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsDestructor()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsConstructor() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsConstructor()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsVariadic() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsVariadic()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getSignature() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getSignature()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getStartDecBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartDecBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getLengthDecBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthDecBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getDecLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getDecLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getLinesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLinesCount()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getComplexity() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getComplexity()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getDefLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getDefLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getStartDefBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartDefBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getLengthDefBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthDefBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppDeclarationFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(getValue()->getCppDeclarationFile()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppDefinitionFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(getValue()->getCppDefinitionFile()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppClass()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppClassInterpreter<EncodingT>(getValue()->getCppClass()) );
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setCppDeclarationFile(boost::shared_ptr< Base<EncodingT> > const& cppDeclarationFile)
{
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppDeclarationFile;
	if (check_cppFile(cppDeclarationFile, nativeCppDeclarationFile))
	{
		getValue()->setCppDeclarationFile(nativeCppDeclarationFile);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setCppDefinitionFile(boost::shared_ptr< Base<EncodingT> > const& cppDefinitionFile)
{
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppDefinitionFile;
	if (check_cppFile(cppDefinitionFile, nativeCppDefinitionFile))
	{
		getValue()->setCppDefinitionFile(nativeCppDefinitionFile);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		getValue()->setName(nativeName);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setCppClass(boost::shared_ptr< Base<EncodingT> > const& cppClass)
{
	boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
	if (check_cppClass(cppClass, nativeCppClass))
	{
		getValue()->setCppClass(nativeCppClass);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setAccessSpecifier(boost::shared_ptr< Base<EncodingT> > const& accessSpecifier)
{
	typename EncodingT::string_t nativeAccessSpecifier;
	if (check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier))
	{
		getValue()->setAccessSpecifier(nativeAccessSpecifier);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setReturnType(boost::shared_ptr< Base<EncodingT> > const& returnType)
{
	typename EncodingT::string_t nativeReturnType;
	if (check_string<EncodingT>(returnType, nativeReturnType))
	{
		getValue()->setReturnType(nativeReturnType);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst)
{
	int nativeIsConst;
	if (check_numeric(isConst, nativeIsConst))
	{
		getValue()->setIsConst(nativeIsConst);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsVirtual(boost::shared_ptr< Base<EncodingT> > const& isVirtual)
{
	int nativeIsVirtual;
	if (check_numeric(isVirtual, nativeIsVirtual))
	{
		getValue()->setIsVirtual(nativeIsVirtual);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsVirtualPure(boost::shared_ptr< Base<EncodingT> > const& isVirtualPure)
{
	int nativeIsVirtualPure;
	if (check_numeric(isVirtualPure, nativeIsVirtualPure))
	{
		getValue()->setIsVirtualPure(nativeIsVirtualPure);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsStatic(boost::shared_ptr< Base<EncodingT> > const& isStatic)
{
	int nativeIsStatic;
	if (check_numeric(isStatic, nativeIsStatic))
	{
		getValue()->setIsStatic(nativeIsStatic);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsOperator(boost::shared_ptr< Base<EncodingT> > const& isOperator)
{
	int nativeIsOperator;
	if (check_numeric(isOperator, nativeIsOperator))
	{
		getValue()->setIsOperator(nativeIsOperator);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsDestructor(boost::shared_ptr< Base<EncodingT> > const& isDestructor)
{
	int nativeIsDestructor;
	if (check_numeric(isDestructor, nativeIsDestructor))
	{
		getValue()->setIsDestructor(nativeIsDestructor);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsConstructor(boost::shared_ptr< Base<EncodingT> > const& isConstructor)
{
	int nativeIsConstructor;
	if (check_numeric(isConstructor, nativeIsConstructor))
	{
		getValue()->setIsConstructor(nativeIsConstructor);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsVariadic(boost::shared_ptr< Base<EncodingT> > const& isVariadic)
{
	int nativeIsVariadic;
	if (check_numeric(isVariadic, nativeIsVariadic))
	{
		getValue()->setIsVariadic(nativeIsVariadic);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setSignature(boost::shared_ptr< Base<EncodingT> > const& signature)
{
	typename EncodingT::string_t nativeSignature;
	if (check_string<EncodingT>(signature, nativeSignature))
	{
		getValue()->setSignature(nativeSignature);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setStartDecBlock(boost::shared_ptr< Base<EncodingT> > const& startDecBlock)
{
	int nativeStartDecBlock;
	if (check_numeric(startDecBlock, nativeStartDecBlock))
	{
		getValue()->setStartDecBlock(nativeStartDecBlock);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setLengthDecBlock(boost::shared_ptr< Base<EncodingT> > const& lengthDecBlock)
{
	int nativeLengthDecBlock;
	if (check_numeric(lengthDecBlock, nativeLengthDecBlock))
	{
		getValue()->setLengthDecBlock(nativeLengthDecBlock);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setDecLineNumber(boost::shared_ptr< Base<EncodingT> > const& decLineNumber)
{
	int nativeDecLineNumber;
	if (check_numeric(decLineNumber, nativeDecLineNumber))
	{
		getValue()->setDecLineNumber(nativeDecLineNumber);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setLinesCount(boost::shared_ptr< Base<EncodingT> > const& linesCount)
{
	int nativeLinesCount;
	if (check_numeric(linesCount, nativeLinesCount))
	{
		getValue()->setLinesCount(nativeLinesCount);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setComplexity(boost::shared_ptr< Base<EncodingT> > const& complexity)
{
	int nativeComplexity;
	if (check_numeric(complexity, nativeComplexity))
	{
		getValue()->setComplexity(nativeComplexity);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setDefLineNumber(boost::shared_ptr< Base<EncodingT> > const& defLineNumber)
{
	int nativeDefLineNumber;
	if (check_numeric(defLineNumber, nativeDefLineNumber))
	{
		getValue()->setDefLineNumber(nativeDefLineNumber);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setStartDefBlock(boost::shared_ptr< Base<EncodingT> > const& startDefBlock)
{
	int nativeStartDefBlock;
	if (check_numeric(startDefBlock, nativeStartDefBlock))
	{
		getValue()->setStartDefBlock(nativeStartDefBlock);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setLengthDefBlock(boost::shared_ptr< Base<EncodingT> > const& lengthDefBlock)
{
	int nativeLengthDefBlock;
	if (check_numeric(lengthDefBlock, nativeLengthDefBlock))
	{
		getValue()->setLengthDefBlock(nativeLengthDefBlock);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppDeclarationFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppDeclarationFile()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppDefinitionFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppDefinitionFile()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppClass() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppClass()) );
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::removeCppDeclarationFile()
{
	getValue()->eraseCppDeclarationFile();
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::removeCppDefinitionFile()
{
	getValue()->eraseCppDefinitionFile();
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::removeCppClass()
{
	getValue()->eraseCppClass();
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::removeCppParameter(boost::shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppParameter(getValue()->getCppParametersBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::removeCppVariable(boost::shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppVariable(getValue()->getCppVariablesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::removeDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseDebugFunctionInfo(getValue()->getDebugFunctionInfosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::insertCppParameter(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppParameter)
{
	int nativePosition;
	boost::shared_ptr< _CppParameter<EncodingT> > nativeCppParameter;
	if (check_numeric(n, nativePosition) &&
		check_cppParameter(cppParameter, nativeCppParameter))
	{
		getValue()->insertCppParameter(getValue()->getCppParametersBeginning()+nativePosition, nativeCppParameter);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::insertCppVariable(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppVariable)
{
	int nativePosition;
	boost::shared_ptr< _CppVariable<EncodingT> > nativeCppVariable;
	if (check_numeric(n, nativePosition) &&
		check_cppVariable(cppVariable, nativeCppVariable))
	{
		getValue()->insertCppVariable(getValue()->getCppVariablesBeginning()+nativePosition, nativeCppVariable);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::insertDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugFunctionInfo)
{
	int nativePosition;
	boost::shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
	if (check_numeric(n, nativePosition) &&
		check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo))
	{
		getValue()->insertDebugFunctionInfo(getValue()->getDebugFunctionInfosBeginning()+nativePosition, nativeDebugFunctionInfo);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppParameter(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppParameterInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppParameterInterpreter<EncodingT>(getValue()->getCppParameterAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppVariable(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppVariableInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppVariableInterpreter<EncodingT>(getValue()->getCppVariableAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugFunctionInfoInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new DebugFunctionInfoInterpreter<EncodingT>(getValue()->getDebugFunctionInfoAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::clearCppParameters()
{
	getValue()->clearCppParameters();
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::clearCppVariables()
{
	getValue()->clearCppVariables();
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::clearDebugFunctionInfos()
{
	getValue()->clearDebugFunctionInfos();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppParameters() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppParametersEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppVariables() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppVariablesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasDebugFunctionInfos() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isDebugFunctionInfosEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::cppParametersCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppParametersSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::cppVariablesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppVariablesSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::debugFunctionInfosCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getDebugFunctionInfosSize()));
}

template <class EncodingT>
typename EncodingT::string_t CppFunctionInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppFunctionInterpreter<EncodingT>(copy_ptr(getValue())));
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
			tryInvoke(this, C("String"), method, args, ret))
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
		o = value->getValue();
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
		value->setValue(o);
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

