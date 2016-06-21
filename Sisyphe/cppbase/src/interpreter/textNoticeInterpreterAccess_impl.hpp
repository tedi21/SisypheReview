#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
TextNoticeInterpreterAccess<EncodingT>::TextNoticeInterpreterAccess()
{
	m_object = _TextNoticeAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
TextNoticeInterpreterAccess<EncodingT>::~TextNoticeInterpreterAccess()
{}

template <class EncodingT>
typename EncodingT::string_t TextNoticeInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreterAccess<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new TextNoticeInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t TextNoticeInterpreterAccess<EncodingT>::getClassName() const
{
	return C("TextNoticeAccess");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("TextNoticeAccess"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in TextNoticeAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreterAccess<EncodingT>::convert_array(const std::vector< shared_ptr< _TextNotice<EncodingT> > >& value) const
{
	shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(shared_ptr< Base<EncodingT> >(new TextNoticeInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreterAccess<EncodingT>::getAllTextNotices()
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllTextNotices());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreterAccess<EncodingT>::getManyTextNotices(const shared_ptr< Base<EncodingT> >& filter)
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyTextNotices(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreterAccess<EncodingT>::getOneTextNotice(shared_ptr< Base<EncodingT> > const& rowid)
{
	shared_ptr< Base<EncodingT> > res(new TextNoticeInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeRowid;
		if (check_numeric(rowid, nativeRowid))
		{
			res.reset(new TextNoticeInterpreter<EncodingT>(m_object->getOneTextNotice(nativeRowid)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreterAccess<EncodingT>::selectOneTextNotice(shared_ptr< Base<EncodingT> > const& rowid,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	shared_ptr< Base<EncodingT> > res(new TextNoticeInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeRowid;
		if (check_numeric(rowid, nativeRowid) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new TextNoticeInterpreter<EncodingT>(m_object->selectOneTextNotice(nativeRowid,
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
shared_ptr< Base<EncodingT> > TextNoticeInterpreterAccess<EncodingT>::selectManyTextNotices(const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		bool nativeNoWait;
		if (check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			res = convert_array(m_object->selectManyTextNotices(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void TextNoticeInterpreterAccess<EncodingT>::cancelSelection()
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
shared_ptr< Base<EncodingT> > TextNoticeInterpreterAccess<EncodingT>::isSelectedTextNotice(const shared_ptr< Base<EncodingT> >& textNotice)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _TextNotice<EncodingT> > nativeTextNotice;
		if (check_textNotice(textNotice, nativeTextNotice))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedTextNotice(nativeTextNotice)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void TextNoticeInterpreterAccess<EncodingT>::fillTextFile(shared_ptr< Base<EncodingT> >& textNotice)
{
	clearError();
	try
	{
		shared_ptr< _TextNotice<EncodingT> > nativeTextNotice;
		if (check_textNotice(textNotice, nativeTextNotice))
		{
			m_object->fillTextFile(nativeTextNotice);
			reset_textNotice(textNotice, nativeTextNotice);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreterAccess<EncodingT>::isModifiedTextNotice(const shared_ptr< Base<EncodingT> >& textNotice)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _TextNotice<EncodingT> > nativeTextNotice;
		if (check_textNotice(textNotice, nativeTextNotice))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedTextNotice(nativeTextNotice)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void TextNoticeInterpreterAccess<EncodingT>::updateTextNotice(shared_ptr< Base<EncodingT> >& textNotice)
{
	clearError();
	try
	{
		shared_ptr< _TextNotice<EncodingT> > nativeTextNotice;
		if (check_textNotice(textNotice, nativeTextNotice))
		{
			m_object->updateTextNotice(nativeTextNotice);
			reset_textNotice(textNotice, nativeTextNotice);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void TextNoticeInterpreterAccess<EncodingT>::insertTextNotice(shared_ptr< Base<EncodingT> >& textNotice)
{
	clearError();
	try
	{
		shared_ptr< _TextNotice<EncodingT> > nativeTextNotice;
		if (check_textNotice(textNotice, nativeTextNotice))
		{
			m_object->insertTextNotice(nativeTextNotice);
			reset_textNotice(textNotice, nativeTextNotice);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void TextNoticeInterpreterAccess<EncodingT>::deleteTextNotice(shared_ptr< Base<EncodingT> >& textNotice)
{
	clearError();
	try
	{
		shared_ptr< _TextNotice<EncodingT> > nativeTextNotice;
		if (check_textNotice(textNotice, nativeTextNotice))
		{
			m_object->deleteTextNotice(nativeTextNotice);
			reset_textNotice(textNotice, nativeTextNotice);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void TextNoticeInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void TextNoticeInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreterAccess<EncodingT>::getError(shared_ptr< Base<EncodingT> >& text) const
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

