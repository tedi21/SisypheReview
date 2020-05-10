#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugStubInfoInterpreterAccess<EncodingT>::DebugStubInfoInterpreterAccess()
{
	m_object = _DebugStubInfoAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t DebugStubInfoInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugStubInfoInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t DebugStubInfoInterpreterAccess<EncodingT>::getClassName() const
{
	return UCS("DebugStubInfoAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugStubInfoAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugStubInfoAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new DebugStubInfoInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreterAccess<EncodingT>::getAllDebugStubInfos()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllDebugStubInfos());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreterAccess<EncodingT>::getManyDebugStubInfos(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyDebugStubInfos(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreterAccess<EncodingT>::getOneDebugStubInfo(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugStubInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res.reset(new DebugStubInfoInterpreter<EncodingT>(m_object->getOneDebugStubInfo(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreterAccess<EncodingT>::selectOneDebugStubInfo(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugStubInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new DebugStubInfoInterpreter<EncodingT>(m_object->selectOneDebugStubInfo(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreterAccess<EncodingT>::selectManyDebugStubInfos(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyDebugStubInfos(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugStubInfoInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreterAccess<EncodingT>::isSelectedDebugStubInfo(const boost::shared_ptr< Base<EncodingT> >& debugStubInfo)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _DebugStubInfo<EncodingT> > nativeDebugStubInfo;
		if (check_debugStubInfo(debugStubInfo, nativeDebugStubInfo))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedDebugStubInfo(nativeDebugStubInfo)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugStubInfoInterpreterAccess<EncodingT>::fillDebugFileInfo(boost::shared_ptr< Base<EncodingT> >& debugStubInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugStubInfo<EncodingT> > nativeDebugStubInfo;
		if (check_debugStubInfo(debugStubInfo, nativeDebugStubInfo))
		{
			m_object->fillDebugFileInfo(nativeDebugStubInfo);
			reset_debugStubInfo(debugStubInfo, nativeDebugStubInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugStubInfoInterpreterAccess<EncodingT>::fillAllDebugValueInfos(boost::shared_ptr< Base<EncodingT> >& debugStubInfo, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _DebugStubInfo<EncodingT> > nativeDebugStubInfo;
		if (check_debugStubInfo(debugStubInfo, nativeDebugStubInfo) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllDebugValueInfos(nativeDebugStubInfo, nativeNoWait);
			reset_debugStubInfo(debugStubInfo, nativeDebugStubInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugStubInfoInterpreterAccess<EncodingT>::fillOneDebugValueInfo(boost::shared_ptr< Base<EncodingT> >& refDebugStubInfo,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _DebugStubInfo<EncodingT> > nativeRefDebugStubInfo;
		long long nativeIdentifier;
		if (check_debugStubInfo(refDebugStubInfo, nativeRefDebugStubInfo) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneDebugValueInfo(nativeRefDebugStubInfo,
				nativeIdentifier,
				nativeNoWait);
			reset_debugStubInfo(refDebugStubInfo, nativeRefDebugStubInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugStubInfoInterpreterAccess<EncodingT>::fillManyDebugValueInfos(boost::shared_ptr< Base<EncodingT> >& debugStubInfo, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _DebugStubInfo<EncodingT> > nativeDebugStubInfo;
		if (check_debugStubInfo(debugStubInfo, nativeDebugStubInfo) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyDebugValueInfos(nativeDebugStubInfo, nativeFilter, nativeNoWait);
			reset_debugStubInfo(debugStubInfo, nativeDebugStubInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreterAccess<EncodingT>::isModifiedDebugStubInfo(const boost::shared_ptr< Base<EncodingT> >& debugStubInfo)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _DebugStubInfo<EncodingT> > nativeDebugStubInfo;
		if (check_debugStubInfo(debugStubInfo, nativeDebugStubInfo))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedDebugStubInfo(nativeDebugStubInfo)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugStubInfoInterpreterAccess<EncodingT>::updateDebugStubInfo(boost::shared_ptr< Base<EncodingT> >& debugStubInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugStubInfo<EncodingT> > nativeDebugStubInfo;
		if (check_debugStubInfo(debugStubInfo, nativeDebugStubInfo))
		{
			m_object->updateDebugStubInfo(nativeDebugStubInfo);
			reset_debugStubInfo(debugStubInfo, nativeDebugStubInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugStubInfoInterpreterAccess<EncodingT>::insertDebugStubInfo(boost::shared_ptr< Base<EncodingT> >& debugStubInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugStubInfo<EncodingT> > nativeDebugStubInfo;
		if (check_debugStubInfo(debugStubInfo, nativeDebugStubInfo))
		{
			m_object->insertDebugStubInfo(nativeDebugStubInfo);
			reset_debugStubInfo(debugStubInfo, nativeDebugStubInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugStubInfoInterpreterAccess<EncodingT>::deleteDebugStubInfo(boost::shared_ptr< Base<EncodingT> >& debugStubInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugStubInfo<EncodingT> > nativeDebugStubInfo;
		if (check_debugStubInfo(debugStubInfo, nativeDebugStubInfo))
		{
			m_object->deleteDebugStubInfo(nativeDebugStubInfo);
			reset_debugStubInfo(debugStubInfo, nativeDebugStubInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugStubInfoInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void DebugStubInfoInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

