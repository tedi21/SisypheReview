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
DebugVariableInfoInterpreterAccess<EncodingT>::~DebugVariableInfoInterpreterAccess()
{}

template <class EncodingT>
typename EncodingT::string_t DebugVariableInfoInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new DebugVariableInfoInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t DebugVariableInfoInterpreterAccess<EncodingT>::getClassName() const
{
	return C("DebugVariableInfoAccess");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("DebugVariableInfoAccess"), method, args, ret))
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
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::convert_array(const std::vector< shared_ptr< _DebugVariableInfo<EncodingT> > >& value) const
{
	shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(shared_ptr< Base<EncodingT> >(new DebugVariableInfoInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::getAllDebugVariableInfos()
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
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
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::getManyDebugVariableInfos(const shared_ptr< Base<EncodingT> >& filter)
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
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
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::getOneDebugVariableInfo(shared_ptr< Base<EncodingT> > const& identifier)
{
	shared_ptr< Base<EncodingT> > res(new DebugVariableInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier))
		{
			res.reset(new DebugVariableInfoInterpreter<EncodingT>(m_object->getOneDebugVariableInfo(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::selectOneDebugVariableInfo(shared_ptr< Base<EncodingT> > const& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	shared_ptr< Base<EncodingT> > res(new DebugVariableInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new DebugVariableInfoInterpreter<EncodingT>(m_object->selectOneDebugVariableInfo(nativeIdentifier,
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
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::selectManyDebugVariableInfos(const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
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
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::isSelectedDebugVariableInfo(const shared_ptr< Base<EncodingT> >& debugVariableInfo)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
		if (check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedDebugVariableInfo(nativeDebugVariableInfo)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugVariableInfoInterpreterAccess<EncodingT>::fillDebugFunctionInfo(shared_ptr< Base<EncodingT> >& debugVariableInfo)
{
	clearError();
	try
	{
		shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
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
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::isModifiedDebugVariableInfo(const shared_ptr< Base<EncodingT> >& debugVariableInfo)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
		if (check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedDebugVariableInfo(nativeDebugVariableInfo)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugVariableInfoInterpreterAccess<EncodingT>::updateDebugVariableInfo(shared_ptr< Base<EncodingT> >& debugVariableInfo)
{
	clearError();
	try
	{
		shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
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
void DebugVariableInfoInterpreterAccess<EncodingT>::insertDebugVariableInfo(shared_ptr< Base<EncodingT> >& debugVariableInfo)
{
	clearError();
	try
	{
		shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
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
void DebugVariableInfoInterpreterAccess<EncodingT>::deleteDebugVariableInfo(shared_ptr< Base<EncodingT> >& debugVariableInfo)
{
	clearError();
	try
	{
		shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
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
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreterAccess<EncodingT>::getError(shared_ptr< Base<EncodingT> >& text) const
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

