#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppParameterInterpreterAccess<EncodingT>::CppParameterInterpreterAccess()
{
	m_object = _CppParameterAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t CppParameterInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppParameterInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppParameterInterpreterAccess<EncodingT>::getClassName() const
{
	return C("CppParameterAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppParameterAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppParameterAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _CppParameter<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new CppParameterInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreterAccess<EncodingT>::getAllCppParameters()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllCppParameters());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreterAccess<EncodingT>::getManyCppParameters(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyCppParameters(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreterAccess<EncodingT>::getOneCppParameter(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppParameterInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res.reset(new CppParameterInterpreter<EncodingT>(m_object->getOneCppParameter(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreterAccess<EncodingT>::selectOneCppParameter(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppParameterInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new CppParameterInterpreter<EncodingT>(m_object->selectOneCppParameter(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreterAccess<EncodingT>::selectManyCppParameters(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyCppParameters(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppParameterInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreterAccess<EncodingT>::isSelectedCppParameter(const boost::shared_ptr< Base<EncodingT> >& cppParameter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppParameter<EncodingT> > nativeCppParameter;
		if (check_cppParameter(cppParameter, nativeCppParameter))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedCppParameter(nativeCppParameter)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppParameterInterpreterAccess<EncodingT>::fillCppFunction(boost::shared_ptr< Base<EncodingT> >& cppParameter)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppParameter<EncodingT> > nativeCppParameter;
		if (check_cppParameter(cppParameter, nativeCppParameter))
		{
			m_object->fillCppFunction(nativeCppParameter);
			reset_cppParameter(cppParameter, nativeCppParameter);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreterAccess<EncodingT>::isModifiedCppParameter(const boost::shared_ptr< Base<EncodingT> >& cppParameter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppParameter<EncodingT> > nativeCppParameter;
		if (check_cppParameter(cppParameter, nativeCppParameter))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedCppParameter(nativeCppParameter)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppParameterInterpreterAccess<EncodingT>::updateCppParameter(boost::shared_ptr< Base<EncodingT> >& cppParameter)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppParameter<EncodingT> > nativeCppParameter;
		if (check_cppParameter(cppParameter, nativeCppParameter))
		{
			m_object->updateCppParameter(nativeCppParameter);
			reset_cppParameter(cppParameter, nativeCppParameter);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppParameterInterpreterAccess<EncodingT>::insertCppParameter(boost::shared_ptr< Base<EncodingT> >& cppParameter)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppParameter<EncodingT> > nativeCppParameter;
		if (check_cppParameter(cppParameter, nativeCppParameter))
		{
			m_object->insertCppParameter(nativeCppParameter);
			reset_cppParameter(cppParameter, nativeCppParameter);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppParameterInterpreterAccess<EncodingT>::deleteCppParameter(boost::shared_ptr< Base<EncodingT> >& cppParameter)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppParameter<EncodingT> > nativeCppParameter;
		if (check_cppParameter(cppParameter, nativeCppParameter))
		{
			m_object->deleteCppParameter(nativeCppParameter);
			reset_cppParameter(cppParameter, nativeCppParameter);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppParameterInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void CppParameterInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

