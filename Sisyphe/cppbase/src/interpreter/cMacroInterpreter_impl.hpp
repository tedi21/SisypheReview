#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CMacroInterpreter<EncodingT>::CMacroInterpreter()
{
	m_value = boost::make_shared< _CMacro<EncodingT> >();
}

template <class EncodingT>
CMacroInterpreter<EncodingT>::CMacroInterpreter(boost::shared_ptr< _CMacro<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
CMacroInterpreter<EncodingT>::CMacroInterpreter(boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& isConst,
				boost::shared_ptr< Base<EncodingT> > const& constValue,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	typename EncodingT::string_t nativeName;
	long long nativeIsConst;
	typename EncodingT::string_t nativeConstValue;
	long long nativeLineNumber;
	long long nativeStartBlock;
	long long nativeLengthBlock;
	if (check_string<EncodingT>(name, nativeName) &&
		check_numeric_i(isConst, nativeIsConst) &&
		check_string<EncodingT>(constValue, nativeConstValue) &&
		check_numeric_i(lineNumber, nativeLineNumber) &&
		check_numeric_i(startBlock, nativeStartBlock) &&
		check_numeric_i(lengthBlock, nativeLengthBlock))
	{
		m_value = boost::make_shared< _CMacro<EncodingT> >(nativeName,
				nativeIsConst,
				nativeConstValue,
				nativeLineNumber,
				nativeStartBlock,
				nativeLengthBlock);
	}
}

template <class EncodingT>
boost::shared_ptr< _CMacro<EncodingT> > CMacroInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void CMacroInterpreter<EncodingT>::value(boost::shared_ptr< _CMacro<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getIsConst() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsConst()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getConstValue() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getConstValue()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getStartBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getStartBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getLengthBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLengthBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getCppFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(m_value->getCppFile()) );
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		m_value->setName(nativeName);
	}
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst)
{
	long long nativeIsConst;
	if (check_numeric_i(isConst, nativeIsConst))
	{
		m_value->setIsConst(nativeIsConst);
	}
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setConstValue(boost::shared_ptr< Base<EncodingT> > const& constValue)
{
	typename EncodingT::string_t nativeConstValue;
	if (check_string<EncodingT>(constValue, nativeConstValue))
	{
		m_value->setConstValue(nativeConstValue);
	}
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setCppFile(boost::shared_ptr< Base<EncodingT> > const& cppFile)
{
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
	if (check_cppFile(cppFile, nativeCppFile))
	{
		m_value->setCppFile(nativeCppFile);
	}
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	long long nativeLineNumber;
	if (check_numeric_i(lineNumber, nativeLineNumber))
	{
		m_value->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock)
{
	long long nativeStartBlock;
	if (check_numeric_i(startBlock, nativeStartBlock))
	{
		m_value->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	long long nativeLengthBlock;
	if (check_numeric_i(lengthBlock, nativeLengthBlock))
	{
		m_value->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::hasCppFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppFile()) );
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::removeCppFile()
{
	m_value->eraseCppFile();
}

template <class EncodingT>
typename EncodingT::string_t CMacroInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CMacroInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t CMacroInterpreter<EncodingT>::getClassName() const
{
	return C("CMacro");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CMacro"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CMacro, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cMacro(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CMacro<EncodingT> >& o)
{
	boost::shared_ptr< CMacroInterpreter<EncodingT> > value  = dynamic_pointer_cast< CMacroInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CMacro expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cMacro(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CMacro<EncodingT> > const& o)
{
	boost::shared_ptr< CMacroInterpreter<EncodingT> > value  = dynamic_pointer_cast< CMacroInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CMacro expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

