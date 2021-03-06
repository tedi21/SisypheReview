#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugVariableInfoInterpreterAccess<EncodingT>::DebugVariableInfoInterpreterAccess()
{
	m_object = _DebugVariableInfoAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t DebugVariableInfoInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugVariableInfoInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t DebugVariableInfoInterpreterAccess<EncodingT>::getClassName() const
{
	return UCS("DebugVariableInfoAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugVariableInfoAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugVariableInfoAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new DebugVariableInfoInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::getAllDebugVariableInfos()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllDebugVariableInfos());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::getManyDebugVariableInfos(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyDebugVariableInfos(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::getOneDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< DebugVariableInfoInterpreter<EncodingT> > res(new DebugVariableInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res->value(m_object->getOneDebugVariableInfo(nativeIdentifier));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::selectOneDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< DebugVariableInfoInterpreter<EncodingT> > res(new DebugVariableInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res->value(m_object->selectOneDebugVariableInfo(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::selectManyDebugVariableInfos(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyDebugVariableInfos(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugVariableInfoInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::isSelectedDebugVariableInfo(const boost::shared_ptr< Base<EncodingT> >& debugVariableInfo)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
		if (check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
		{
			res->value(m_object->isSelectedDebugVariableInfo(nativeDebugVariableInfo));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugVariableInfoInterpreterAccess<EncodingT>::fillDebugTypeInfo(boost::shared_ptr< Base<EncodingT> >& debugVariableInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
		if (check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
		{
			m_object->fillDebugTypeInfo(nativeDebugVariableInfo);
			reset_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugVariableInfoInterpreterAccess<EncodingT>::fillDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> >& debugVariableInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
		if (check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
		{
			m_object->fillDebugFunctionInfo(nativeDebugVariableInfo);
			reset_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugVariableInfoInterpreterAccess<EncodingT>::fillAllDebugValueInfos(boost::shared_ptr< Base<EncodingT> >& debugVariableInfo, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
		if (check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllDebugValueInfos(nativeDebugVariableInfo, nativeNoWait);
			reset_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugVariableInfoInterpreterAccess<EncodingT>::fillOneDebugValueInfo(boost::shared_ptr< Base<EncodingT> >& refDebugVariableInfo,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeRefDebugVariableInfo;
		long long nativeIdentifier;
		if (check_debugVariableInfo(refDebugVariableInfo, nativeRefDebugVariableInfo) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneDebugValueInfo(nativeRefDebugVariableInfo,
				nativeIdentifier,
				nativeNoWait);
			reset_debugVariableInfo(refDebugVariableInfo, nativeRefDebugVariableInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugVariableInfoInterpreterAccess<EncodingT>::fillManyDebugValueInfos(boost::shared_ptr< Base<EncodingT> >& debugVariableInfo, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
		if (check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyDebugValueInfos(nativeDebugVariableInfo, nativeFilter, nativeNoWait);
			reset_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::isModifiedDebugVariableInfo(const boost::shared_ptr< Base<EncodingT> >& debugVariableInfo)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
		if (check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
		{
			res->value(m_object->isModifiedDebugVariableInfo(nativeDebugVariableInfo));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugVariableInfoInterpreterAccess<EncodingT>::updateDebugVariableInfo(boost::shared_ptr< Base<EncodingT> >& debugVariableInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
		if (check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
		{
			m_object->updateDebugVariableInfo(nativeDebugVariableInfo);
			reset_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugVariableInfoInterpreterAccess<EncodingT>::insertDebugVariableInfo(boost::shared_ptr< Base<EncodingT> >& debugVariableInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
		if (check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
		{
			m_object->insertDebugVariableInfo(nativeDebugVariableInfo);
			reset_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugVariableInfoInterpreterAccess<EncodingT>::deleteDebugVariableInfo(boost::shared_ptr< Base<EncodingT> >& debugVariableInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
		if (check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
		{
			m_object->deleteDebugVariableInfo(nativeDebugVariableInfo);
			reset_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugVariableInfoInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void DebugVariableInfoInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

