#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppFileTypeInterpreter<EncodingT>::CppFileTypeInterpreter()
{
	m_value = boost::make_shared< _CppFileType<EncodingT> >();
}

template <class EncodingT>
CppFileTypeInterpreter<EncodingT>::CppFileTypeInterpreter(boost::shared_ptr< _CppFileType<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
CppFileTypeInterpreter<EncodingT>::CppFileTypeInterpreter(boost::shared_ptr< Base<EncodingT> > const& string)
{
	typename EncodingT::string_t nativeString;
	if (check_string<EncodingT>(string, nativeString))
	{
		m_value = boost::make_shared< _CppFileType<EncodingT> >(nativeString);
	}
}

template <class EncodingT>
boost::shared_ptr< _CppFileType<EncodingT> > CppFileTypeInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void CppFileTypeInterpreter<EncodingT>::value(boost::shared_ptr< _CppFileType<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::getString() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getString()) );
}


template <class EncodingT>
void CppFileTypeInterpreter<EncodingT>::setString(boost::shared_ptr< Base<EncodingT> > const& string)
{
	typename EncodingT::string_t nativeString;
	if (check_string<EncodingT>(string, nativeString))
	{
		m_value->setString(nativeString);
	}
}


template <class EncodingT>
void CppFileTypeInterpreter<EncodingT>::removeCppFile(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppFile(m_value->getCppFilesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileTypeInterpreter<EncodingT>::insertCppFile(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppFile)
{
	size_t nativePosition;
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
	if (check_numeric_i(n, nativePosition) &&
		check_cppFile(cppFile, nativeCppFile))
	{
		m_value->insertCppFile(m_value->getCppFilesBeginning()+nativePosition, nativeCppFile);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::getCppFile(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppFileInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new CppFileInterpreter<EncodingT>(m_value->getCppFileAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void CppFileTypeInterpreter<EncodingT>::clearCppFiles()
{
	m_value->clearCppFiles();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::hasCppFiles() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppFilesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::cppFilesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppFilesSize()));
}

template <class EncodingT>
typename EncodingT::string_t CppFileTypeInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppFileTypeInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t CppFileTypeInterpreter<EncodingT>::getClassName() const
{
	return UCS("CppFileType");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("CppFileType"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppFileType, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppFileType(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppFileType<EncodingT> >& o)
{
	boost::shared_ptr< CppFileTypeInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppFileTypeInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppFileType expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cppFileType(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppFileType<EncodingT> > const& o)
{
	boost::shared_ptr< CppFileTypeInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppFileTypeInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppFileType expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

