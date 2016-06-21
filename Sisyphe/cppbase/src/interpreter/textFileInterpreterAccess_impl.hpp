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
TextFileInterpreterAccess<EncodingT>::~TextFileInterpreterAccess()
{}

template <class EncodingT>
typename EncodingT::string_t TextFileInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new TextFileInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t TextFileInterpreterAccess<EncodingT>::getClassName() const
{
	return C("TextFileAccess");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("TextFileAccess"), method, args, ret))
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
shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::convert_array(const std::vector< shared_ptr< _TextFile<EncodingT> > >& value) const
{
	shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(shared_ptr< Base<EncodingT> >(new TextFileInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::getAllTextFiles()
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
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
shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::getManyTextFiles(const shared_ptr< Base<EncodingT> >& filter)
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
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
shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::getOneTextFile(shared_ptr< Base<EncodingT> > const& rowid)
{
	shared_ptr< Base<EncodingT> > res(new TextFileInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeRowid;
		if (check_numeric(rowid, nativeRowid))
		{
			res.reset(new TextFileInterpreter<EncodingT>(m_object->getOneTextFile(nativeRowid)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::selectOneTextFile(shared_ptr< Base<EncodingT> > const& rowid,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	shared_ptr< Base<EncodingT> > res(new TextFileInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeRowid;
		if (check_numeric(rowid, nativeRowid) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new TextFileInterpreter<EncodingT>(m_object->selectOneTextFile(nativeRowid,
				nativeNoWait)));
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
shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::isSelectedTextFile(const shared_ptr< Base<EncodingT> >& textFile)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedTextFile(nativeTextFile)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::fillAllTextNotices(shared_ptr< Base<EncodingT> >& textFile, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllTextNotices(nativeTextFile, nativeNoWait);
			reset_textFile(textFile, nativeTextFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::fillOneTextNotice(shared_ptr< Base<EncodingT> >& refTextFile,
				const shared_ptr< Base<EncodingT> >& rowid,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _TextFile<EncodingT> > nativeRefTextFile;
		long long nativeRowid;
		if (check_textFile(refTextFile, nativeRefTextFile) && 
			check_numeric(rowid, nativeRowid) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneTextNotice(nativeRefTextFile,
				nativeRowid,
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
void TextFileInterpreterAccess<EncodingT>::fillManyTextNotices(shared_ptr< Base<EncodingT> >& textFile, const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyTextNotices(nativeTextFile, nativeFilter, nativeNoWait);
			reset_textFile(textFile, nativeTextFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::isModifiedTextFile(const shared_ptr< Base<EncodingT> >& textFile)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedTextFile(nativeTextFile)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void TextFileInterpreterAccess<EncodingT>::updateTextFile(shared_ptr< Base<EncodingT> >& textFile)
{
	clearError();
	try
	{
		shared_ptr< _TextFile<EncodingT> > nativeTextFile;
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
void TextFileInterpreterAccess<EncodingT>::insertTextFile(shared_ptr< Base<EncodingT> >& textFile)
{
	clearError();
	try
	{
		shared_ptr< _TextFile<EncodingT> > nativeTextFile;
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
void TextFileInterpreterAccess<EncodingT>::deleteTextFile(shared_ptr< Base<EncodingT> >& textFile)
{
	clearError();
	try
	{
		shared_ptr< _TextFile<EncodingT> > nativeTextFile;
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
shared_ptr< Base<EncodingT> > TextFileInterpreterAccess<EncodingT>::getError(shared_ptr< Base<EncodingT> >& text) const
{
	shared_ptr< String<EncodingT> > str  = dynamic_pointer_cast< String<EncodingT> >(text);
	if (str)
	{
		str->setValue(C(m_errorText));
	}
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(m_error));
}

NAMESPACE_END

#undef C
#undef A

