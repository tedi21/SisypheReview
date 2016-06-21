#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CMacroInterpreterAccess<EncodingT>::CMacroInterpreterAccess()
{
	m_object = _CMacroAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
CMacroInterpreterAccess<EncodingT>::~CMacroInterpreterAccess()
{}

template <class EncodingT>
typename EncodingT::string_t CMacroInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreterAccess<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new CMacroInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CMacroInterpreterAccess<EncodingT>::getClassName() const
{
	return C("CMacroAccess");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CMacroAccess"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in CMacroAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreterAccess<EncodingT>::convert_array(const std::vector< shared_ptr< _CMacro<EncodingT> > >& value) const
{
	shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(shared_ptr< Base<EncodingT> >(new CMacroInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreterAccess<EncodingT>::getAllCMacros()
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllCMacros());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreterAccess<EncodingT>::getManyCMacros(const shared_ptr< Base<EncodingT> >& filter)
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyCMacros(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreterAccess<EncodingT>::getOneCMacro(shared_ptr< Base<EncodingT> > const& identifier)
{
	shared_ptr< Base<EncodingT> > res(new CMacroInterpreter<EncodingT>());
	clearError();
	try
	{
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier))
		{
			res.reset(new CMacroInterpreter<EncodingT>(m_object->getOneCMacro(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreterAccess<EncodingT>::selectOneCMacro(shared_ptr< Base<EncodingT> > const& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	shared_ptr< Base<EncodingT> > res(new CMacroInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new CMacroInterpreter<EncodingT>(m_object->selectOneCMacro(nativeIdentifier,
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
shared_ptr< Base<EncodingT> > CMacroInterpreterAccess<EncodingT>::selectManyCMacros(const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyCMacros(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CMacroInterpreterAccess<EncodingT>::cancelSelection()
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
shared_ptr< Base<EncodingT> > CMacroInterpreterAccess<EncodingT>::isSelectedCMacro(const shared_ptr< Base<EncodingT> >& cMacro)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _CMacro<EncodingT> > nativeCMacro;
		if (check_cMacro(cMacro, nativeCMacro))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedCMacro(nativeCMacro)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CMacroInterpreterAccess<EncodingT>::fillCppFile(shared_ptr< Base<EncodingT> >& cMacro)
{
	clearError();
	try
	{
		shared_ptr< _CMacro<EncodingT> > nativeCMacro;
		if (check_cMacro(cMacro, nativeCMacro))
		{
			m_object->fillCppFile(nativeCMacro);
			reset_cMacro(cMacro, nativeCMacro);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreterAccess<EncodingT>::isModifiedCMacro(const shared_ptr< Base<EncodingT> >& cMacro)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _CMacro<EncodingT> > nativeCMacro;
		if (check_cMacro(cMacro, nativeCMacro))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedCMacro(nativeCMacro)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CMacroInterpreterAccess<EncodingT>::updateCMacro(shared_ptr< Base<EncodingT> >& cMacro)
{
	clearError();
	try
	{
		shared_ptr< _CMacro<EncodingT> > nativeCMacro;
		if (check_cMacro(cMacro, nativeCMacro))
		{
			m_object->updateCMacro(nativeCMacro);
			reset_cMacro(cMacro, nativeCMacro);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CMacroInterpreterAccess<EncodingT>::insertCMacro(shared_ptr< Base<EncodingT> >& cMacro)
{
	clearError();
	try
	{
		shared_ptr< _CMacro<EncodingT> > nativeCMacro;
		if (check_cMacro(cMacro, nativeCMacro))
		{
			m_object->insertCMacro(nativeCMacro);
			reset_cMacro(cMacro, nativeCMacro);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CMacroInterpreterAccess<EncodingT>::deleteCMacro(shared_ptr< Base<EncodingT> >& cMacro)
{
	clearError();
	try
	{
		shared_ptr< _CMacro<EncodingT> > nativeCMacro;
		if (check_cMacro(cMacro, nativeCMacro))
		{
			m_object->deleteCMacro(nativeCMacro);
			reset_cMacro(cMacro, nativeCMacro);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CMacroInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void CMacroInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreterAccess<EncodingT>::getError(shared_ptr< Base<EncodingT> >& text) const
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

