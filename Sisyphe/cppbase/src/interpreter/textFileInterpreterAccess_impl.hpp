#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
TextFileInterpreterAccess<EncodingT>::TextFileInterpreterAccess()
{
	m_object = _TextFileAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t TextFileInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new TextFileInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t TextFileInterpreterAccess<EncodingT>::getClassName() const
{
	return UCS("TextFileAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("TextFileAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in TextFileAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _TextFile<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new TextFileInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::getAllTextFiles()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllTextFiles());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::getManyTextFiles(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyTextFiles(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::getOneTextFile(boost::shared_ptr< Base<EncodingT> > const& rowid)
{
	boost::shared_ptr< TextFileInterpreter<EncodingT> > res(new TextFileInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeRowid;
		if (check_numeric_i(rowid, nativeRowid))
		{
			res->value(m_object->getOneTextFile(nativeRowid));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::selectOneTextFile(boost::shared_ptr< Base<EncodingT> > const& rowid,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< TextFileInterpreter<EncodingT> > res(new TextFileInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeRowid;
		if (check_numeric_i(rowid, nativeRowid) &&
			check_bool(nowait, nativeNoWait))
		{
			res->value(m_object->selectOneTextFile(nativeRowid,
				nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::cancelSelection()
{
	clearError();
	try
	{
		m_object->cancelSelection();
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::isSelectedTextFile(const boost::shared_ptr< Base<EncodingT> >& textFile)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile))
		{
			res->value(m_object->isSelectedTextFile(nativeTextFile));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::fillAllCppFiles(boost::shared_ptr< Base<EncodingT> >& textFile, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppFiles(nativeTextFile, nativeNoWait);
			reset_textFile(textFile, nativeTextFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::fillAllDebugFileInfos(boost::shared_ptr< Base<EncodingT> >& textFile, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllDebugFileInfos(nativeTextFile, nativeNoWait);
			reset_textFile(textFile, nativeTextFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::fillOneCppFile(boost::shared_ptr< Base<EncodingT> >& refTextFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _TextFile<EncodingT> > nativeRefTextFile;
		long long nativeIdentifier;
		if (check_textFile(refTextFile, nativeRefTextFile) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppFile(nativeRefTextFile,
				nativeIdentifier,
				nativeNoWait);
			reset_textFile(refTextFile, nativeRefTextFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::fillOneDebugFileInfo(boost::shared_ptr< Base<EncodingT> >& refTextFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _TextFile<EncodingT> > nativeRefTextFile;
		long long nativeIdentifier;
		if (check_textFile(refTextFile, nativeRefTextFile) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneDebugFileInfo(nativeRefTextFile,
				nativeIdentifier,
				nativeNoWait);
			reset_textFile(refTextFile, nativeRefTextFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::fillManyCppFiles(boost::shared_ptr< Base<EncodingT> >& textFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppFiles(nativeTextFile, nativeFilter, nativeNoWait);
			reset_textFile(textFile, nativeTextFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::fillManyDebugFileInfos(boost::shared_ptr< Base<EncodingT> >& textFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyDebugFileInfos(nativeTextFile, nativeFilter, nativeNoWait);
			reset_textFile(textFile, nativeTextFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::isModifiedTextFile(const boost::shared_ptr< Base<EncodingT> >& textFile)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile))
		{
			res->value(m_object->isModifiedTextFile(nativeTextFile));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::updateTextFile(boost::shared_ptr< Base<EncodingT> >& textFile)
{
	clearError();
	try
	{
		boost::shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile))
		{
			m_object->updateTextFile(nativeTextFile);
			reset_textFile(textFile, nativeTextFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::insertTextFile(boost::shared_ptr< Base<EncodingT> >& textFile)
{
	clearError();
	try
	{
		boost::shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile))
		{
			m_object->insertTextFile(nativeTextFile);
			reset_textFile(textFile, nativeTextFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::deleteTextFile(boost::shared_ptr< Base<EncodingT> >& textFile)
{
	clearError();
	try
	{
		boost::shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile))
		{
			m_object->deleteTextFile(nativeTextFile);
			reset_textFile(textFile, nativeTextFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
{
	boost::shared_ptr< String<EncodingT> > str  = dynamic_pointer_cast< String<EncodingT> >(text);
	if (str)
	{
		str->value(C(m_errorText));
	}
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(m_error));
}

NAMESPACE_END

#undef C
#undef A

