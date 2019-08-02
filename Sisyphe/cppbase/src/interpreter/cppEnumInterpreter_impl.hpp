#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppEnumInterpreter<EncodingT>::CppEnumInterpreter()
{
	m_value = boost::make_shared< _CppEnum<EncodingT> >();
}

template <class EncodingT>
CppEnumInterpreter<EncodingT>::CppEnumInterpreter(boost::shared_ptr< _CppEnum<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
CppEnumInterpreter<EncodingT>::CppEnumInterpreter(boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& accessSpecifier,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	typename EncodingT::string_t nativeName;
	typename EncodingT::string_t nativeAccessSpecifier;
	long long nativeLineNumber;
	long long nativeStartBlock;
	long long nativeLengthBlock;
	if (check_string<EncodingT>(name, nativeName) &&
		check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier) &&
		check_numeric_i(lineNumber, nativeLineNumber) &&
		check_numeric_i(startBlock, nativeStartBlock) &&
		check_numeric_i(lengthBlock, nativeLengthBlock))
	{
		m_value = boost::make_shared< _CppEnum<EncodingT> >(nativeName,
				nativeAccessSpecifier,
				nativeLineNumber,
				nativeStartBlock,
				nativeLengthBlock);
	}
}

template <class EncodingT>
boost::shared_ptr< _CppEnum<EncodingT> > CppEnumInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void CppEnumInterpreter<EncodingT>::value(boost::shared_ptr< _CppEnum<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getAccessSpecifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getAccessSpecifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getStartBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getStartBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getLengthBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLengthBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getCppFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(m_value->getCppFile()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getCppClass()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppClassInterpreter<EncodingT>(m_value->getCppClass()) );
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		m_value->setName(nativeName);
	}
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::setCppFile(boost::shared_ptr< Base<EncodingT> > const& cppFile)
{
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
	if (check_cppFile(cppFile, nativeCppFile))
	{
		m_value->setCppFile(nativeCppFile);
	}
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::setCppClass(boost::shared_ptr< Base<EncodingT> > const& cppClass)
{
	boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
	if (check_cppClass(cppClass, nativeCppClass))
	{
		m_value->setCppClass(nativeCppClass);
	}
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::setAccessSpecifier(boost::shared_ptr< Base<EncodingT> > const& accessSpecifier)
{
	typename EncodingT::string_t nativeAccessSpecifier;
	if (check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier))
	{
		m_value->setAccessSpecifier(nativeAccessSpecifier);
	}
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	long long nativeLineNumber;
	if (check_numeric_i(lineNumber, nativeLineNumber))
	{
		m_value->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock)
{
	long long nativeStartBlock;
	if (check_numeric_i(startBlock, nativeStartBlock))
	{
		m_value->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	long long nativeLengthBlock;
	if (check_numeric_i(lengthBlock, nativeLengthBlock))
	{
		m_value->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::hasCppFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppFile()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::hasCppClass() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppClass()) );
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::removeCppFile()
{
	m_value->eraseCppFile();
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::removeCppClass()
{
	m_value->eraseCppClass();
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::removeCppEnumConstant(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppEnumConstant(m_value->getCppEnumConstantsBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::insertCppEnumConstant(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppEnumConstant)
{
	size_t nativePosition;
	boost::shared_ptr< _CppEnumConstant<EncodingT> > nativeCppEnumConstant;
	if (check_numeric_i(n, nativePosition) &&
		check_cppEnumConstant(cppEnumConstant, nativeCppEnumConstant))
	{
		m_value->insertCppEnumConstant(m_value->getCppEnumConstantsBeginning()+nativePosition, nativeCppEnumConstant);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getCppEnumConstant(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppEnumConstantInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new CppEnumConstantInterpreter<EncodingT>(m_value->getCppEnumConstantAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::clearCppEnumConstants()
{
	m_value->clearCppEnumConstants();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::hasCppEnumConstants() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppEnumConstantsEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::cppEnumConstantsCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppEnumConstantsSize()));
}

template <class EncodingT>
typename EncodingT::string_t CppEnumInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppEnumInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t CppEnumInterpreter<EncodingT>::getClassName() const
{
	return UCS("CppEnum");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("CppEnum"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppEnum, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppEnum(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppEnum<EncodingT> >& o)
{
	boost::shared_ptr< CppEnumInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppEnumInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppEnum expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cppEnum(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppEnum<EncodingT> > const& o)
{
	boost::shared_ptr< CppEnumInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppEnumInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppEnum expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

