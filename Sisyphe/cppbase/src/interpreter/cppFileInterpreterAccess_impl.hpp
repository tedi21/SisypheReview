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
CppFileInterpreterAccess<EncodingT>::~CppFileInterpreterAccess()
{}

template <class EncodingT>
typename EncodingT::string_t CppFileInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new CppFileInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CppFileInterpreterAccess<EncodingT>::getClassName() const
{
	return C("CppFileAccess");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppFileAccess"), method, args, ret))
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
shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::convert_array(const std::vector< shared_ptr< _CppFile<EncodingT> > >& value) const
{
	shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(shared_ptr< Base<EncodingT> >(new CppFileInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::getAllCppFiles()
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
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
shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::getManyCppFiles(const shared_ptr< Base<EncodingT> >& filter)
{
	shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
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
shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::getOneCppFile(shared_ptr< Base<EncodingT> > const& textFile)
{
	shared_ptr< Base<EncodingT> > res(new CppFileInterpreter<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile))
		{
			res.reset(new CppFileInterpreter<EncodingT>(m_object->getOneCppFile(nativeTextFile)));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::selectOneCppFile(shared_ptr< Base<EncodingT> > const& textFile,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	shared_ptr< Base<EncodingT> > res(new CppFileInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _TextFile<EncodingT> > nativeTextFile;
		if (check_textFile(textFile, nativeTextFile) &&
			check_bool(nowait, nativeNoWait))
		{
			res.reset(new CppFileInterpreter<EncodingT>(m_object->selectOneCppFile(nativeTextFile,
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
shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::selectManyCppFiles(const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
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
shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::isSelectedCppFile(const shared_ptr< Base<EncodingT> >& cppFile)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillCppFileType(shared_ptr< Base<EncodingT> >& cppFile)
{
	clearError();
	try
	{
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillAllCppDeclarationFunctions(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillAllCppDefinitionFunctions(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillAllCppIncludes(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillAllCppClasss(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillAllCppEnums(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillAllCMacros(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillAllDebugFileInfos(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) && 
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillAllDebugFileInfos(nativeCppFile, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void CppFileInterpreterAccess<EncodingT>::fillOneCppDeclarationFunction(shared_ptr< Base<EncodingT> >& refCppFile,
				const shared_ptr< Base<EncodingT> >& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		int nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric(identifier, nativeIdentifier) &&
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
void CppFileInterpreterAccess<EncodingT>::fillOneCppDefinitionFunction(shared_ptr< Base<EncodingT> >& refCppFile,
				const shared_ptr< Base<EncodingT> >& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		int nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric(identifier, nativeIdentifier) &&
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
void CppFileInterpreterAccess<EncodingT>::fillOneCppInclude(shared_ptr< Base<EncodingT> >& refCppFile,
				const shared_ptr< Base<EncodingT> >& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		int nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric(identifier, nativeIdentifier) &&
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
void CppFileInterpreterAccess<EncodingT>::fillOneCppClass(shared_ptr< Base<EncodingT> >& refCppFile,
				const shared_ptr< Base<EncodingT> >& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		int nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric(identifier, nativeIdentifier) &&
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
void CppFileInterpreterAccess<EncodingT>::fillOneCppEnum(shared_ptr< Base<EncodingT> >& refCppFile,
				const shared_ptr< Base<EncodingT> >& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		int nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric(identifier, nativeIdentifier) &&
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
void CppFileInterpreterAccess<EncodingT>::fillOneCMacro(shared_ptr< Base<EncodingT> >& refCppFile,
				const shared_ptr< Base<EncodingT> >& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		int nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric(identifier, nativeIdentifier) &&
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
void CppFileInterpreterAccess<EncodingT>::fillOneDebugFileInfo(shared_ptr< Base<EncodingT> >& refCppFile,
				const shared_ptr< Base<EncodingT> >& identifier,
				const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		shared_ptr< _CppFile<EncodingT> > nativeRefCppFile;
		int nativeIdentifier;
		if (check_cppFile(refCppFile, nativeRefCppFile) && 
			check_numeric(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillOneDebugFileInfo(nativeRefCppFile,
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
void CppFileInterpreterAccess<EncodingT>::fillManyCppDeclarationFunctions(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillManyCppDefinitionFunctions(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillManyCppIncludes(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillManyCppClasss(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillManyCppEnums(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillManyCMacros(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::fillManyDebugFileInfos(shared_ptr< Base<EncodingT> >& cppFile, const shared_ptr< Base<EncodingT> >& filter, const shared_ptr< Base<EncodingT> >& nowait)
{
	clearError();
	try
	{
		bool nativeNoWait;
		typename EncodingT::string_t nativeFilter;
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
		if (check_cppFile(cppFile, nativeCppFile) &&
			check_string<EncodingT>(filter, nativeFilter) &&
			check_bool(nowait, nativeNoWait))
		{
			m_object->fillManyDebugFileInfos(nativeCppFile, nativeFilter, nativeNoWait);
			reset_cppFile(cppFile, nativeCppFile);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::isModifiedCppFile(const shared_ptr< Base<EncodingT> >& cppFile)
{
	shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::updateCppFile(shared_ptr< Base<EncodingT> >& cppFile)
{
	clearError();
	try
	{
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::insertCppFile(shared_ptr< Base<EncodingT> >& cppFile)
{
	clearError();
	try
	{
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
void CppFileInterpreterAccess<EncodingT>::deleteCppFile(shared_ptr< Base<EncodingT> >& cppFile)
{
	clearError();
	try
	{
		shared_ptr< _CppFile<EncodingT> > nativeCppFile;
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
shared_ptr< Base<EncodingT> > CppFileInterpreterAccess<EncodingT>::getError(shared_ptr< Base<EncodingT> >& text) const
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

