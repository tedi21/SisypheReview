#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppVariableInterpreterAccess<EncodingT>::CppVariableInterpreterAccess()
{
	m_object = _CppVariableAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
CppVariableInterpreterAccess<EncodingT>::~CppVariableInterpreterAccess()
{}

template <class EncodingT>
typename EncodingT::string_t CppVariableInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppVariableInterpreterAccess<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new CppVariableInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppVariableInterpreterAccess<EncodingT>::getClassName() const
{
	return C("CppVariableAccess");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppVariableInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppVariableAccess"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in CppVariableAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppVariableInterpreterAccess<EncodingT>::convert_array(const std::vector< shared_ptr< _CppVariable<EncodingT> > >& value) const
{
	shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(shared_ptr< Base<EncodingT> >(new CppVariableInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppVariableInterpreterAccess<EncodingT>::getAllCppVariables()
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllCppVariables());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppVariableInterpreterAccess<EncodingT>::getManyCppVariables(const shared_ptr< Base<EncodingT> >& filter)
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyCppVariables(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppVariableInterpreterAccess<EncodingT>::getOneCppVariable(shared_ptr< Base<EncodingT> > const& identifier)
{
	shared_ptr< Base<EncodingT> > res(new CppVariableInterpreter<EncodingT>());
	clearError();
	try
	{
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier))
		{
			res.reset(new CppVariableInterpreter<EncodingT>(m_object->getOneCppVariable(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppVariableInterpreterAccess<EncodingT>::selectOneCppVariable(shared_ptr< Base<EncodingT> > const& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	shared_ptr< Base<EncodingT> > res(new CppVariableInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new CppVariableInterpreter<EncodingT>(m_object->selectOneCppVariable(nativeIdentifier,
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
shared_ptr< Base<EncodingT> > CppVariableInterpreterAccess<EncodingT>::selectManyCppVariables(const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyCppVariables(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppVariableInterpreterAccess<EncodingT>::cancelSelection()
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
shared_ptr< Base<EncodingT> > CppVariableInterpreterAccess<EncodingT>::isSelectedCppVariable(const shared_ptr< Base<EncodingT> >& cppVariable)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _CppVariable<EncodingT> > nativeCppVariable;
		if (check_cppVariable(cppVariable, nativeCppVariable))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedCppVariable(nativeCppVariable)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppVariableInterpreterAccess<EncodingT>::fillCppFunction(shared_ptr< Base<EncodingT> >& cppVariable)
{
	clearError();
	try
	{
		shared_ptr< _CppVariable<EncodingT> > nativeCppVariable;
		if (check_cppVariable(cppVariable, nativeCppVariable))
		{
			m_object->fillCppFunction(nativeCppVariable);
			reset_cppVariable(cppVariable, nativeCppVariable);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppVariableInterpreterAccess<EncodingT>::isModifiedCppVariable(const shared_ptr< Base<EncodingT> >& cppVariable)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _CppVariable<EncodingT> > nativeCppVariable;
		if (check_cppVariable(cppVariable, nativeCppVariable))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedCppVariable(nativeCppVariable)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppVariableInterpreterAccess<EncodingT>::updateCppVariable(shared_ptr< Base<EncodingT> >& cppVariable)
{
	clearError();
	try
	{
		shared_ptr< _CppVariable<EncodingT> > nativeCppVariable;
		if (check_cppVariable(cppVariable, nativeCppVariable))
		{
			m_object->updateCppVariable(nativeCppVariable);
			reset_cppVariable(cppVariable, nativeCppVariable);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppVariableInterpreterAccess<EncodingT>::insertCppVariable(shared_ptr< Base<EncodingT> >& cppVariable)
{
	clearError();
	try
	{
		shared_ptr< _CppVariable<EncodingT> > nativeCppVariable;
		if (check_cppVariable(cppVariable, nativeCppVariable))
		{
			m_object->insertCppVariable(nativeCppVariable);
			reset_cppVariable(cppVariable, nativeCppVariable);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppVariableInterpreterAccess<EncodingT>::deleteCppVariable(shared_ptr< Base<EncodingT> >& cppVariable)
{
	clearError();
	try
	{
		shared_ptr< _CppVariable<EncodingT> > nativeCppVariable;
		if (check_cppVariable(cppVariable, nativeCppVariable))
		{
			m_object->deleteCppVariable(nativeCppVariable);
			reset_cppVariable(cppVariable, nativeCppVariable);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppVariableInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void CppVariableInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppVariableInterpreterAccess<EncodingT>::getError(shared_ptr< Base<EncodingT> >& text) const
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

