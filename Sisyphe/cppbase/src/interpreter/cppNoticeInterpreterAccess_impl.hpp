#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppNoticeInterpreterAccess<EncodingT>::CppNoticeInterpreterAccess()
{
	m_object = _CppNoticeAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t CppNoticeInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppNoticeInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppNoticeInterpreterAccess<EncodingT>::getClassName() const
{
	return UCS("CppNoticeAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("CppNoticeAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppNoticeAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _CppNotice<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new CppNoticeInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreterAccess<EncodingT>::getAllCppNotices()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllCppNotices());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreterAccess<EncodingT>::getManyCppNotices(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyCppNotices(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreterAccess<EncodingT>::getOneCppNotice(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppNoticeInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res.reset(new CppNoticeInterpreter<EncodingT>(m_object->getOneCppNotice(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreterAccess<EncodingT>::selectOneCppNotice(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppNoticeInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new CppNoticeInterpreter<EncodingT>(m_object->selectOneCppNotice(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreterAccess<EncodingT>::selectManyCppNotices(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		bool nativeNoWait;
		if (check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			res = convert_array(m_object->selectManyCppNotices(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppNoticeInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreterAccess<EncodingT>::isSelectedCppNotice(const boost::shared_ptr< Base<EncodingT> >& cppNotice)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppNotice<EncodingT> > nativeCppNotice;
		if (check_cppNotice(cppNotice, nativeCppNotice))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedCppNotice(nativeCppNotice)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppNoticeInterpreterAccess<EncodingT>::fillCppFile(boost::shared_ptr< Base<EncodingT> >& cppNotice)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppNotice<EncodingT> > nativeCppNotice;
		if (check_cppNotice(cppNotice, nativeCppNotice))
		{
			m_object->fillCppFile(nativeCppNotice);
			reset_cppNotice(cppNotice, nativeCppNotice);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreterAccess<EncodingT>::isModifiedCppNotice(const boost::shared_ptr< Base<EncodingT> >& cppNotice)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppNotice<EncodingT> > nativeCppNotice;
		if (check_cppNotice(cppNotice, nativeCppNotice))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedCppNotice(nativeCppNotice)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppNoticeInterpreterAccess<EncodingT>::updateCppNotice(boost::shared_ptr< Base<EncodingT> >& cppNotice)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppNotice<EncodingT> > nativeCppNotice;
		if (check_cppNotice(cppNotice, nativeCppNotice))
		{
			m_object->updateCppNotice(nativeCppNotice);
			reset_cppNotice(cppNotice, nativeCppNotice);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppNoticeInterpreterAccess<EncodingT>::insertCppNotice(boost::shared_ptr< Base<EncodingT> >& cppNotice)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppNotice<EncodingT> > nativeCppNotice;
		if (check_cppNotice(cppNotice, nativeCppNotice))
		{
			m_object->insertCppNotice(nativeCppNotice);
			reset_cppNotice(cppNotice, nativeCppNotice);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppNoticeInterpreterAccess<EncodingT>::deleteCppNotice(boost::shared_ptr< Base<EncodingT> >& cppNotice)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppNotice<EncodingT> > nativeCppNotice;
		if (check_cppNotice(cppNotice, nativeCppNotice))
		{
			m_object->deleteCppNotice(nativeCppNotice);
			reset_cppNotice(cppNotice, nativeCppNotice);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppNoticeInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void CppNoticeInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

