#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppVariableInterpreter<EncodingT>::CppVariableInterpreter()
{
	m_value = boost::make_shared< _CppVariable<EncodingT> >();
}

template <class EncodingT>
CppVariableInterpreter<EncodingT>::CppVariableInterpreter(boost::shared_ptr< _CppVariable<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
CppVariableInterpreter<EncodingT>::CppVariableInterpreter(boost::shared_ptr< Base<EncodingT> > const& varType,
				boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& isStatic,
				boost::shared_ptr< Base<EncodingT> > const& isConst,
				boost::shared_ptr< Base<EncodingT> > const& isConstexpr,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	typename EncodingT::string_t nativeVarType;
	typename EncodingT::string_t nativeName;
	long long nativeIsStatic;
	long long nativeIsConst;
	long long nativeIsConstexpr;
	long long nativeLineNumber;
	long long nativeStartBlock;
	long long nativeLengthBlock;
	if (check_string<EncodingT>(varType, nativeVarType) &&
		check_string<EncodingT>(name, nativeName) &&
		check_numeric_i(isStatic, nativeIsStatic) &&
		check_numeric_i(isConst, nativeIsConst) &&
		check_numeric_i(isConstexpr, nativeIsConstexpr) &&
		check_numeric_i(lineNumber, nativeLineNumber) &&
		check_numeric_i(startBlock, nativeStartBlock) &&
		check_numeric_i(lengthBlock, nativeLengthBlock))
	{
		m_value = boost::make_shared< _CppVariable<EncodingT> >(nativeVarType,
				nativeName,
				nativeIsStatic,
				nativeIsConst,
				nativeIsConstexpr,
				nativeLineNumber,
				nativeStartBlock,
				nativeLengthBlock);
	}
}

template <class EncodingT>
boost::shared_ptr< _CppVariable<EncodingT> > CppVariableInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void CppVariableInterpreter<EncodingT>::value(boost::shared_ptr< _CppVariable<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getVarType() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getVarType()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getIsStatic() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsStatic()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getIsConst() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsConst()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getIsConstexpr() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsConstexpr()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getStartBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getStartBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getLengthBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLengthBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getCppFunction()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFunctionInterpreter<EncodingT>(m_value->getCppFunction()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::getCppFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(m_value->getCppFile()) );
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setVarType(boost::shared_ptr< Base<EncodingT> > const& varType)
{
	typename EncodingT::string_t nativeVarType;
	if (check_string<EncodingT>(varType, nativeVarType))
	{
		m_value->setVarType(nativeVarType);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		m_value->setName(nativeName);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setIsStatic(boost::shared_ptr< Base<EncodingT> > const& isStatic)
{
	long long nativeIsStatic;
	if (check_numeric_i(isStatic, nativeIsStatic))
	{
		m_value->setIsStatic(nativeIsStatic);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst)
{
	long long nativeIsConst;
	if (check_numeric_i(isConst, nativeIsConst))
	{
		m_value->setIsConst(nativeIsConst);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setIsConstexpr(boost::shared_ptr< Base<EncodingT> > const& isConstexpr)
{
	long long nativeIsConstexpr;
	if (check_numeric_i(isConstexpr, nativeIsConstexpr))
	{
		m_value->setIsConstexpr(nativeIsConstexpr);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setCppFunction(boost::shared_ptr< Base<EncodingT> > const& cppFunction)
{
	boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
	if (check_cppFunction(cppFunction, nativeCppFunction))
	{
		m_value->setCppFunction(nativeCppFunction);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	long long nativeLineNumber;
	if (check_numeric_i(lineNumber, nativeLineNumber))
	{
		m_value->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock)
{
	long long nativeStartBlock;
	if (check_numeric_i(startBlock, nativeStartBlock))
	{
		m_value->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	long long nativeLengthBlock;
	if (check_numeric_i(lengthBlock, nativeLengthBlock))
	{
		m_value->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::setCppFile(boost::shared_ptr< Base<EncodingT> > const& cppFile)
{
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
	if (check_cppFile(cppFile, nativeCppFile))
	{
		m_value->setCppFile(nativeCppFile);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::hasCppFunction() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppFunction()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::hasCppFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppFile()) );
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::removeCppFunction()
{
	m_value->eraseCppFunction();
}


template <class EncodingT>
void CppVariableInterpreter<EncodingT>::removeCppFile()
{
	m_value->eraseCppFile();
}

template <class EncodingT>
typename EncodingT::string_t CppVariableInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppVariableInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppVariableInterpreter<EncodingT>(copy_ptr(m_value)));
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
		o = value->value();
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
		value->value(o);
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

