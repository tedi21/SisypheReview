#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
TextFileInterpreter<EncodingT>::TextFileInterpreter()
{
	m_value = boost::make_shared< _TextFile<EncodingT> >();
}

template <class EncodingT>
TextFileInterpreter<EncodingT>::TextFileInterpreter(boost::shared_ptr< _TextFile<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
TextFileInterpreter<EncodingT>::TextFileInterpreter(boost::shared_ptr< Base<EncodingT> > const& content)
{
	typename EncodingT::string_t nativeContent;
	if (check_string<EncodingT>(content, nativeContent))
	{
		m_value = boost::make_shared< _TextFile<EncodingT> >(nativeContent);
	}
}

template <class EncodingT>
boost::shared_ptr< _TextFile<EncodingT> > TextFileInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void TextFileInterpreter<EncodingT>::value(boost::shared_ptr< _TextFile<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::getRowid() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getRowid()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::getContent() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getContent()) );
}


template <class EncodingT>
void TextFileInterpreter<EncodingT>::setContent(boost::shared_ptr< Base<EncodingT> > const& content)
{
	typename EncodingT::string_t nativeContent;
	if (check_string<EncodingT>(content, nativeContent))
	{
		m_value->setContent(nativeContent);
	}
}


template <class EncodingT>
void TextFileInterpreter<EncodingT>::removeCppFile(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppFile(m_value->getCppFilesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void TextFileInterpreter<EncodingT>::removeDebugFileInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseDebugFileInfo(m_value->getDebugFileInfosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void TextFileInterpreter<EncodingT>::insertCppFile(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppFile)
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
void TextFileInterpreter<EncodingT>::insertDebugFileInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugFileInfo)
{
	size_t nativePosition;
	boost::shared_ptr< _DebugFileInfo<EncodingT> > nativeDebugFileInfo;
	if (check_numeric_i(n, nativePosition) &&
		check_debugFileInfo(debugFileInfo, nativeDebugFileInfo))
	{
		m_value->insertDebugFileInfo(m_value->getDebugFileInfosBeginning()+nativePosition, nativeDebugFileInfo);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::getCppFile(boost::shared_ptr< Base<EncodingT> > const& n)
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
boost::shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::getDebugFileInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugFileInfoInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new DebugFileInfoInterpreter<EncodingT>(m_value->getDebugFileInfoAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void TextFileInterpreter<EncodingT>::clearCppFiles()
{
	m_value->clearCppFiles();
}


template <class EncodingT>
void TextFileInterpreter<EncodingT>::clearDebugFileInfos()
{
	m_value->clearDebugFileInfos();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::hasCppFiles() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppFilesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::hasDebugFileInfos() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isDebugFileInfosEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::cppFilesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppFilesSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::debugFileInfosCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getDebugFileInfosSize()));
}

template <class EncodingT>
typename EncodingT::string_t TextFileInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new TextFileInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t TextFileInterpreter<EncodingT>::getClassName() const
{
	return C("TextFile");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("TextFile"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in TextFile, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_textFile(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _TextFile<EncodingT> >& o)
{
	boost::shared_ptr< TextFileInterpreter<EncodingT> > value  = dynamic_pointer_cast< TextFileInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "TextFile expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_textFile(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _TextFile<EncodingT> > const& o)
{
	boost::shared_ptr< TextFileInterpreter<EncodingT> > value  = dynamic_pointer_cast< TextFileInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "TextFile expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

