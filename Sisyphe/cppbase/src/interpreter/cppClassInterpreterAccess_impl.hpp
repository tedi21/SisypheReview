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
CppClassInterpreterAccess<EncodingT>::~CppClassInterpreterAccess()
{}

template <class EncodingT>
typename EncodingT::string_t CppClassInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new CppClassInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppClassInterpreterAccess<EncodingT>::getClassName() const
{
	return C("CppClassAccess");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppClassAccess"), method, args, ret))
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
shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::convert_array(const std::vector< shared_ptr< _CppClass<EncodingT> > >& value) const
{
	shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(shared_ptr< Base<EncodingT> >(new CppClassInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::getAllCppClasss()
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
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
shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::getManyCppClasss(const shared_ptr< Base<EncodingT> >& filter)
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
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
shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::getOneCppClass(shared_ptr< Base<EncodingT> > const& identifier)
{
	shared_ptr< Base<EncodingT> > res(new CppClassInterpreter<EncodingT>());
	clearError();
	try
	{
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier))
		{
			res.reset(new CppClassInterpreter<EncodingT>(m_object->getOneCppClass(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::selectOneCppClass(shared_ptr< Base<EncodingT> > const& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	shared_ptr< Base<EncodingT> > res(new CppClassInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new CppClassInterpreter<EncodingT>(m_object->selectOneCppClass(nativeIdentifier,
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
shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::selectManyCppClasss(const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
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
shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::isSelectedCppClass(const shared_ptr< Base<EncodingT> >& cppClass)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedCppClass(nativeCppClass)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::fillCppFile(shared_ptr< Base<EncodingT> >& cppClass)
{
	clearError();
	try
	{
		shared_ptr< _CppClass<EncodingT> > nativeCppClass;
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
void CppClassInterpreterAccess<EncodingT>::fillAllCppInheritances(shared_ptr< Base<EncodingT> >& cppClass, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppClass<EncodingT> > nativeCppClass;
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
void CppClassInterpreterAccess<EncodingT>::fillAllCppFunctions(shared_ptr< Base<EncodingT> >& cppClass, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppClass<EncodingT> > nativeCppClass;
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
void CppClassInterpreterAccess<EncodingT>::fillAllCppAttributes(shared_ptr< Base<EncodingT> >& cppClass, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppClass<EncodingT> > nativeCppClass;
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
void CppClassInterpreterAccess<EncodingT>::fillOneCppInheritance(shared_ptr< Base<EncodingT> >& refCppClass,
				const shared_ptr< Base<EncodingT> >& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppClass<EncodingT> > nativeRefCppClass;
		int nativeIdentifier;
		if (check_cppClass(refCppClass, nativeRefCppClass) && 
			check_numeric(identifier, nativeIdentifier) &&
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
void CppClassInterpreterAccess<EncodingT>::fillOneCppFunction(shared_ptr< Base<EncodingT> >& refCppClass,
				const shared_ptr< Base<EncodingT> >& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppClass<EncodingT> > nativeRefCppClass;
		int nativeIdentifier;
		if (check_cppClass(refCppClass, nativeRefCppClass) && 
			check_numeric(identifier, nativeIdentifier) &&
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
void CppClassInterpreterAccess<EncodingT>::fillOneCppAttribute(shared_ptr< Base<EncodingT> >& refCppClass,
				const shared_ptr< Base<EncodingT> >& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppClass<EncodingT> > nativeRefCppClass;
		int nativeIdentifier;
		if (check_cppClass(refCppClass, nativeRefCppClass) && 
			check_numeric(identifier, nativeIdentifier) &&
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
void CppClassInterpreterAccess<EncodingT>::fillManyCppInheritances(shared_ptr< Base<EncodingT> >& cppClass, const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		shared_ptr< _CppClass<EncodingT> > nativeCppClass;
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
void CppClassInterpreterAccess<EncodingT>::fillManyCppFunctions(shared_ptr< Base<EncodingT> >& cppClass, const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		shared_ptr< _CppClass<EncodingT> > nativeCppClass;
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
void CppClassInterpreterAccess<EncodingT>::fillManyCppAttributes(shared_ptr< Base<EncodingT> >& cppClass, const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		shared_ptr< _CppClass<EncodingT> > nativeCppClass;
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
shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::isModifiedCppClass(const shared_ptr< Base<EncodingT> >& cppClass)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _CppClass<EncodingT> > nativeCppClass;
		if (check_cppClass(cppClass, nativeCppClass))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedCppClass(nativeCppClass)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppClassInterpreterAccess<EncodingT>::updateCppClass(shared_ptr< Base<EncodingT> >& cppClass)
{
	clearError();
	try
	{
		shared_ptr< _CppClass<EncodingT> > nativeCppClass;
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
void CppClassInterpreterAccess<EncodingT>::insertCppClass(shared_ptr< Base<EncodingT> >& cppClass)
{
	clearError();
	try
	{
		shared_ptr< _CppClass<EncodingT> > nativeCppClass;
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
void CppClassInterpreterAccess<EncodingT>::deleteCppClass(shared_ptr< Base<EncodingT> >& cppClass)
{
	clearError();
	try
	{
		shared_ptr< _CppClass<EncodingT> > nativeCppClass;
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
shared_ptr< Base<EncodingT> > CppClassInterpreterAccess<EncodingT>::getError(shared_ptr< Base<EncodingT> >& text) const
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

