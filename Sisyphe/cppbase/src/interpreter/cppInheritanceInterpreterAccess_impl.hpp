#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppInheritanceInterpreterAccess<EncodingT>::CppInheritanceInterpreterAccess()
{
	m_object = _CppInheritanceAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t CppInheritanceInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppInheritanceInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppInheritanceInterpreterAccess<EncodingT>::getClassName() const
{
	return C("CppInheritanceAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppInheritanceAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppInheritanceAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _CppInheritance<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new CppInheritanceInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreterAccess<EncodingT>::getAllCppInheritances()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllCppInheritances());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreterAccess<EncodingT>::getManyCppInheritances(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyCppInheritances(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreterAccess<EncodingT>::getOneCppInheritance(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppInheritanceInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res.reset(new CppInheritanceInterpreter<EncodingT>(m_object->getOneCppInheritance(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreterAccess<EncodingT>::selectOneCppInheritance(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppInheritanceInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new CppInheritanceInterpreter<EncodingT>(m_object->selectOneCppInheritance(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreterAccess<EncodingT>::selectManyCppInheritances(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyCppInheritances(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppInheritanceInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreterAccess<EncodingT>::isSelectedCppInheritance(const boost::shared_ptr< Base<EncodingT> >& cppInheritance)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppInheritance<EncodingT> > nativeCppInheritance;
		if (check_cppInheritance(cppInheritance, nativeCppInheritance))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedCppInheritance(nativeCppInheritance)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppInheritanceInterpreterAccess<EncodingT>::fillDerived(boost::shared_ptr< Base<EncodingT> >& cppInheritance)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppInheritance<EncodingT> > nativeCppInheritance;
		if (check_cppInheritance(cppInheritance, nativeCppInheritance))
		{
			m_object->fillDerived(nativeCppInheritance);
			reset_cppInheritance(cppInheritance, nativeCppInheritance);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreterAccess<EncodingT>::isModifiedCppInheritance(const boost::shared_ptr< Base<EncodingT> >& cppInheritance)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppInheritance<EncodingT> > nativeCppInheritance;
		if (check_cppInheritance(cppInheritance, nativeCppInheritance))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedCppInheritance(nativeCppInheritance)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppInheritanceInterpreterAccess<EncodingT>::updateCppInheritance(boost::shared_ptr< Base<EncodingT> >& cppInheritance)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppInheritance<EncodingT> > nativeCppInheritance;
		if (check_cppInheritance(cppInheritance, nativeCppInheritance))
		{
			m_object->updateCppInheritance(nativeCppInheritance);
			reset_cppInheritance(cppInheritance, nativeCppInheritance);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppInheritanceInterpreterAccess<EncodingT>::insertCppInheritance(boost::shared_ptr< Base<EncodingT> >& cppInheritance)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppInheritance<EncodingT> > nativeCppInheritance;
		if (check_cppInheritance(cppInheritance, nativeCppInheritance))
		{
			m_object->insertCppInheritance(nativeCppInheritance);
			reset_cppInheritance(cppInheritance, nativeCppInheritance);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppInheritanceInterpreterAccess<EncodingT>::deleteCppInheritance(boost::shared_ptr< Base<EncodingT> >& cppInheritance)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppInheritance<EncodingT> > nativeCppInheritance;
		if (check_cppInheritance(cppInheritance, nativeCppInheritance))
		{
			m_object->deleteCppInheritance(nativeCppInheritance);
			reset_cppInheritance(cppInheritance, nativeCppInheritance);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppInheritanceInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void CppInheritanceInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

