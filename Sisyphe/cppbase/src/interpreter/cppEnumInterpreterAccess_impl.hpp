#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppEnumInterpreterAccess<EncodingT>::CppEnumInterpreterAccess()
{
	m_object = _CppEnumAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t CppEnumInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppEnumInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppEnumInterpreterAccess<EncodingT>::getClassName() const
{
	return UCS("CppEnumAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("CppEnumAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppEnumAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _CppEnum<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new CppEnumInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreterAccess<EncodingT>::getAllCppEnums()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllCppEnums());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreterAccess<EncodingT>::getManyCppEnums(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyCppEnums(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreterAccess<EncodingT>::getOneCppEnum(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< CppEnumInterpreter<EncodingT> > res(new CppEnumInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res->value(m_object->getOneCppEnum(nativeIdentifier));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreterAccess<EncodingT>::selectOneCppEnum(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< CppEnumInterpreter<EncodingT> > res(new CppEnumInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res->value(m_object->selectOneCppEnum(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreterAccess<EncodingT>::selectManyCppEnums(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyCppEnums(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppEnumInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreterAccess<EncodingT>::isSelectedCppEnum(const boost::shared_ptr< Base<EncodingT> >& cppEnum)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppEnum<EncodingT> > nativeCppEnum;
		if (check_cppEnum(cppEnum, nativeCppEnum))
		{
			res->value(m_object->isSelectedCppEnum(nativeCppEnum));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppEnumInterpreterAccess<EncodingT>::fillCppFile(boost::shared_ptr< Base<EncodingT> >& cppEnum)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppEnum<EncodingT> > nativeCppEnum;
		if (check_cppEnum(cppEnum, nativeCppEnum))
		{
			m_object->fillCppFile(nativeCppEnum);
			reset_cppEnum(cppEnum, nativeCppEnum);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppEnumInterpreterAccess<EncodingT>::fillCppClass(boost::shared_ptr< Base<EncodingT> >& cppEnum)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppEnum<EncodingT> > nativeCppEnum;
		if (check_cppEnum(cppEnum, nativeCppEnum))
		{
			m_object->fillCppClass(nativeCppEnum);
			reset_cppEnum(cppEnum, nativeCppEnum);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppEnumInterpreterAccess<EncodingT>::fillAllCppEnumConstants(boost::shared_ptr< Base<EncodingT> >& cppEnum, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppEnum<EncodingT> > nativeCppEnum;
		if (check_cppEnum(cppEnum, nativeCppEnum) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppEnumConstants(nativeCppEnum, nativeNoWait);
			reset_cppEnum(cppEnum, nativeCppEnum);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppEnumInterpreterAccess<EncodingT>::fillOneCppEnumConstant(boost::shared_ptr< Base<EncodingT> >& refCppEnum,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppEnum<EncodingT> > nativeRefCppEnum;
		long long nativeIdentifier;
		if (check_cppEnum(refCppEnum, nativeRefCppEnum) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppEnumConstant(nativeRefCppEnum,
				nativeIdentifier,
				nativeNoWait);
			reset_cppEnum(refCppEnum, nativeRefCppEnum);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppEnumInterpreterAccess<EncodingT>::fillManyCppEnumConstants(boost::shared_ptr< Base<EncodingT> >& cppEnum, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppEnum<EncodingT> > nativeCppEnum;
		if (check_cppEnum(cppEnum, nativeCppEnum) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppEnumConstants(nativeCppEnum, nativeFilter, nativeNoWait);
			reset_cppEnum(cppEnum, nativeCppEnum);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreterAccess<EncodingT>::isModifiedCppEnum(const boost::shared_ptr< Base<EncodingT> >& cppEnum)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppEnum<EncodingT> > nativeCppEnum;
		if (check_cppEnum(cppEnum, nativeCppEnum))
		{
			res->value(m_object->isModifiedCppEnum(nativeCppEnum));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppEnumInterpreterAccess<EncodingT>::updateCppEnum(boost::shared_ptr< Base<EncodingT> >& cppEnum)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppEnum<EncodingT> > nativeCppEnum;
		if (check_cppEnum(cppEnum, nativeCppEnum))
		{
			m_object->updateCppEnum(nativeCppEnum);
			reset_cppEnum(cppEnum, nativeCppEnum);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppEnumInterpreterAccess<EncodingT>::insertCppEnum(boost::shared_ptr< Base<EncodingT> >& cppEnum)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppEnum<EncodingT> > nativeCppEnum;
		if (check_cppEnum(cppEnum, nativeCppEnum))
		{
			m_object->insertCppEnum(nativeCppEnum);
			reset_cppEnum(cppEnum, nativeCppEnum);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppEnumInterpreterAccess<EncodingT>::deleteCppEnum(boost::shared_ptr< Base<EncodingT> >& cppEnum)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppEnum<EncodingT> > nativeCppEnum;
		if (check_cppEnum(cppEnum, nativeCppEnum))
		{
			m_object->deleteCppEnum(nativeCppEnum);
			reset_cppEnum(cppEnum, nativeCppEnum);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppEnumInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void CppEnumInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppEnumInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

