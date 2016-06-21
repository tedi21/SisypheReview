#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugFunctionInfoInterpreterAccess<EncodingT>::DebugFunctionInfoInterpreterAccess()
{
	m_object = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
DebugFunctionInfoInterpreterAccess<EncodingT>::~DebugFunctionInfoInterpreterAccess()
{}

template <class EncodingT>
typename EncodingT::string_t DebugFunctionInfoInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreterAccess<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new DebugFunctionInfoInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t DebugFunctionInfoInterpreterAccess<EncodingT>::getClassName() const
{
	return C("DebugFunctionInfoAccess");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("DebugFunctionInfoAccess"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in DebugFunctionInfoAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreterAccess<EncodingT>::convert_array(const std::vector< shared_ptr< _DebugFunctionInfo<EncodingT> > >& value) const
{
	shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(shared_ptr< Base<EncodingT> >(new DebugFunctionInfoInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreterAccess<EncodingT>::getAllDebugFunctionInfos()
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllDebugFunctionInfos());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreterAccess<EncodingT>::getManyDebugFunctionInfos(const shared_ptr< Base<EncodingT> >& filter)
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyDebugFunctionInfos(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreterAccess<EncodingT>::getOneDebugFunctionInfo(shared_ptr< Base<EncodingT> > const& identifier)
{
	shared_ptr< Base<EncodingT> > res(new DebugFunctionInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier))
		{
			res.reset(new DebugFunctionInfoInterpreter<EncodingT>(m_object->getOneDebugFunctionInfo(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreterAccess<EncodingT>::selectOneDebugFunctionInfo(shared_ptr< Base<EncodingT> > const& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	shared_ptr< Base<EncodingT> > res(new DebugFunctionInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new DebugFunctionInfoInterpreter<EncodingT>(m_object->selectOneDebugFunctionInfo(nativeIdentifier,
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
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreterAccess<EncodingT>::selectManyDebugFunctionInfos(const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyDebugFunctionInfos(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugFunctionInfoInterpreterAccess<EncodingT>::cancelSelection()
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
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreterAccess<EncodingT>::isSelectedDebugFunctionInfo(const shared_ptr< Base<EncodingT> >& debugFunctionInfo)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
		if (check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedDebugFunctionInfo(nativeDebugFunctionInfo)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugFunctionInfoInterpreterAccess<EncodingT>::fillCppFunction(shared_ptr< Base<EncodingT> >& debugFunctionInfo)
{
	clearError();
	try
	{
		shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
		if (check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo))
		{
			m_object->fillCppFunction(nativeDebugFunctionInfo);
			reset_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugFunctionInfoInterpreterAccess<EncodingT>::fillAllDebugVariableInfos(shared_ptr< Base<EncodingT> >& debugFunctionInfo, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
		if (check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllDebugVariableInfos(nativeDebugFunctionInfo, nativeNoWait);
			reset_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugFunctionInfoInterpreterAccess<EncodingT>::fillOneDebugVariableInfo(shared_ptr< Base<EncodingT> >& refDebugFunctionInfo,
				const shared_ptr< Base<EncodingT> >& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _DebugFunctionInfo<EncodingT> > nativeRefDebugFunctionInfo;
		int nativeIdentifier;
		if (check_debugFunctionInfo(refDebugFunctionInfo, nativeRefDebugFunctionInfo) && 
			check_numeric(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneDebugVariableInfo(nativeRefDebugFunctionInfo,
				nativeIdentifier,
				nativeNoWait);
			reset_debugFunctionInfo(refDebugFunctionInfo, nativeRefDebugFunctionInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugFunctionInfoInterpreterAccess<EncodingT>::fillManyDebugVariableInfos(shared_ptr< Base<EncodingT> >& debugFunctionInfo, const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
		if (check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyDebugVariableInfos(nativeDebugFunctionInfo, nativeFilter, nativeNoWait);
			reset_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreterAccess<EncodingT>::isModifiedDebugFunctionInfo(const shared_ptr< Base<EncodingT> >& debugFunctionInfo)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
		if (check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedDebugFunctionInfo(nativeDebugFunctionInfo)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugFunctionInfoInterpreterAccess<EncodingT>::updateDebugFunctionInfo(shared_ptr< Base<EncodingT> >& debugFunctionInfo)
{
	clearError();
	try
	{
		shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
		if (check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo))
		{
			m_object->updateDebugFunctionInfo(nativeDebugFunctionInfo);
			reset_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugFunctionInfoInterpreterAccess<EncodingT>::insertDebugFunctionInfo(shared_ptr< Base<EncodingT> >& debugFunctionInfo)
{
	clearError();
	try
	{
		shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
		if (check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo))
		{
			m_object->insertDebugFunctionInfo(nativeDebugFunctionInfo);
			reset_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugFunctionInfoInterpreterAccess<EncodingT>::deleteDebugFunctionInfo(shared_ptr< Base<EncodingT> >& debugFunctionInfo)
{
	clearError();
	try
	{
		shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
		if (check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo))
		{
			m_object->deleteDebugFunctionInfo(nativeDebugFunctionInfo);
			reset_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugFunctionInfoInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void DebugFunctionInfoInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreterAccess<EncodingT>::getError(shared_ptr< Base<EncodingT> >& text) const
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

