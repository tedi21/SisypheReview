#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppIncludeInterpreter<EncodingT>::CppIncludeInterpreter()
{
	m_value = boost::make_shared< _CppInclude<EncodingT> >();
}

template <class EncodingT>
CppIncludeInterpreter<EncodingT>::CppIncludeInterpreter(boost::shared_ptr< _CppInclude<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
CppIncludeInterpreter<EncodingT>::CppIncludeInterpreter(boost::shared_ptr< Base<EncodingT> > const& fileName,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	typename EncodingT::string_t nativeFileName;
	long long nativeLineNumber;
	if (check_string<EncodingT>(fileName, nativeFileName) &&
		check_numeric_i(lineNumber, nativeLineNumber))
	{
		m_value = boost::make_shared< _CppInclude<EncodingT> >(nativeFileName,
				nativeLineNumber);
	}
}

template <class EncodingT>
boost::shared_ptr< _CppInclude<EncodingT> > CppIncludeInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void CppIncludeInterpreter<EncodingT>::value(boost::shared_ptr< _CppInclude<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreter<EncodingT>::getFileName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getFileName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreter<EncodingT>::getCppFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(m_value->getCppFile()) );
}


template <class EncodingT>
void CppIncludeInterpreter<EncodingT>::setFileName(boost::shared_ptr< Base<EncodingT> > const& fileName)
{
	typename EncodingT::string_t nativeFileName;
	if (check_string<EncodingT>(fileName, nativeFileName))
	{
		m_value->setFileName(nativeFileName);
	}
}


template <class EncodingT>
void CppIncludeInterpreter<EncodingT>::setCppFile(boost::shared_ptr< Base<EncodingT> > const& cppFile)
{
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
	if (check_cppFile(cppFile, nativeCppFile))
	{
		m_value->setCppFile(nativeCppFile);
	}
}


template <class EncodingT>
void CppIncludeInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	long long nativeLineNumber;
	if (check_numeric_i(lineNumber, nativeLineNumber))
	{
		m_value->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreter<EncodingT>::hasCppFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppFile()) );
}


template <class EncodingT>
void CppIncludeInterpreter<EncodingT>::removeCppFile()
{
	m_value->eraseCppFile();
}

template <class EncodingT>
typename EncodingT::string_t CppIncludeInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppIncludeInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t CppIncludeInterpreter<EncodingT>::getClassName() const
{
	return C("CppInclude");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppInclude"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppInclude, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppInclude(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppInclude<EncodingT> >& o)
{
	boost::shared_ptr< CppIncludeInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppIncludeInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppInclude expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cppInclude(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppInclude<EncodingT> > const& o)
{
	boost::shared_ptr< CppIncludeInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppIncludeInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppInclude expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

