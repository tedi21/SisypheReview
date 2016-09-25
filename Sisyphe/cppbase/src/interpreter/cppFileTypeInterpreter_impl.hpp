#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppFileTypeInterpreter<EncodingT>::CppFileTypeInterpreter()
{
	setValue( boost::shared_ptr< _CppFileType<EncodingT> > (new _CppFileType<EncodingT>()) );
}

template <class EncodingT>
CppFileTypeInterpreter<EncodingT>::CppFileTypeInterpreter(boost::shared_ptr< _CppFileType<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CppFileTypeInterpreter<EncodingT>::CppFileTypeInterpreter(boost::shared_ptr< Base<EncodingT> > const& string)
{
	typename EncodingT::string_t nativeString;
	if (check_string<EncodingT>(string, nativeString))
	{
		setValue(boost::shared_ptr< _CppFileType<EncodingT> >(new _CppFileType<EncodingT>(nativeString)));
	}
}

template <class EncodingT>
CppFileTypeInterpreter<EncodingT>::~CppFileTypeInterpreter()
{}

template <class EncodingT>
boost::shared_ptr< _CppFileType<EncodingT> > CppFileTypeInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppFileTypeInterpreter<EncodingT>::setValue(boost::shared_ptr< _CppFileType<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::getString() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getString()) );
}


template <class EncodingT>
void CppFileTypeInterpreter<EncodingT>::setString(boost::shared_ptr< Base<EncodingT> > const& string)
{
	typename EncodingT::string_t nativeString;
	if (check_string<EncodingT>(string, nativeString))
	{
		getValue()->setString(nativeString);
	}
}


template <class EncodingT>
void CppFileTypeInterpreter<EncodingT>::removeCppFile(boost::shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppFile(getValue()->getCppFilesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileTypeInterpreter<EncodingT>::insertCppFile(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppFile)
{
	int nativePosition;
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
	if (check_numeric(n, nativePosition) &&
		check_cppFile(cppFile, nativeCppFile))
	{
		getValue()->insertCppFile(getValue()->getCppFilesBeginning()+nativePosition, nativeCppFile);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::getCppFile(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppFileInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppFileInterpreter<EncodingT>(getValue()->getCppFileAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void CppFileTypeInterpreter<EncodingT>::clearCppFiles()
{
	getValue()->clearCppFiles();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::hasCppFiles() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppFilesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::cppFilesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppFilesSize()));
}

template <class EncodingT>
typename EncodingT::string_t CppFileTypeInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppFileTypeInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CppFileTypeInterpreter<EncodingT>::getClassName() const
{
	return C("CppFileType");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileTypeInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppFileType"), method, args, ret) ||
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
		o = value->getValue();
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
		value->setValue(o);
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

