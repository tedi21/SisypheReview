#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugFileInfoInterpreterAccess<EncodingT>::DebugFileInfoInterpreterAccess()
{
	m_object = _DebugFileInfoAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
DebugFileInfoInterpreterAccess<EncodingT>::~DebugFileInfoInterpreterAccess()
{}

template <class EncodingT>
typename EncodingT::string_t DebugFileInfoInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugFileInfoInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t DebugFileInfoInterpreterAccess<EncodingT>::getClassName() const
{
	return C("DebugFileInfoAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("DebugFileInfoAccess"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in DebugFileInfoAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new DebugFileInfoInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreterAccess<EncodingT>::getAllDebugFileInfos()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllDebugFileInfos());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreterAccess<EncodingT>::getManyDebugFileInfos(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyDebugFileInfos(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreterAccess<EncodingT>::getOneDebugFileInfo(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugFileInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier))
		{
			res.reset(new DebugFileInfoInterpreter<EncodingT>(m_object->getOneDebugFileInfo(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreterAccess<EncodingT>::selectOneDebugFileInfo(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugFileInfoInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new DebugFileInfoInterpreter<EncodingT>(m_object->selectOneDebugFileInfo(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreterAccess<EncodingT>::selectManyDebugFileInfos(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyDebugFileInfos(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugFileInfoInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreterAccess<EncodingT>::isSelectedDebugFileInfo(const boost::shared_ptr< Base<EncodingT> >& debugFileInfo)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _DebugFileInfo<EncodingT> > nativeDebugFileInfo;
		if (check_debugFileInfo(debugFileInfo, nativeDebugFileInfo))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedDebugFileInfo(nativeDebugFileInfo)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugFileInfoInterpreterAccess<EncodingT>::fillCppFile(boost::shared_ptr< Base<EncodingT> >& debugFileInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugFileInfo<EncodingT> > nativeDebugFileInfo;
		if (check_debugFileInfo(debugFileInfo, nativeDebugFileInfo))
		{
			m_object->fillCppFile(nativeDebugFileInfo);
			reset_debugFileInfo(debugFileInfo, nativeDebugFileInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreterAccess<EncodingT>::isModifiedDebugFileInfo(const boost::shared_ptr< Base<EncodingT> >& debugFileInfo)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _DebugFileInfo<EncodingT> > nativeDebugFileInfo;
		if (check_debugFileInfo(debugFileInfo, nativeDebugFileInfo))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedDebugFileInfo(nativeDebugFileInfo)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void DebugFileInfoInterpreterAccess<EncodingT>::updateDebugFileInfo(boost::shared_ptr< Base<EncodingT> >& debugFileInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugFileInfo<EncodingT> > nativeDebugFileInfo;
		if (check_debugFileInfo(debugFileInfo, nativeDebugFileInfo))
		{
			m_object->updateDebugFileInfo(nativeDebugFileInfo);
			reset_debugFileInfo(debugFileInfo, nativeDebugFileInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugFileInfoInterpreterAccess<EncodingT>::insertDebugFileInfo(boost::shared_ptr< Base<EncodingT> >& debugFileInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugFileInfo<EncodingT> > nativeDebugFileInfo;
		if (check_debugFileInfo(debugFileInfo, nativeDebugFileInfo))
		{
			m_object->insertDebugFileInfo(nativeDebugFileInfo);
			reset_debugFileInfo(debugFileInfo, nativeDebugFileInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugFileInfoInterpreterAccess<EncodingT>::deleteDebugFileInfo(boost::shared_ptr< Base<EncodingT> >& debugFileInfo)
{
	clearError();
	try
	{
		boost::shared_ptr< _DebugFileInfo<EncodingT> > nativeDebugFileInfo;
		if (check_debugFileInfo(debugFileInfo, nativeDebugFileInfo))
		{
			m_object->deleteDebugFileInfo(nativeDebugFileInfo);
			reset_debugFileInfo(debugFileInfo, nativeDebugFileInfo);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void DebugFileInfoInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void DebugFileInfoInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFileInfoInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
{
	boost::shared_ptr< String<EncodingT> > str  = dynamic_pointer_cast< String<EncodingT> >(text);
	if (str)
	{
		str->setValue(C(m_errorText));
	}
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(m_error));
}

NAMESPACE_END

#undef C
#undef A

