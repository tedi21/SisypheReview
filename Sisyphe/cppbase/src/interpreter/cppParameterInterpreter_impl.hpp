#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppParameterInterpreter<EncodingT>::CppParameterInterpreter()
{
	m_value = boost::make_shared< _CppParameter<EncodingT> >();
}

template <class EncodingT>
CppParameterInterpreter<EncodingT>::CppParameterInterpreter(boost::shared_ptr< _CppParameter<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
CppParameterInterpreter<EncodingT>::CppParameterInterpreter(boost::shared_ptr< Base<EncodingT> > const& paramOrder,
				boost::shared_ptr< Base<EncodingT> > const& paramType,
				boost::shared_ptr< Base<EncodingT> > const& isConst,
				boost::shared_ptr< Base<EncodingT> > const& defaultValue,
				boost::shared_ptr< Base<EncodingT> > const& decName,
				boost::shared_ptr< Base<EncodingT> > const& decLineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startDecBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthDecBlock,
				boost::shared_ptr< Base<EncodingT> > const& defName,
				boost::shared_ptr< Base<EncodingT> > const& defLineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startDefBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthDefBlock)
{
	long long nativeParamOrder;
	typename EncodingT::string_t nativeParamType;
	long long nativeIsConst;
	typename EncodingT::string_t nativeDefaultValue;
	typename EncodingT::string_t nativeDecName;
	long long nativeDecLineNumber;
	long long nativeStartDecBlock;
	long long nativeLengthDecBlock;
	typename EncodingT::string_t nativeDefName;
	long long nativeDefLineNumber;
	long long nativeStartDefBlock;
	long long nativeLengthDefBlock;
	if (check_numeric_i(paramOrder, nativeParamOrder) &&
		check_string<EncodingT>(paramType, nativeParamType) &&
		check_numeric_i(isConst, nativeIsConst) &&
		check_string<EncodingT>(defaultValue, nativeDefaultValue) &&
		check_string<EncodingT>(decName, nativeDecName) &&
		check_numeric_i(decLineNumber, nativeDecLineNumber) &&
		check_numeric_i(startDecBlock, nativeStartDecBlock) &&
		check_numeric_i(lengthDecBlock, nativeLengthDecBlock) &&
		check_string<EncodingT>(defName, nativeDefName) &&
		check_numeric_i(defLineNumber, nativeDefLineNumber) &&
		check_numeric_i(startDefBlock, nativeStartDefBlock) &&
		check_numeric_i(lengthDefBlock, nativeLengthDefBlock))
	{
		m_value = boost::make_shared< _CppParameter<EncodingT> >(nativeParamOrder,
				nativeParamType,
				nativeIsConst,
				nativeDefaultValue,
				nativeDecName,
				nativeDecLineNumber,
				nativeStartDecBlock,
				nativeLengthDecBlock,
				nativeDefName,
				nativeDefLineNumber,
				nativeStartDefBlock,
				nativeLengthDefBlock);
	}
}

template <class EncodingT>
boost::shared_ptr< _CppParameter<EncodingT> > CppParameterInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void CppParameterInterpreter<EncodingT>::value(boost::shared_ptr< _CppParameter<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getParamOrder() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getParamOrder()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getParamType() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getParamType()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getIsConst() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsConst()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getDefaultValue() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getDefaultValue()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getDecName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getDecName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getDecLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getDecLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getStartDecBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getStartDecBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getLengthDecBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLengthDecBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getDefName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getDefName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getDefLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getDefLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getStartDefBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getStartDefBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getLengthDefBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLengthDefBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getCppFunction()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFunctionInterpreter<EncodingT>(m_value->getCppFunction()) );
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setParamOrder(boost::shared_ptr< Base<EncodingT> > const& paramOrder)
{
	long long nativeParamOrder;
	if (check_numeric_i(paramOrder, nativeParamOrder))
	{
		m_value->setParamOrder(nativeParamOrder);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setParamType(boost::shared_ptr< Base<EncodingT> > const& paramType)
{
	typename EncodingT::string_t nativeParamType;
	if (check_string<EncodingT>(paramType, nativeParamType))
	{
		m_value->setParamType(nativeParamType);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst)
{
	long long nativeIsConst;
	if (check_numeric_i(isConst, nativeIsConst))
	{
		m_value->setIsConst(nativeIsConst);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setDefaultValue(boost::shared_ptr< Base<EncodingT> > const& defaultValue)
{
	typename EncodingT::string_t nativeDefaultValue;
	if (check_string<EncodingT>(defaultValue, nativeDefaultValue))
	{
		m_value->setDefaultValue(nativeDefaultValue);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setCppFunction(boost::shared_ptr< Base<EncodingT> > const& cppFunction)
{
	boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
	if (check_cppFunction(cppFunction, nativeCppFunction))
	{
		m_value->setCppFunction(nativeCppFunction);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setDecName(boost::shared_ptr< Base<EncodingT> > const& decName)
{
	typename EncodingT::string_t nativeDecName;
	if (check_string<EncodingT>(decName, nativeDecName))
	{
		m_value->setDecName(nativeDecName);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setDecLineNumber(boost::shared_ptr< Base<EncodingT> > const& decLineNumber)
{
	long long nativeDecLineNumber;
	if (check_numeric_i(decLineNumber, nativeDecLineNumber))
	{
		m_value->setDecLineNumber(nativeDecLineNumber);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setStartDecBlock(boost::shared_ptr< Base<EncodingT> > const& startDecBlock)
{
	long long nativeStartDecBlock;
	if (check_numeric_i(startDecBlock, nativeStartDecBlock))
	{
		m_value->setStartDecBlock(nativeStartDecBlock);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setLengthDecBlock(boost::shared_ptr< Base<EncodingT> > const& lengthDecBlock)
{
	long long nativeLengthDecBlock;
	if (check_numeric_i(lengthDecBlock, nativeLengthDecBlock))
	{
		m_value->setLengthDecBlock(nativeLengthDecBlock);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setDefName(boost::shared_ptr< Base<EncodingT> > const& defName)
{
	typename EncodingT::string_t nativeDefName;
	if (check_string<EncodingT>(defName, nativeDefName))
	{
		m_value->setDefName(nativeDefName);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setDefLineNumber(boost::shared_ptr< Base<EncodingT> > const& defLineNumber)
{
	long long nativeDefLineNumber;
	if (check_numeric_i(defLineNumber, nativeDefLineNumber))
	{
		m_value->setDefLineNumber(nativeDefLineNumber);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setStartDefBlock(boost::shared_ptr< Base<EncodingT> > const& startDefBlock)
{
	long long nativeStartDefBlock;
	if (check_numeric_i(startDefBlock, nativeStartDefBlock))
	{
		m_value->setStartDefBlock(nativeStartDefBlock);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setLengthDefBlock(boost::shared_ptr< Base<EncodingT> > const& lengthDefBlock)
{
	long long nativeLengthDefBlock;
	if (check_numeric_i(lengthDefBlock, nativeLengthDefBlock))
	{
		m_value->setLengthDefBlock(nativeLengthDefBlock);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::hasCppFunction() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppFunction()) );
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::removeCppFunction()
{
	m_value->eraseCppFunction();
}

template <class EncodingT>
typename EncodingT::string_t CppParameterInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppParameterInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t CppParameterInterpreter<EncodingT>::getClassName() const
{
	return C("CppParameter");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppParameter"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppParameter, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppParameter(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppParameter<EncodingT> >& o)
{
	boost::shared_ptr< CppParameterInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppParameterInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppParameter expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cppParameter(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppParameter<EncodingT> > const& o)
{
	boost::shared_ptr< CppParameterInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppParameterInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppParameter expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

