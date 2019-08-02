#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugErrorInfoInterpreterAccess<EncodingT>::DebugErrorInfoInterpreterAccess()
{
	m_object = _DebugErrorInfoAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t DebugErrorInfoInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugErrorInfoInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t DebugErrorInfoInterpreterAccess<EncodingT>::getClassName() const
{
	return UCS("DebugErrorInfoAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugErrorInfoAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugErrorInfoAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _DebugErrorInfo<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new DebugErrorInfoInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreterAccess<EncodingT>::getAllDebugErrorInfos()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllDebugErrorInfos());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreterAccess<EncodingT>::getManyDebugErrorInfos(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyDebugErrorInfos(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreterAccess<EncodingT>::getOneDebugErrorInfo(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugErrorInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res.reset(new DebugErrorInfoInterpreter<EncodingT>(m_object->getOneDebugErrorInfo(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreterAccess<EncodingT>::selectOneDebugErrorInfo(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugErrorInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new DebugErrorInfoInterpreter<EncodingT>(m_object->selectOneDebugErrorInfo(nativeIdentifier,
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
void DebugErrorInfoInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreterAccess<EncodingT>::isSelectedDebugErrorInfo(const boost::shared_ptr< Base<EncodingT> >& debugErrorInfo)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _DebugErrorInfo<EncodingT> > nativeDebugErrorInfo;
		if (check_debugErrorInfo(debugErrorInfo, nativeDebugErrorInfo))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedDebugErrorInfo(nativeDebugErrorInfo)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreterAccess<EncodingT>::isModifiedDebugErrorInfo(const boost::shared_ptr< Base<EncodingT> >& debugErrorInfo)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _DebugErrorInfo<EncodingT> > nativeDebugErrorInfo;
		if (check_debugErrorInfo(debugErrorInfo, nativeDebugErrorInfo))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedDebugErrorInfo(nativeDebugErrorInfo)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugErrorInfoInterpreterAccess<EncodingT>::updateDebugErrorInfo(boost::shared_ptr< Base<EncodingT> >& debugErrorInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugErrorInfo<EncodingT> > nativeDebugErrorInfo;
		if (check_debugErrorInfo(debugErrorInfo, nativeDebugErrorInfo))
		{
			m_object->updateDebugErrorInfo(nativeDebugErrorInfo);
			reset_debugErrorInfo(debugErrorInfo, nativeDebugErrorInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugErrorInfoInterpreterAccess<EncodingT>::insertDebugErrorInfo(boost::shared_ptr< Base<EncodingT> >& debugErrorInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugErrorInfo<EncodingT> > nativeDebugErrorInfo;
		if (check_debugErrorInfo(debugErrorInfo, nativeDebugErrorInfo))
		{
			m_object->insertDebugErrorInfo(nativeDebugErrorInfo);
			reset_debugErrorInfo(debugErrorInfo, nativeDebugErrorInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugErrorInfoInterpreterAccess<EncodingT>::deleteDebugErrorInfo(boost::shared_ptr< Base<EncodingT> >& debugErrorInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugErrorInfo<EncodingT> > nativeDebugErrorInfo;
		if (check_debugErrorInfo(debugErrorInfo, nativeDebugErrorInfo))
		{
			m_object->deleteDebugErrorInfo(nativeDebugErrorInfo);
			reset_debugErrorInfo(debugErrorInfo, nativeDebugErrorInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugErrorInfoInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void DebugErrorInfoInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

