#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppEnumConstantInterpreter<EncodingT>::CppEnumConstantInterpreter()
{
	m_value = boost::make_shared< _CppEnumConstant<EncodingT> >();
}

template <class EncodingT>
CppEnumConstantInterpreter<EncodingT>::CppEnumConstantInterpreter(boost::shared_ptr< _CppEnumConstant<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
CppEnumConstantInterpreter<EncodingT>::CppEnumConstantInterpreter(boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& defaultValue,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	typename EncodingT::string_t nativeName;
	long long nativeDefaultValue;
	long long nativeLineNumber;
	long long nativeStartBlock;
	long long nativeLengthBlock;
	if (check_string<EncodingT>(name, nativeName) &&
		check_numeric_i(defaultValue, nativeDefaultValue) &&
		check_numeric_i(lineNumber, nativeLineNumber) &&
		check_numeric_i(startBlock, nativeStartBlock) &&
		check_numeric_i(lengthBlock, nativeLengthBlock))
	{
		m_value = boost::make_shared< _CppEnumConstant<EncodingT> >(nativeName,
				nativeDefaultValue,
				nativeLineNumber,
				nativeStartBlock,
				nativeLengthBlock);
	}
}

template <class EncodingT>
boost::shared_ptr< _CppEnumConstant<EncodingT> > CppEnumConstantInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::value(boost::shared_ptr< _CppEnumConstant<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getDefaultValue() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getDefaultValue()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getStartBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getStartBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getLengthBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLengthBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getCppEnum()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppEnumInterpreter<EncodingT>(m_value->getCppEnum()) );
}


template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		m_value->setName(nativeName);
	}
}


template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::setDefaultValue(boost::shared_ptr< Base<EncodingT> > const& defaultValue)
{
	long long nativeDefaultValue;
	if (check_numeric_i(defaultValue, nativeDefaultValue))
	{
		m_value->setDefaultValue(nativeDefaultValue);
	}
}


template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::setCppEnum(boost::shared_ptr< Base<EncodingT> > const& cppEnum)
{
	boost::shared_ptr< _CppEnum<EncodingT> > nativeCppEnum;
	if (check_cppEnum(cppEnum, nativeCppEnum))
	{
		m_value->setCppEnum(nativeCppEnum);
	}
}


template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	long long nativeLineNumber;
	if (check_numeric_i(lineNumber, nativeLineNumber))
	{
		m_value->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock)
{
	long long nativeStartBlock;
	if (check_numeric_i(startBlock, nativeStartBlock))
	{
		m_value->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	long long nativeLengthBlock;
	if (check_numeric_i(lengthBlock, nativeLengthBlock))
	{
		m_value->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::hasCppEnum() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppEnum()) );
}


template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::removeCppEnum()
{
	m_value->eraseCppEnum();
}

template <class EncodingT>
typename EncodingT::string_t CppEnumConstantInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppEnumConstantInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t CppEnumConstantInterpreter<EncodingT>::getClassName() const
{
	return C("CppEnumConstant");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppEnumConstant"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppEnumConstant, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppEnumConstant(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppEnumConstant<EncodingT> >& o)
{
	boost::shared_ptr< CppEnumConstantInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppEnumConstantInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppEnumConstant expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cppEnumConstant(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppEnumConstant<EncodingT> > const& o)
{
	boost::shared_ptr< CppEnumConstantInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppEnumConstantInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppEnumConstant expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

