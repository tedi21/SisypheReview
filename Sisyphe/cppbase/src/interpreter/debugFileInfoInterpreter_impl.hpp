#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugFileInfoInterpreter<EncodingT>::DebugFileInfoInterpreter()
{
	m_value = boost::make_shared< _DebugFileInfo<EncodingT> >();
}

template <class EncodingT>
DebugFileInfoInterpreter<EncodingT>::DebugFileInfoInterpreter(boost::shared_ptr< _DebugFileInfo<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
DebugFileInfoInterpreter<EncodingT>::DebugFileInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& compilandPath,
				boost::shared_ptr< Base<EncodingT> > const& checksum)
{
	typename EncodingT::string_t nativeName;
	typename EncodingT::string_t nativeCompilandPath;
	boost::container::vector<unsigned char> nativeChecksum;
	if (check_string<EncodingT>(name, nativeName) &&
		check_string<EncodingT>(compilandPath, nativeCompilandPath) &&
		check_numeric_i_array(checksum, nativeChecksum))
	{
		m_value = boost::make_shared< _DebugFileInfo<EncodingT> >(nativeName,
				nativeCompilandPath,
				nativeChecksum);
	}
}

template <class EncodingT>
boost::shared_ptr< _DebugFileInfo<EncodingT> > DebugFileInfoInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::value(boost::shared_ptr< _DebugFileInfo<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::getCompilandPath() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getCompilandPath()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::getChecksum() const
{
	return convert_numeric_array<EncodingT>(m_value->getChecksum());
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::getTextFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new TextFileInterpreter<EncodingT>(m_value->getTextFile()) );
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::setTextFile(boost::shared_ptr< Base<EncodingT> > const& textFile)
{
	boost::shared_ptr< _TextFile<EncodingT> > nativeTextFile;
	if (check_textFile(textFile, nativeTextFile))
	{
		m_value->setTextFile(nativeTextFile);
	}
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		m_value->setName(nativeName);
	}
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::setCompilandPath(boost::shared_ptr< Base<EncodingT> > const& compilandPath)
{
	typename EncodingT::string_t nativeCompilandPath;
	if (check_string<EncodingT>(compilandPath, nativeCompilandPath))
	{
		m_value->setCompilandPath(nativeCompilandPath);
	}
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::setChecksum(boost::shared_ptr< Base<EncodingT> > const& checksum)
{
	boost::container::vector<unsigned char> nativeChecksum;
	if (check_numeric_i_array(checksum, nativeChecksum))
	{
		m_value->setChecksum(nativeChecksum);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::hasTextFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullTextFile()) );
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::removeTextFile()
{
	m_value->eraseTextFile();
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::removeDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseDebugFunctionInfo(m_value->getDebugFunctionInfosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::removeDebugStubInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseDebugStubInfo(m_value->getDebugStubInfosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::insertDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugFunctionInfo)
{
	size_t nativePosition;
	boost::shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
	if (check_numeric_i(n, nativePosition) &&
		check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo))
	{
		m_value->insertDebugFunctionInfo(m_value->getDebugFunctionInfosBeginning()+nativePosition, nativeDebugFunctionInfo);
	}
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::insertDebugStubInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugStubInfo)
{
	size_t nativePosition;
	boost::shared_ptr< _DebugStubInfo<EncodingT> > nativeDebugStubInfo;
	if (check_numeric_i(n, nativePosition) &&
		check_debugStubInfo(debugStubInfo, nativeDebugStubInfo))
	{
		m_value->insertDebugStubInfo(m_value->getDebugStubInfosBeginning()+nativePosition, nativeDebugStubInfo);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::getDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugFunctionInfoInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new DebugFunctionInfoInterpreter<EncodingT>(m_value->getDebugFunctionInfoAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::getDebugStubInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugStubInfoInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new DebugStubInfoInterpreter<EncodingT>(m_value->getDebugStubInfoAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::clearDebugFunctionInfos()
{
	m_value->clearDebugFunctionInfos();
}


template <class EncodingT>
void DebugFileInfoInterpreter<EncodingT>::clearDebugStubInfos()
{
	m_value->clearDebugStubInfos();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::hasDebugFunctionInfos() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isDebugFunctionInfosEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::hasDebugStubInfos() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isDebugStubInfosEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::debugFunctionInfosCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getDebugFunctionInfosSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::debugStubInfosCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getDebugStubInfosSize()));
}

template <class EncodingT>
typename EncodingT::string_t DebugFileInfoInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugFileInfoInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t DebugFileInfoInterpreter<EncodingT>::getClassName() const
{
	return UCS("DebugFileInfo");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugFileInfo"), method, args, ret) ||
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
		o = value->value();
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
		value->value(o);
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

