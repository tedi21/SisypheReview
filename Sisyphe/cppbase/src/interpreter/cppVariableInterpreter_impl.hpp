#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppVariableInterpreter<EncodingT>::CppVariableInterpreter()
{
	setValue( boost::shared_ptr< _CppVariable<EncodingT> > (new _CppVariable<EncodingT>()) );
}

template <class EncodingT>
CppVariableInterpreter<EncodingT>::CppVariableInterpreter(boost::shared_ptr< _CppVariable<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CppVariableInterpreter<EncodingT>::CppVariableInterpreter(boost::shared_ptr< Base<EncodingT> > const& varType,
				boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& isStatic,
				boost::shared_ptr< Base<EncodingT> > const& isConst,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	typename EncodingT::string_t nativeVarType;
	typename EncodingT::string_t nativeName;
	int nativeIsStatic;
	int nativeIsConst;
	int nativeLineNumber;
	int nativeStartBlock;
	int nativeLengthBlock;
	if (check_string<EncodingT>(varType, nativeVarType) &&
		check_string<EncodingT>(name, nativeName) &&
		check_numeric(isStatic, nativeIsStatic) &&
		check_numeric(isConst, nativeIsConst) &&
		check_numeric(lineNumber, nativeLineNumber) &&
		check_numeric(startBlock, nativeStartBlock) &&
		check_numeric(lengthBlock, nativeLengthBlock))
	{
		setValue(boost::shared_ptr< _CppVariable<EncodingT> >(new _CppVariable<EncodingT>(nativeVarType,
				nativeName,
				nativeIsStatic,
				nativeIsConst,
				nativeLineNumber,
				nativeStartBlock,
				nativeLengthBlock)));
	}
}

template <class EncodingT>
CppVariableInterpreter<EncodingT>::~CppVariableInterpreter()
{}

template <class EncodingT>
boost::shared_ptr< _CppVariable<EncodingT> > CppVariableInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setValue(boost::shared_ptr< _CppVariable<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getVarType() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getVarType()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getIsStatic() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsStatic()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getIsConst() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsConst()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getStartBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getLengthBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getCppFunction()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFunctionInterpreter<EncodingT>(getValue()->getCppFunction()) );
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setVarType(boost::shared_ptr< Base<EncodingT> > const& varType)
{
	typename EncodingT::string_t nativeVarType;
	if (check_string<EncodingT>(varType, nativeVarType))
	{
		getValue()->setVarType(nativeVarType);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		getValue()->setName(nativeName);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setIsStatic(boost::shared_ptr< Base<EncodingT> > const& isStatic)
{
	int nativeIsStatic;
	if (check_numeric(isStatic, nativeIsStatic))
	{
		getValue()->setIsStatic(nativeIsStatic);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst)
{
	int nativeIsConst;
	if (check_numeric(isConst, nativeIsConst))
	{
		getValue()->setIsConst(nativeIsConst);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setCppFunction(boost::shared_ptr< Base<EncodingT> > const& cppFunction)
{
	boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
	if (check_cppFunction(cppFunction, nativeCppFunction))
	{
		getValue()->setCppFunction(nativeCppFunction);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	int nativeLineNumber;
	if (check_numeric(lineNumber, nativeLineNumber))
	{
		getValue()->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock)
{
	int nativeStartBlock;
	if (check_numeric(startBlock, nativeStartBlock))
	{
		getValue()->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	int nativeLengthBlock;
	if (check_numeric(lengthBlock, nativeLengthBlock))
	{
		getValue()->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::hasCppFunction() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppFunction()) );
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::removeCppFunction()
{
	getValue()->eraseCppFunction();
}

template <class EncodingT>
typename EncodingT::string_t CppVariableInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppVariableInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CppVariableInterpreter<EncodingT>::getClassName() const
{
	return C("CppVariable");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppVariable"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppVariable, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppVariable(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppVariable<EncodingT> >& o)
{
	boost::shared_ptr< CppVariableInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppVariableInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppVariable expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cppVariable(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppVariable<EncodingT> > const& o)
{
	boost::shared_ptr< CppVariableInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppVariableInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppVariable expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

