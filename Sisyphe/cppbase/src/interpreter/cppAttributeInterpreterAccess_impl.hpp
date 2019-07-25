#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppAttributeInterpreterAccess<EncodingT>::CppAttributeInterpreterAccess()
{
	m_object = _CppAttributeAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t CppAttributeInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppAttributeInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppAttributeInterpreterAccess<EncodingT>::getClassName() const
{
	return C("CppAttributeAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppAttributeAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppAttributeAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new CppAttributeInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreterAccess<EncodingT>::getAllCppAttributes()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllCppAttributes());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreterAccess<EncodingT>::getManyCppAttributes(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyCppAttributes(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreterAccess<EncodingT>::getOneCppAttribute(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppAttributeInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res.reset(new CppAttributeInterpreter<EncodingT>(m_object->getOneCppAttribute(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreterAccess<EncodingT>::selectOneCppAttribute(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppAttributeInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new CppAttributeInterpreter<EncodingT>(m_object->selectOneCppAttribute(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreterAccess<EncodingT>::selectManyCppAttributes(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyCppAttributes(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppAttributeInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreterAccess<EncodingT>::isSelectedCppAttribute(const boost::shared_ptr< Base<EncodingT> >& cppAttribute)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppAttribute<EncodingT> > nativeCppAttribute;
		if (check_cppAttribute(cppAttribute, nativeCppAttribute))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedCppAttribute(nativeCppAttribute)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppAttributeInterpreterAccess<EncodingT>::fillCppClass(boost::shared_ptr< Base<EncodingT> >& cppAttribute)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppAttribute<EncodingT> > nativeCppAttribute;
		if (check_cppAttribute(cppAttribute, nativeCppAttribute))
		{
			m_object->fillCppClass(nativeCppAttribute);
			reset_cppAttribute(cppAttribute, nativeCppAttribute);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreterAccess<EncodingT>::isModifiedCppAttribute(const boost::shared_ptr< Base<EncodingT> >& cppAttribute)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppAttribute<EncodingT> > nativeCppAttribute;
		if (check_cppAttribute(cppAttribute, nativeCppAttribute))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedCppAttribute(nativeCppAttribute)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppAttributeInterpreterAccess<EncodingT>::updateCppAttribute(boost::shared_ptr< Base<EncodingT> >& cppAttribute)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppAttribute<EncodingT> > nativeCppAttribute;
		if (check_cppAttribute(cppAttribute, nativeCppAttribute))
		{
			m_object->updateCppAttribute(nativeCppAttribute);
			reset_cppAttribute(cppAttribute, nativeCppAttribute);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppAttributeInterpreterAccess<EncodingT>::insertCppAttribute(boost::shared_ptr< Base<EncodingT> >& cppAttribute)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppAttribute<EncodingT> > nativeCppAttribute;
		if (check_cppAttribute(cppAttribute, nativeCppAttribute))
		{
			m_object->insertCppAttribute(nativeCppAttribute);
			reset_cppAttribute(cppAttribute, nativeCppAttribute);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppAttributeInterpreterAccess<EncodingT>::deleteCppAttribute(boost::shared_ptr< Base<EncodingT> >& cppAttribute)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppAttribute<EncodingT> > nativeCppAttribute;
		if (check_cppAttribute(cppAttribute, nativeCppAttribute))
		{
			m_object->deleteCppAttribute(nativeCppAttribute);
			reset_cppAttribute(cppAttribute, nativeCppAttribute);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppAttributeInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void CppAttributeInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

