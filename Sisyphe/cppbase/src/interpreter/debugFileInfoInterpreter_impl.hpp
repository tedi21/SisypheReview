#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugFileInfoInterpreter<EncodingT>::DebugFileInfoInterpreter()
{
	setValue( boost::shared_ptr< _DebugFileInfo<EncodingT> > (new _DebugFileInfo<EncodingT>()) );
}

template <class EncodingT>
DebugFileInfoInterpreter<EncodingT>::DebugFileInfoInterpreter(boost::shared_ptr< _DebugFileInfo<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
DebugFileInfoInterpreter<EncodingT>::DebugFileInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& compilandPath,
				boost::shared_ptr< Base<EncodingT> > const& checksum)
{
	typename EncodingT::string_t nativeCompilandPath;
	boost::container::vector<unsigned char> nativeChecksum;
	if (check_string<EncodingT>(compilandPath, nativeCompilandPath) &&
		check_numeric_array(checksum, nativeChecksum))
	{
		setValue(boost::shared_ptr< _DebugFileInfo<EncodingT> >(new _DebugFileInfo<EncodingT>(nativeCompilandPath,
				nativeChecksum)));
	}
}

template <class EncodingT>
DebugFileInfoInterpreter<EncodingT>::~DebugFileInfoInterpreter()
{}

template <class EncodingT>
boost::shared_ptr< _DebugFileInfo<EncodingT> > DebugFileInfoInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::setValue(boost::shared_ptr< _DebugFileInfo<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::getCompilandPath() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getCompilandPath()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::getChecksum() const
{
	return convert_numeric_array<EncodingT>(getValue()->getChecksum());
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::getCppFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(getValue()->getCppFile()) );
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::setCompilandPath(boost::shared_ptr< Base<EncodingT> > const& compilandPath)
{
	typename EncodingT::string_t nativeCompilandPath;
	if (check_string<EncodingT>(compilandPath, nativeCompilandPath))
	{
		getValue()->setCompilandPath(nativeCompilandPath);
	}
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::setChecksum(boost::shared_ptr< Base<EncodingT> > const& checksum)
{
	boost::container::vector<unsigned char> nativeChecksum;
	if (check_numeric_array(checksum, nativeChecksum))
	{
		getValue()->setChecksum(nativeChecksum);
	}
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::setCppFile(boost::shared_ptr< Base<EncodingT> > const& cppFile)
{
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
	if (check_cppFile(cppFile, nativeCppFile))
	{
		getValue()->setCppFile(nativeCppFile);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::hasCppFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppFile()) );
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::removeCppFile()
{
	getValue()->eraseCppFile();
}

template <class EncodingT>
typename EncodingT::string_t DebugFileInfoInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugFileInfoInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t DebugFileInfoInterpreter<EncodingT>::getClassName() const
{
	return C("DebugFileInfo");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("DebugFileInfo"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugFileInfo, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_debugFileInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugFileInfo<EncodingT> >& o)
{
	boost::shared_ptr< DebugFileInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugFileInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugFileInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_debugFileInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugFileInfo<EncodingT> > const& o)
{
	boost::shared_ptr< DebugFileInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugFileInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugFileInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

