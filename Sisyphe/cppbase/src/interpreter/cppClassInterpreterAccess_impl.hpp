#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppClassInterpreterAccess<EncodingT>::CppClassInterpreterAccess()
{
	m_object = _CppClassAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t CppClassInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppClassInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppClassInterpreterAccess<EncodingT>::getClassName() const
{
	return UCS("CppClassAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("CppClassAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppClassAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _CppClass<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new CppClassInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::getAllCppClasss()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllCppClasss());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::getManyCppClasss(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyCppClasss(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::getOneCppClass(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< CppClassInterpreter<EncodingT> > res(new CppClassInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res->value(m_object->getOneCppClass(nativeIdentifier));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::selectOneCppClass(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< CppClassInterpreter<EncodingT> > res(new CppClassInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res->value(m_object->selectOneCppClass(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::selectManyCppClasss(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyCppClasss(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::isSelectedCppClass(const boost::shared_ptr< Base<EncodingT> >& cppClass)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass))
		{
			res->value(m_object->isSelectedCppClass(nativeCppClass));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillEncapsulationClass(boost::shared_ptr< Base<EncodingT> >& cppClass)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass))
		{
			m_object->fillEncapsulationClass(nativeCppClass);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillCppFile(boost::shared_ptr< Base<EncodingT> >& cppClass)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass))
		{
			m_object->fillCppFile(nativeCppClass);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillAllCppInheritances(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppInheritances(nativeCppClass, nativeNoWait);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillAllCppFunctions(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppFunctions(nativeCppClass, nativeNoWait);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillAllInternClasses(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllInternClasses(nativeCppClass, nativeNoWait);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillAllCppAttributes(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppAttributes(nativeCppClass, nativeNoWait);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillAllCppEnums(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppEnums(nativeCppClass, nativeNoWait);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillOneCppInheritance(boost::shared_ptr< Base<EncodingT> >& refCppClass,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppClass<EncodingT> > nativeRefCppClass;
		long long nativeIdentifier;
		if (check_cppClass(refCppClass, nativeRefCppClass) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppInheritance(nativeRefCppClass,
				nativeIdentifier,
				nativeNoWait);
			reset_cppClass(refCppClass, nativeRefCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillOneCppFunction(boost::shared_ptr< Base<EncodingT> >& refCppClass,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppClass<EncodingT> > nativeRefCppClass;
		long long nativeIdentifier;
		if (check_cppClass(refCppClass, nativeRefCppClass) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppFunction(nativeRefCppClass,
				nativeIdentifier,
				nativeNoWait);
			reset_cppClass(refCppClass, nativeRefCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillOneInternClasse(boost::shared_ptr< Base<EncodingT> >& refCppClass,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppClass<EncodingT> > nativeRefCppClass;
		long long nativeIdentifier;
		if (check_cppClass(refCppClass, nativeRefCppClass) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneInternClasse(nativeRefCppClass,
				nativeIdentifier,
				nativeNoWait);
			reset_cppClass(refCppClass, nativeRefCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillOneCppAttribute(boost::shared_ptr< Base<EncodingT> >& refCppClass,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppClass<EncodingT> > nativeRefCppClass;
		long long nativeIdentifier;
		if (check_cppClass(refCppClass, nativeRefCppClass) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppAttribute(nativeRefCppClass,
				nativeIdentifier,
				nativeNoWait);
			reset_cppClass(refCppClass, nativeRefCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillOneCppEnum(boost::shared_ptr< Base<EncodingT> >& refCppClass,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppClass<EncodingT> > nativeRefCppClass;
		long long nativeIdentifier;
		if (check_cppClass(refCppClass, nativeRefCppClass) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppEnum(nativeRefCppClass,
				nativeIdentifier,
				nativeNoWait);
			reset_cppClass(refCppClass, nativeRefCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillManyCppInheritances(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppInheritances(nativeCppClass, nativeFilter, nativeNoWait);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillManyCppFunctions(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppFunctions(nativeCppClass, nativeFilter, nativeNoWait);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillManyInternClasses(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyInternClasses(nativeCppClass, nativeFilter, nativeNoWait);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillManyCppAttributes(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppAttributes(nativeCppClass, nativeFilter, nativeNoWait);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillManyCppEnums(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppEnums(nativeCppClass, nativeFilter, nativeNoWait);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::isModifiedCppClass(const boost::shared_ptr< Base<EncodingT> >& cppClass)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass))
		{
			res->value(m_object->isModifiedCppClass(nativeCppClass));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::updateCppClass(boost::shared_ptr< Base<EncodingT> >& cppClass)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass))
		{
			m_object->updateCppClass(nativeCppClass);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::insertCppClass(boost::shared_ptr< Base<EncodingT> >& cppClass)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass))
		{
			m_object->insertCppClass(nativeCppClass);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::deleteCppClass(boost::shared_ptr< Base<EncodingT> >& cppClass)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass))
		{
			m_object->deleteCppClass(nativeCppClass);
			reset_cppClass(cppClass, nativeCppClass);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

