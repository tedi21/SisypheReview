#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppFileInterpreterAccess<EncodingT>::CppFileInterpreterAccess()
{
	m_object = _CppFileAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t CppFileInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppFileInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppFileInterpreterAccess<EncodingT>::getClassName() const
{
	return C("CppFileAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppFileAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppFileAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _CppFile<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new CppFileInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::getAllCppFiles()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllCppFiles());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::getManyCppFiles(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyCppFiles(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::getOneCppFile(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppFileInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res.reset(new CppFileInterpreter<EncodingT>(m_object->getOneCppFile(nativeIdentifier)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::selectOneCppFile(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppFileInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new CppFileInterpreter<EncodingT>(m_object->selectOneCppFile(nativeIdentifier,
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
boost::shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::selectManyCppFiles(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
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
			res = convert_array(m_object->selectManyCppFiles(nativeFilter, nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::cancelSelection()
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
boost::shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::isSelectedCppFile(const boost::shared_ptr< Base<EncodingT> >& cppFile)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile))
		{
			res.reset(new Bool<EncodingT>(m_object->isSelectedCppFile(nativeCppFile)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillTextFile(boost::shared_ptr< Base<EncodingT> >& cppFile)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile))
		{
			m_object->fillTextFile(nativeCppFile);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillCppFileType(boost::shared_ptr< Base<EncodingT> >& cppFile)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile))
		{
			m_object->fillCppFileType(nativeCppFile);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillAllCppDeclarationFunctions(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppDeclarationFunctions(nativeCppFile, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillAllCppDefinitionFunctions(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppDefinitionFunctions(nativeCppFile, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillAllCppClasss(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppClasss(nativeCppFile, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillAllCppIncludes(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppIncludes(nativeCppFile, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillAllCppVariables(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppVariables(nativeCppFile, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillAllCppEnums(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppEnums(nativeCppFile, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillAllCMacros(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCMacros(nativeCppFile, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillAllCppNotices(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllCppNotices(nativeCppFile, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillOneCppDeclarationFunction(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		long long nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppDeclarationFunction(nativeRefCppFile,
				nativeIdentifier,
				nativeNoWait);
			reset_cppFile(refCppFile, nativeRefCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillOneCppDefinitionFunction(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		long long nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppDefinitionFunction(nativeRefCppFile,
				nativeIdentifier,
				nativeNoWait);
			reset_cppFile(refCppFile, nativeRefCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillOneCppClass(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		long long nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppClass(nativeRefCppFile,
				nativeIdentifier,
				nativeNoWait);
			reset_cppFile(refCppFile, nativeRefCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillOneCppInclude(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		long long nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppInclude(nativeRefCppFile,
				nativeIdentifier,
				nativeNoWait);
			reset_cppFile(refCppFile, nativeRefCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillOneCppVariable(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		long long nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppVariable(nativeRefCppFile,
				nativeIdentifier,
				nativeNoWait);
			reset_cppFile(refCppFile, nativeRefCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillOneCppEnum(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		long long nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppEnum(nativeRefCppFile,
				nativeIdentifier,
				nativeNoWait);
			reset_cppFile(refCppFile, nativeRefCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillOneCMacro(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		long long nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCMacro(nativeRefCppFile,
				nativeIdentifier,
				nativeNoWait);
			reset_cppFile(refCppFile, nativeRefCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillOneCppNotice(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		boost::shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		long long nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneCppNotice(nativeRefCppFile,
				nativeIdentifier,
				nativeNoWait);
			reset_cppFile(refCppFile, nativeRefCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillManyCppDeclarationFunctions(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppDeclarationFunctions(nativeCppFile, nativeFilter, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillManyCppDefinitionFunctions(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppDefinitionFunctions(nativeCppFile, nativeFilter, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillManyCppClasss(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppClasss(nativeCppFile, nativeFilter, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillManyCppIncludes(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppIncludes(nativeCppFile, nativeFilter, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillManyCppVariables(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppVariables(nativeCppFile, nativeFilter, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillManyCppEnums(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppEnums(nativeCppFile, nativeFilter, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillManyCMacros(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCMacros(nativeCppFile, nativeFilter, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillManyCppNotices(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyCppNotices(nativeCppFile, nativeFilter, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::isModifiedCppFile(const boost::shared_ptr< Base<EncodingT> >& cppFile)
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile))
		{
			res.reset(new Bool<EncodingT>(m_object->isModifiedCppFile(nativeCppFile)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::updateCppFile(boost::shared_ptr< Base<EncodingT> >& cppFile)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile))
		{
			m_object->updateCppFile(nativeCppFile);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::insertCppFile(boost::shared_ptr< Base<EncodingT> >& cppFile)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile))
		{
			m_object->insertCppFile(nativeCppFile);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::deleteCppFile(boost::shared_ptr< Base<EncodingT> >& cppFile)
{
	clearError();
	try
	{
		boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile))
		{
			m_object->deleteCppFile(nativeCppFile);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
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

