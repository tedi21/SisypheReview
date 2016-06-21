#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppFunctionInterpreter<EncodingT>::CppFunctionInterpreter()
{
	setValue( shared_ptr< _CppFunction<EncodingT> > (new _CppFunction<EncodingT>()) );
}

template <class EncodingT>
CppFunctionInterpreter<EncodingT>::CppFunctionInterpreter(shared_ptr< _CppFunction<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CppFunctionInterpreter<EncodingT>::CppFunctionInterpreter(shared_ptr< Base<EncodingT> > const& name,
				shared_ptr< Base<EncodingT> > const& accessSpecifier,
				shared_ptr< Base<EncodingT> > const& returnType,
				shared_ptr< Base<EncodingT> > const& isConst,
				shared_ptr< Base<EncodingT> > const& isVirtual,
				shared_ptr< Base<EncodingT> > const& isVirtualPure,
				shared_ptr< Base<EncodingT> > const& isStatic,
				shared_ptr< Base<EncodingT> > const& isOperator,
				shared_ptr< Base<EncodingT> > const& isDestructor,
				shared_ptr< Base<EncodingT> > const& isConstructor,
				shared_ptr< Base<EncodingT> > const& isVariadic,
				shared_ptr< Base<EncodingT> > const& signature,
				shared_ptr< Base<EncodingT> > const& startDecBlock,
				shared_ptr< Base<EncodingT> > const& lengthDecBlock,
				shared_ptr< Base<EncodingT> > const& decLineNumber,
				shared_ptr< Base<EncodingT> > const& linesCount,
				shared_ptr< Base<EncodingT> > const& complexity,
				shared_ptr< Base<EncodingT> > const& defLineNumber,
				shared_ptr< Base<EncodingT> > const& startDefBlock,
				shared_ptr< Base<EncodingT> > const& lengthDefBlock)
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
		setValue(shared_ptr< _CppFunction<EncodingT> >(new _CppFunction<EncodingT>(nativeName,
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
shared_ptr< _CppFunction<EncodingT> > CppFunctionInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setValue(shared_ptr< _CppFunction<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIdentifier() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getName() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getName()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getAccessSpecifier() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getAccessSpecifier()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getReturnType() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getReturnType()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsConst() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsConst()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsVirtual() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsVirtual()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsVirtualPure() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsVirtualPure()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsStatic() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsStatic()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsOperator() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsOperator()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsDestructor() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsDestructor()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsConstructor() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsConstructor()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getIsVariadic() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsVariadic()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getSignature() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getSignature()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getStartDecBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartDecBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getLengthDecBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthDecBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getDecLineNumber() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getDecLineNumber()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getLinesCount() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLinesCount()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getComplexity() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getComplexity()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getDefLineNumber() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getDefLineNumber()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getStartDefBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartDefBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getLengthDefBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthDefBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppDeclarationFile()
{
	return shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(getValue()->getCppDeclarationFile()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppDefinitionFile()
{
	return shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(getValue()->getCppDefinitionFile()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppClass()
{
	return shared_ptr< Base<EncodingT> >( new CppClassInterpreter<EncodingT>(getValue()->getCppClass()) );
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setCppDeclarationFile(shared_ptr< Base<EncodingT> > const& cppDeclarationFile)
{
	shared_ptr< _CppFile<EncodingT> > nativeCppDeclarationFile;
	if (check_cppFile(cppDeclarationFile, nativeCppDeclarationFile))
	{
		getValue()->setCppDeclarationFile(nativeCppDeclarationFile);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setCppDefinitionFile(shared_ptr< Base<EncodingT> > const& cppDefinitionFile)
{
	shared_ptr< _CppFile<EncodingT> > nativeCppDefinitionFile;
	if (check_cppFile(cppDefinitionFile, nativeCppDefinitionFile))
	{
		getValue()->setCppDefinitionFile(nativeCppDefinitionFile);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setName(shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		getValue()->setName(nativeName);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setCppClass(shared_ptr< Base<EncodingT> > const& cppClass)
{
	shared_ptr< _CppClass<EncodingT> > nativeCppClass;
	if (check_cppClass(cppClass, nativeCppClass))
	{
		getValue()->setCppClass(nativeCppClass);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setAccessSpecifier(shared_ptr< Base<EncodingT> > const& accessSpecifier)
{
	typename EncodingT::string_t nativeAccessSpecifier;
	if (check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier))
	{
		getValue()->setAccessSpecifier(nativeAccessSpecifier);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setReturnType(shared_ptr< Base<EncodingT> > const& returnType)
{
	typename EncodingT::string_t nativeReturnType;
	if (check_string<EncodingT>(returnType, nativeReturnType))
	{
		getValue()->setReturnType(nativeReturnType);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsConst(shared_ptr< Base<EncodingT> > const& isConst)
{
	int nativeIsConst;
	if (check_numeric(isConst, nativeIsConst))
	{
		getValue()->setIsConst(nativeIsConst);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsVirtual(shared_ptr< Base<EncodingT> > const& isVirtual)
{
	int nativeIsVirtual;
	if (check_numeric(isVirtual, nativeIsVirtual))
	{
		getValue()->setIsVirtual(nativeIsVirtual);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsVirtualPure(shared_ptr< Base<EncodingT> > const& isVirtualPure)
{
	int nativeIsVirtualPure;
	if (check_numeric(isVirtualPure, nativeIsVirtualPure))
	{
		getValue()->setIsVirtualPure(nativeIsVirtualPure);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsStatic(shared_ptr< Base<EncodingT> > const& isStatic)
{
	int nativeIsStatic;
	if (check_numeric(isStatic, nativeIsStatic))
	{
		getValue()->setIsStatic(nativeIsStatic);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsOperator(shared_ptr< Base<EncodingT> > const& isOperator)
{
	int nativeIsOperator;
	if (check_numeric(isOperator, nativeIsOperator))
	{
		getValue()->setIsOperator(nativeIsOperator);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsDestructor(shared_ptr< Base<EncodingT> > const& isDestructor)
{
	int nativeIsDestructor;
	if (check_numeric(isDestructor, nativeIsDestructor))
	{
		getValue()->setIsDestructor(nativeIsDestructor);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsConstructor(shared_ptr< Base<EncodingT> > const& isConstructor)
{
	int nativeIsConstructor;
	if (check_numeric(isConstructor, nativeIsConstructor))
	{
		getValue()->setIsConstructor(nativeIsConstructor);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setIsVariadic(shared_ptr< Base<EncodingT> > const& isVariadic)
{
	int nativeIsVariadic;
	if (check_numeric(isVariadic, nativeIsVariadic))
	{
		getValue()->setIsVariadic(nativeIsVariadic);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setSignature(shared_ptr< Base<EncodingT> > const& signature)
{
	typename EncodingT::string_t nativeSignature;
	if (check_string<EncodingT>(signature, nativeSignature))
	{
		getValue()->setSignature(nativeSignature);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setStartDecBlock(shared_ptr< Base<EncodingT> > const& startDecBlock)
{
	int nativeStartDecBlock;
	if (check_numeric(startDecBlock, nativeStartDecBlock))
	{
		getValue()->setStartDecBlock(nativeStartDecBlock);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setLengthDecBlock(shared_ptr< Base<EncodingT> > const& lengthDecBlock)
{
	int nativeLengthDecBlock;
	if (check_numeric(lengthDecBlock, nativeLengthDecBlock))
	{
		getValue()->setLengthDecBlock(nativeLengthDecBlock);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setDecLineNumber(shared_ptr< Base<EncodingT> > const& decLineNumber)
{
	int nativeDecLineNumber;
	if (check_numeric(decLineNumber, nativeDecLineNumber))
	{
		getValue()->setDecLineNumber(nativeDecLineNumber);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setLinesCount(shared_ptr< Base<EncodingT> > const& linesCount)
{
	int nativeLinesCount;
	if (check_numeric(linesCount, nativeLinesCount))
	{
		getValue()->setLinesCount(nativeLinesCount);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setComplexity(shared_ptr< Base<EncodingT> > const& complexity)
{
	int nativeComplexity;
	if (check_numeric(complexity, nativeComplexity))
	{
		getValue()->setComplexity(nativeComplexity);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setDefLineNumber(shared_ptr< Base<EncodingT> > const& defLineNumber)
{
	int nativeDefLineNumber;
	if (check_numeric(defLineNumber, nativeDefLineNumber))
	{
		getValue()->setDefLineNumber(nativeDefLineNumber);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setStartDefBlock(shared_ptr< Base<EncodingT> > const& startDefBlock)
{
	int nativeStartDefBlock;
	if (check_numeric(startDefBlock, nativeStartDefBlock))
	{
		getValue()->setStartDefBlock(nativeStartDefBlock);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::setLengthDefBlock(shared_ptr< Base<EncodingT> > const& lengthDefBlock)
{
	int nativeLengthDefBlock;
	if (check_numeric(lengthDefBlock, nativeLengthDefBlock))
	{
		getValue()->setLengthDefBlock(nativeLengthDefBlock);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppDeclarationFile() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppDeclarationFile()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppDefinitionFile() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppDefinitionFile()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppClass() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppClass()) );
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
void CppFunctionInterpreter<EncodingT>::removeCppParameter(shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppParameter(getValue()->getCppParametersBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::removeCppVariable(shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppVariable(getValue()->getCppVariablesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::removeDebugFunctionInfo(shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseDebugFunctionInfo(getValue()->getDebugFunctionInfosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::insertCppParameter(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& cppParameter)
{
	int nativePosition;
	shared_ptr< _CppParameter<EncodingT> > nativeCppParameter;
	if (check_numeric(n, nativePosition) &&
		check_cppParameter(cppParameter, nativeCppParameter))
	{
		getValue()->insertCppParameter(getValue()->getCppParametersBeginning()+nativePosition, nativeCppParameter);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::insertCppVariable(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& cppVariable)
{
	int nativePosition;
	shared_ptr< _CppVariable<EncodingT> > nativeCppVariable;
	if (check_numeric(n, nativePosition) &&
		check_cppVariable(cppVariable, nativeCppVariable))
	{
		getValue()->insertCppVariable(getValue()->getCppVariablesBeginning()+nativePosition, nativeCppVariable);
	}
}


template <class EncodingT>
void CppFunctionInterpreter<EncodingT>::insertDebugFunctionInfo(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& debugFunctionInfo)
{
	int nativePosition;
	shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
	if (check_numeric(n, nativePosition) &&
		check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo))
	{
		getValue()->insertDebugFunctionInfo(getValue()->getDebugFunctionInfosBeginning()+nativePosition, nativeDebugFunctionInfo);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppParameter(shared_ptr< Base<EncodingT> > const& n)
{
	shared_ptr< Base<EncodingT> > res(new CppParameterInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppParameterInterpreter<EncodingT>(getValue()->getCppParameterAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getCppVariable(shared_ptr< Base<EncodingT> > const& n)
{
	shared_ptr< Base<EncodingT> > res(new CppVariableInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppVariableInterpreter<EncodingT>(getValue()->getCppVariableAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::getDebugFunctionInfo(shared_ptr< Base<EncodingT> > const& n)
{
	shared_ptr< Base<EncodingT> > res(new DebugFunctionInfoInterpreter<EncodingT>());
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
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppParameters() const
{
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppParametersEmpty()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasCppVariables() const
{
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppVariablesEmpty()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::hasDebugFunctionInfos() const
{
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isDebugFunctionInfosEmpty()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::cppParametersCount() const
{
	return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppParametersSize()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::cppVariablesCount() const
{
	return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppVariablesSize()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::debugFunctionInfosCount() const
{
	return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getDebugFunctionInfosSize()));
}

template <class EncodingT>
typename EncodingT::string_t CppFunctionInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new CppFunctionInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CppFunctionInterpreter<EncodingT>::getClassName() const
{
	return C("CppFunction");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFunctionInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

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
bool check_cppFunction(shared_ptr< Base<EncodingT> > const& val, shared_ptr< _CppFunction<EncodingT> >& o)
{
	shared_ptr< CppFunctionInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppFunctionInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppFunction expected, got " << A(val->getClassName());
	}
	return value;
}

template <class EncodingT>
bool reset_cppFunction(shared_ptr< Base<EncodingT> >& val, shared_ptr< _CppFunction<EncodingT> > const& o)
{
	shared_ptr< CppFunctionInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppFunctionInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppFunction expected, got " << A(val->getClassName());
	}
	return value;
}

NAMESPACE_END

#undef C
#undef A

