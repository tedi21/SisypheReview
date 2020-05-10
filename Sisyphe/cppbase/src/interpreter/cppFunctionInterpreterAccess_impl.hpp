#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppFunctionInterpreterAccess<EncodingT>::CppFunctionInterpreterAccess()
{
	m_object = _CppFunctionAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t CppFunctionInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppFunctionInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppFunctionInterpreterAccess<EncodingT>::getClassName() const
{
	return C("CppFunctionAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppFunctionAccess"), method, args, ret) ||
			tryInvoke(this, C("Base"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in CppFunctionAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _CppFunction<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new CppFunctionInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreterAccess<EncodingT>::getAllCppFunctions()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllCppFunctions());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreterAccess<EncodingT>::getManyCppFunctions(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyCppFunctions(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreterAccess<EncodingT>::getOneCppFunction(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppFunctionInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res.reset(new CppFunctionInterpreter<EncodingT>(m_object->getOneCppFunction(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreterAccess<EncodingT>::selectOneCppFunction(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppFunctionInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new CppFunctionInterpreter<EncodingT>(m_object->selectOneCppFunction(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreterAccess<EncodingT>::selectManyCppFunctions(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyCppFunctions(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreterAccess<EncodingT>::isSelectedCppFunction(const boost::shared_ptr< Base<EncodingT> >& cppFunction)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
		if (check_cppFunction(cppFunction, nativeCppFunction))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedCppFunction(nativeCppFunction)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::fillCppDeclarationFile(boost::shared_ptr< Base<EncodingT> >& cppFunction)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
		if (check_cppFunction(cppFunction, nativeCppFunction))
		{
			m_object->fillCppDeclarationFile(nativeCppFunction);
			reset_cppFunction(cppFunction, nativeCppFunction);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::fillCppDefinitionFile(boost::shared_ptr< Base<EncodingT> >& cppFunction)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
		if (check_cppFunction(cppFunction, nativeCppFunction))
		{
			m_object->fillCppDefinitionFile(nativeCppFunction);
			reset_cppFunction(cppFunction, nativeCppFunction);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::fillCppClass(boost::shared_ptr< Base<EncodingT> >& cppFunction)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
		if (check_cppFunction(cppFunction, nativeCppFunction))
		{
			m_object->fillCppClass(nativeCppFunction);
			reset_cppFunction(cppFunction, nativeCppFunction);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::fillAllCppParameters(boost::shared_ptr< Base<EncodingT> >& cppFunction, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
		if (check_cppFunction(cppFunction, nativeCppFunction) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppParameters(nativeCppFunction, nativeNoWait);
			reset_cppFunction(cppFunction, nativeCppFunction);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::fillAllCppVariables(boost::shared_ptr< Base<EncodingT> >& cppFunction, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
		if (check_cppFunction(cppFunction, nativeCppFunction) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppVariables(nativeCppFunction, nativeNoWait);
			reset_cppFunction(cppFunction, nativeCppFunction);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::fillOneCppParameter(boost::shared_ptr< Base<EncodingT> >& refCppFunction,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFunction<EncodingT> > nativeRefCppFunction;
		long long nativeIdentifier;
		if (check_cppFunction(refCppFunction, nativeRefCppFunction) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppParameter(nativeRefCppFunction,
				nativeIdentifier,
				nativeNoWait);
			reset_cppFunction(refCppFunction, nativeRefCppFunction);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::fillOneCppVariable(boost::shared_ptr< Base<EncodingT> >& refCppFunction,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFunction<EncodingT> > nativeRefCppFunction;
		long long nativeIdentifier;
		if (check_cppFunction(refCppFunction, nativeRefCppFunction) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppVariable(nativeRefCppFunction,
				nativeIdentifier,
				nativeNoWait);
			reset_cppFunction(refCppFunction, nativeRefCppFunction);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::fillManyCppParameters(boost::shared_ptr< Base<EncodingT> >& cppFunction, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
		if (check_cppFunction(cppFunction, nativeCppFunction) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppParameters(nativeCppFunction, nativeFilter, nativeNoWait);
			reset_cppFunction(cppFunction, nativeCppFunction);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::fillManyCppVariables(boost::shared_ptr< Base<EncodingT> >& cppFunction, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
		if (check_cppFunction(cppFunction, nativeCppFunction) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppVariables(nativeCppFunction, nativeFilter, nativeNoWait);
			reset_cppFunction(cppFunction, nativeCppFunction);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreterAccess<EncodingT>::isModifiedCppFunction(const boost::shared_ptr< Base<EncodingT> >& cppFunction)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
		if (check_cppFunction(cppFunction, nativeCppFunction))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedCppFunction(nativeCppFunction)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::updateCppFunction(boost::shared_ptr< Base<EncodingT> >& cppFunction)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
		if (check_cppFunction(cppFunction, nativeCppFunction))
		{
			m_object->updateCppFunction(nativeCppFunction);
			reset_cppFunction(cppFunction, nativeCppFunction);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::insertCppFunction(boost::shared_ptr< Base<EncodingT> >& cppFunction)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
		if (check_cppFunction(cppFunction, nativeCppFunction))
		{
			m_object->insertCppFunction(nativeCppFunction);
			reset_cppFunction(cppFunction, nativeCppFunction);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::deleteCppFunction(boost::shared_ptr< Base<EncodingT> >& cppFunction)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
		if (check_cppFunction(cppFunction, nativeCppFunction))
		{
			m_object->deleteCppFunction(nativeCppFunction);
			reset_cppFunction(cppFunction, nativeCppFunction);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void CppFunctionInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFunctionInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

