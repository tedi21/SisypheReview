#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppFileTypeInterpreterAccess<EncodingT>::CppFileTypeInterpreterAccess()
{
	m_object = _CppFileTypeAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
CppFileTypeInterpreterAccess<EncodingT>::~CppFileTypeInterpreterAccess()
{}

template <class EncodingT>
typename EncodingT::string_t CppFileTypeInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileTypeInterpreterAccess<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new CppFileTypeInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppFileTypeInterpreterAccess<EncodingT>::getClassName() const
{
	return C("CppFileTypeAccess");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileTypeInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppFileTypeAccess"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in CppFileTypeAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileTypeInterpreterAccess<EncodingT>::convert_array(const std::vector< shared_ptr< _CppFileType<EncodingT> > >& value) const
{
	shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(shared_ptr< Base<EncodingT> >(new CppFileTypeInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileTypeInterpreterAccess<EncodingT>::getAllCppFileTypes()
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllCppFileTypes());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileTypeInterpreterAccess<EncodingT>::getManyCppFileTypes(const shared_ptr< Base<EncodingT> >& filter)
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyCppFileTypes(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileTypeInterpreterAccess<EncodingT>::getOneCppFileType(shared_ptr< Base<EncodingT> > const& identifier)
{
	shared_ptr< Base<EncodingT> > res(new CppFileTypeInterpreter<EncodingT>());
	clearError();
	try
	{
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier))
		{
			res.reset(new CppFileTypeInterpreter<EncodingT>(m_object->getOneCppFileType(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileTypeInterpreterAccess<EncodingT>::selectOneCppFileType(shared_ptr< Base<EncodingT> > const& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	shared_ptr< Base<EncodingT> > res(new CppFileTypeInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		int nativeIdentifier;
		if (check_numeric(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new CppFileTypeInterpreter<EncodingT>(m_object->selectOneCppFileType(nativeIdentifier,
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
void CppFileTypeInterpreterAccess<EncodingT>::cancelSelection()
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
shared_ptr< Base<EncodingT> > CppFileTypeInterpreterAccess<EncodingT>::isSelectedCppFileType(const shared_ptr< Base<EncodingT> >& cppFileType)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _CppFileType<EncodingT> > nativeCppFileType;
		if (check_cppFileType(cppFileType, nativeCppFileType))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedCppFileType(nativeCppFileType)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppFileTypeInterpreterAccess<EncodingT>::fillAllCppFiles(shared_ptr< Base<EncodingT> >& cppFileType, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFileType<EncodingT> > nativeCppFileType;
		if (check_cppFileType(cppFileType, nativeCppFileType) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppFiles(nativeCppFileType, nativeNoWait);
			reset_cppFileType(cppFileType, nativeCppFileType);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileTypeInterpreterAccess<EncodingT>::fillOneCppFile(shared_ptr< Base<EncodingT> >& refCppFileType,
				const shared_ptr< Base<EncodingT> >& textFile,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFileType<EncodingT> > nativeRefCppFileType;
		shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_cppFileType(refCppFileType, nativeRefCppFileType) && 
			check_textFile(textFile, nativeTextFile) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppFile(nativeRefCppFileType,
				nativeTextFile,
				nativeNoWait);
			reset_cppFileType(refCppFileType, nativeRefCppFileType);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileTypeInterpreterAccess<EncodingT>::fillManyCppFiles(shared_ptr< Base<EncodingT> >& cppFileType, const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		shared_ptr< _CppFileType<EncodingT> > nativeCppFileType;
		if (check_cppFileType(cppFileType, nativeCppFileType) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppFiles(nativeCppFileType, nativeFilter, nativeNoWait);
			reset_cppFileType(cppFileType, nativeCppFileType);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileTypeInterpreterAccess<EncodingT>::isModifiedCppFileType(const shared_ptr< Base<EncodingT> >& cppFileType)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _CppFileType<EncodingT> > nativeCppFileType;
		if (check_cppFileType(cppFileType, nativeCppFileType))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedCppFileType(nativeCppFileType)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppFileTypeInterpreterAccess<EncodingT>::updateCppFileType(shared_ptr< Base<EncodingT> >& cppFileType)
{
	clearError();
	try
	{
		shared_ptr< _CppFileType<EncodingT> > nativeCppFileType;
		if (check_cppFileType(cppFileType, nativeCppFileType))
		{
			m_object->updateCppFileType(nativeCppFileType);
			reset_cppFileType(cppFileType, nativeCppFileType);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileTypeInterpreterAccess<EncodingT>::insertCppFileType(shared_ptr< Base<EncodingT> >& cppFileType)
{
	clearError();
	try
	{
		shared_ptr< _CppFileType<EncodingT> > nativeCppFileType;
		if (check_cppFileType(cppFileType, nativeCppFileType))
		{
			m_object->insertCppFileType(nativeCppFileType);
			reset_cppFileType(cppFileType, nativeCppFileType);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileTypeInterpreterAccess<EncodingT>::deleteCppFileType(shared_ptr< Base<EncodingT> >& cppFileType)
{
	clearError();
	try
	{
		shared_ptr< _CppFileType<EncodingT> > nativeCppFileType;
		if (check_cppFileType(cppFileType, nativeCppFileType))
		{
			m_object->deleteCppFileType(nativeCppFileType);
			reset_cppFileType(cppFileType, nativeCppFileType);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileTypeInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void CppFileTypeInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileTypeInterpreterAccess<EncodingT>::getError(shared_ptr< Base<EncodingT> >& text) const
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

