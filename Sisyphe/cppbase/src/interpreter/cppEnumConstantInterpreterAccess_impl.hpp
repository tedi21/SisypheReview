#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppEnumConstantInterpreterAccess<EncodingT>::CppEnumConstantInterpreterAccess()
{
	m_object = _CppEnumConstantAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t CppEnumConstantInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppEnumConstantInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppEnumConstantInterpreterAccess<EncodingT>::getClassName() const
{
	return UCS("CppEnumConstantAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("CppEnumConstantAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppEnumConstantAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new CppEnumConstantInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreterAccess<EncodingT>::getAllCppEnumConstants()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllCppEnumConstants());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreterAccess<EncodingT>::getManyCppEnumConstants(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyCppEnumConstants(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreterAccess<EncodingT>::getOneCppEnumConstant(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< CppEnumConstantInterpreter<EncodingT> > res(new CppEnumConstantInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res->value(m_object->getOneCppEnumConstant(nativeIdentifier));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreterAccess<EncodingT>::selectOneCppEnumConstant(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< CppEnumConstantInterpreter<EncodingT> > res(new CppEnumConstantInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res->value(m_object->selectOneCppEnumConstant(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreterAccess<EncodingT>::selectManyCppEnumConstants(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyCppEnumConstants(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppEnumConstantInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreterAccess<EncodingT>::isSelectedCppEnumConstant(const boost::shared_ptr< Base<EncodingT> >& cppEnumConstant)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppEnumConstant<EncodingT> > nativeCppEnumConstant;
		if (check_cppEnumConstant(cppEnumConstant, nativeCppEnumConstant))
		{
			res->value(m_object->isSelectedCppEnumConstant(nativeCppEnumConstant));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppEnumConstantInterpreterAccess<EncodingT>::fillCppEnum(boost::shared_ptr< Base<EncodingT> >& cppEnumConstant)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppEnumConstant<EncodingT> > nativeCppEnumConstant;
		if (check_cppEnumConstant(cppEnumConstant, nativeCppEnumConstant))
		{
			m_object->fillCppEnum(nativeCppEnumConstant);
			reset_cppEnumConstant(cppEnumConstant, nativeCppEnumConstant);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreterAccess<EncodingT>::isModifiedCppEnumConstant(const boost::shared_ptr< Base<EncodingT> >& cppEnumConstant)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppEnumConstant<EncodingT> > nativeCppEnumConstant;
		if (check_cppEnumConstant(cppEnumConstant, nativeCppEnumConstant))
		{
			res->value(m_object->isModifiedCppEnumConstant(nativeCppEnumConstant));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppEnumConstantInterpreterAccess<EncodingT>::updateCppEnumConstant(boost::shared_ptr< Base<EncodingT> >& cppEnumConstant)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppEnumConstant<EncodingT> > nativeCppEnumConstant;
		if (check_cppEnumConstant(cppEnumConstant, nativeCppEnumConstant))
		{
			m_object->updateCppEnumConstant(nativeCppEnumConstant);
			reset_cppEnumConstant(cppEnumConstant, nativeCppEnumConstant);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppEnumConstantInterpreterAccess<EncodingT>::insertCppEnumConstant(boost::shared_ptr< Base<EncodingT> >& cppEnumConstant)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppEnumConstant<EncodingT> > nativeCppEnumConstant;
		if (check_cppEnumConstant(cppEnumConstant, nativeCppEnumConstant))
		{
			m_object->insertCppEnumConstant(nativeCppEnumConstant);
			reset_cppEnumConstant(cppEnumConstant, nativeCppEnumConstant);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppEnumConstantInterpreterAccess<EncodingT>::deleteCppEnumConstant(boost::shared_ptr< Base<EncodingT> >& cppEnumConstant)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppEnumConstant<EncodingT> > nativeCppEnumConstant;
		if (check_cppEnumConstant(cppEnumConstant, nativeCppEnumConstant))
		{
			m_object->deleteCppEnumConstant(nativeCppEnumConstant);
			reset_cppEnumConstant(cppEnumConstant, nativeCppEnumConstant);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppEnumConstantInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void CppEnumConstantInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumConstantInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

