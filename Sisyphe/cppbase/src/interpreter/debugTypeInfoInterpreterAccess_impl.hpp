#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugTypeInfoInterpreterAccess<EncodingT>::DebugTypeInfoInterpreterAccess()
{
	m_object = _DebugTypeInfoAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t DebugTypeInfoInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugTypeInfoInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t DebugTypeInfoInterpreterAccess<EncodingT>::getClassName() const
{
	return UCS("DebugTypeInfoAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugTypeInfoAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugTypeInfoAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new DebugTypeInfoInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreterAccess<EncodingT>::getAllDebugTypeInfos()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllDebugTypeInfos());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreterAccess<EncodingT>::getManyDebugTypeInfos(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyDebugTypeInfos(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreterAccess<EncodingT>::getOneDebugTypeInfo(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< DebugTypeInfoInterpreter<EncodingT> > res(new DebugTypeInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res->value(m_object->getOneDebugTypeInfo(nativeIdentifier));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreterAccess<EncodingT>::selectOneDebugTypeInfo(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< DebugTypeInfoInterpreter<EncodingT> > res(new DebugTypeInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res->value(m_object->selectOneDebugTypeInfo(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreterAccess<EncodingT>::selectManyDebugTypeInfos(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyDebugTypeInfos(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreterAccess<EncodingT>::isSelectedDebugTypeInfo(const boost::shared_ptr< Base<EncodingT> >& debugTypeInfo)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
		if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo))
		{
			res->value(m_object->isSelectedDebugTypeInfo(nativeDebugTypeInfo));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::fillPrimitiveType(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
		if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo))
		{
			m_object->fillPrimitiveType(nativeDebugTypeInfo);
			reset_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::fillAllRichTypes(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
		if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllRichTypes(nativeDebugTypeInfo, nativeNoWait);
			reset_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::fillAllDebugFunctionInfos(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
		if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllDebugFunctionInfos(nativeDebugTypeInfo, nativeNoWait);
			reset_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::fillAllDebugVariableInfos(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
		if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllDebugVariableInfos(nativeDebugTypeInfo, nativeNoWait);
			reset_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::fillOneRichType(boost::shared_ptr< Base<EncodingT> >& refDebugTypeInfo,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeRefDebugTypeInfo;
		long long nativeIdentifier;
		if (check_debugTypeInfo(refDebugTypeInfo, nativeRefDebugTypeInfo) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneRichType(nativeRefDebugTypeInfo,
				nativeIdentifier,
				nativeNoWait);
			reset_debugTypeInfo(refDebugTypeInfo, nativeRefDebugTypeInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::fillOneDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> >& refDebugTypeInfo,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeRefDebugTypeInfo;
		long long nativeIdentifier;
		if (check_debugTypeInfo(refDebugTypeInfo, nativeRefDebugTypeInfo) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneDebugFunctionInfo(nativeRefDebugTypeInfo,
				nativeIdentifier,
				nativeNoWait);
			reset_debugTypeInfo(refDebugTypeInfo, nativeRefDebugTypeInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::fillOneDebugVariableInfo(boost::shared_ptr< Base<EncodingT> >& refDebugTypeInfo,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeRefDebugTypeInfo;
		long long nativeIdentifier;
		if (check_debugTypeInfo(refDebugTypeInfo, nativeRefDebugTypeInfo) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneDebugVariableInfo(nativeRefDebugTypeInfo,
				nativeIdentifier,
				nativeNoWait);
			reset_debugTypeInfo(refDebugTypeInfo, nativeRefDebugTypeInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::fillManyRichTypes(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
		if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyRichTypes(nativeDebugTypeInfo, nativeFilter, nativeNoWait);
			reset_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::fillManyDebugFunctionInfos(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
		if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyDebugFunctionInfos(nativeDebugTypeInfo, nativeFilter, nativeNoWait);
			reset_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::fillManyDebugVariableInfos(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
		if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyDebugVariableInfos(nativeDebugTypeInfo, nativeFilter, nativeNoWait);
			reset_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreterAccess<EncodingT>::isModifiedDebugTypeInfo(const boost::shared_ptr< Base<EncodingT> >& debugTypeInfo)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
		if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo))
		{
			res->value(m_object->isModifiedDebugTypeInfo(nativeDebugTypeInfo));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::updateDebugTypeInfo(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
		if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo))
		{
			m_object->updateDebugTypeInfo(nativeDebugTypeInfo);
			reset_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::insertDebugTypeInfo(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
		if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo))
		{
			m_object->insertDebugTypeInfo(nativeDebugTypeInfo);
			reset_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::deleteDebugTypeInfo(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
		if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo))
		{
			m_object->deleteDebugTypeInfo(nativeDebugTypeInfo);
			reset_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void DebugTypeInfoInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugTypeInfoInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

