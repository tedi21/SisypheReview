#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugValueInfoInterpreterAccess<EncodingT>::DebugValueInfoInterpreterAccess()
{
	m_object = _DebugValueInfoAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t DebugValueInfoInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugValueInfoInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t DebugValueInfoInterpreterAccess<EncodingT>::getClassName() const
{
	return UCS("DebugValueInfoAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugValueInfoAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugValueInfoAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new DebugValueInfoInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreterAccess<EncodingT>::getAllDebugValueInfos()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllDebugValueInfos());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreterAccess<EncodingT>::getManyDebugValueInfos(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyDebugValueInfos(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreterAccess<EncodingT>::getOneDebugValueInfo(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< DebugValueInfoInterpreter<EncodingT> > res(new DebugValueInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res->value(m_object->getOneDebugValueInfo(nativeIdentifier));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreterAccess<EncodingT>::selectOneDebugValueInfo(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< DebugValueInfoInterpreter<EncodingT> > res(new DebugValueInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res->value(m_object->selectOneDebugValueInfo(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreterAccess<EncodingT>::selectManyDebugValueInfos(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyDebugValueInfos(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugValueInfoInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreterAccess<EncodingT>::isSelectedDebugValueInfo(const boost::shared_ptr< Base<EncodingT> >& debugValueInfo)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _DebugValueInfo<EncodingT> > nativeDebugValueInfo;
		if (check_debugValueInfo(debugValueInfo, nativeDebugValueInfo))
		{
			res->value(m_object->isSelectedDebugValueInfo(nativeDebugValueInfo));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugValueInfoInterpreterAccess<EncodingT>::fillDebugVariableInfo(boost::shared_ptr< Base<EncodingT> >& debugValueInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugValueInfo<EncodingT> > nativeDebugValueInfo;
		if (check_debugValueInfo(debugValueInfo, nativeDebugValueInfo))
		{
			m_object->fillDebugVariableInfo(nativeDebugValueInfo);
			reset_debugValueInfo(debugValueInfo, nativeDebugValueInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugValueInfoInterpreterAccess<EncodingT>::fillDebugStubInfo(boost::shared_ptr< Base<EncodingT> >& debugValueInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugValueInfo<EncodingT> > nativeDebugValueInfo;
		if (check_debugValueInfo(debugValueInfo, nativeDebugValueInfo))
		{
			m_object->fillDebugStubInfo(nativeDebugValueInfo);
			reset_debugValueInfo(debugValueInfo, nativeDebugValueInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreterAccess<EncodingT>::isModifiedDebugValueInfo(const boost::shared_ptr< Base<EncodingT> >& debugValueInfo)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _DebugValueInfo<EncodingT> > nativeDebugValueInfo;
		if (check_debugValueInfo(debugValueInfo, nativeDebugValueInfo))
		{
			res->value(m_object->isModifiedDebugValueInfo(nativeDebugValueInfo));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugValueInfoInterpreterAccess<EncodingT>::updateDebugValueInfo(boost::shared_ptr< Base<EncodingT> >& debugValueInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugValueInfo<EncodingT> > nativeDebugValueInfo;
		if (check_debugValueInfo(debugValueInfo, nativeDebugValueInfo))
		{
			m_object->updateDebugValueInfo(nativeDebugValueInfo);
			reset_debugValueInfo(debugValueInfo, nativeDebugValueInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugValueInfoInterpreterAccess<EncodingT>::insertDebugValueInfo(boost::shared_ptr< Base<EncodingT> >& debugValueInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugValueInfo<EncodingT> > nativeDebugValueInfo;
		if (check_debugValueInfo(debugValueInfo, nativeDebugValueInfo))
		{
			m_object->insertDebugValueInfo(nativeDebugValueInfo);
			reset_debugValueInfo(debugValueInfo, nativeDebugValueInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugValueInfoInterpreterAccess<EncodingT>::deleteDebugValueInfo(boost::shared_ptr< Base<EncodingT> >& debugValueInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugValueInfo<EncodingT> > nativeDebugValueInfo;
		if (check_debugValueInfo(debugValueInfo, nativeDebugValueInfo))
		{
			m_object->deleteDebugValueInfo(nativeDebugValueInfo);
			reset_debugValueInfo(debugValueInfo, nativeDebugValueInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugValueInfoInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void DebugValueInfoInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

