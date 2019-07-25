#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppIncludeInterpreterAccess<EncodingT>::CppIncludeInterpreterAccess()
{
	m_object = _CppIncludeAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t CppIncludeInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppIncludeInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppIncludeInterpreterAccess<EncodingT>::getClassName() const
{
	return C("CppIncludeAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppIncludeAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppIncludeAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _CppInclude<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new CppIncludeInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreterAccess<EncodingT>::getAllCppIncludes()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllCppIncludes());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreterAccess<EncodingT>::getManyCppIncludes(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyCppIncludes(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreterAccess<EncodingT>::getOneCppInclude(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppIncludeInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res.reset(new CppIncludeInterpreter<EncodingT>(m_object->getOneCppInclude(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreterAccess<EncodingT>::selectOneCppInclude(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppIncludeInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new CppIncludeInterpreter<EncodingT>(m_object->selectOneCppInclude(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreterAccess<EncodingT>::selectManyCppIncludes(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyCppIncludes(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppIncludeInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreterAccess<EncodingT>::isSelectedCppInclude(const boost::shared_ptr< Base<EncodingT> >& cppInclude)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppInclude<EncodingT> > nativeCppInclude;
		if (check_cppInclude(cppInclude, nativeCppInclude))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedCppInclude(nativeCppInclude)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppIncludeInterpreterAccess<EncodingT>::fillCppFile(boost::shared_ptr< Base<EncodingT> >& cppInclude)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppInclude<EncodingT> > nativeCppInclude;
		if (check_cppInclude(cppInclude, nativeCppInclude))
		{
			m_object->fillCppFile(nativeCppInclude);
			reset_cppInclude(cppInclude, nativeCppInclude);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreterAccess<EncodingT>::isModifiedCppInclude(const boost::shared_ptr< Base<EncodingT> >& cppInclude)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppInclude<EncodingT> > nativeCppInclude;
		if (check_cppInclude(cppInclude, nativeCppInclude))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedCppInclude(nativeCppInclude)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppIncludeInterpreterAccess<EncodingT>::updateCppInclude(boost::shared_ptr< Base<EncodingT> >& cppInclude)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppInclude<EncodingT> > nativeCppInclude;
		if (check_cppInclude(cppInclude, nativeCppInclude))
		{
			m_object->updateCppInclude(nativeCppInclude);
			reset_cppInclude(cppInclude, nativeCppInclude);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppIncludeInterpreterAccess<EncodingT>::insertCppInclude(boost::shared_ptr< Base<EncodingT> >& cppInclude)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppInclude<EncodingT> > nativeCppInclude;
		if (check_cppInclude(cppInclude, nativeCppInclude))
		{
			m_object->insertCppInclude(nativeCppInclude);
			reset_cppInclude(cppInclude, nativeCppInclude);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppIncludeInterpreterAccess<EncodingT>::deleteCppInclude(boost::shared_ptr< Base<EncodingT> >& cppInclude)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppInclude<EncodingT> > nativeCppInclude;
		if (check_cppInclude(cppInclude, nativeCppInclude))
		{
			m_object->deleteCppInclude(nativeCppInclude);
			reset_cppInclude(cppInclude, nativeCppInclude);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppIncludeInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void CppIncludeInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppIncludeInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

