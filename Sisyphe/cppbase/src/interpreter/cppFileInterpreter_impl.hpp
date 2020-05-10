#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppFileInterpreter<EncodingT>::CppFileInterpreter()
{
	m_value = boost::make_shared< _CppFile<EncodingT> >();
}

template <class EncodingT>
CppFileInterpreter<EncodingT>::CppFileInterpreter(boost::shared_ptr< _CppFile<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
CppFileInterpreter<EncodingT>::CppFileInterpreter(boost::shared_ptr< Base<EncodingT> > const& path,
				boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& linesCount,
				boost::shared_ptr< Base<EncodingT> > const& hash,
				boost::shared_ptr< Base<EncodingT> > const& analyzed)
{
	typename EncodingT::string_t nativePath;
	typename EncodingT::string_t nativeName;
	long long nativeLinesCount;
	long long nativeHash;
	long long nativeAnalyzed;
	if (check_string<EncodingT>(path, nativePath) &&
		check_string<EncodingT>(name, nativeName) &&
		check_numeric_i(linesCount, nativeLinesCount) &&
		check_numeric_i(hash, nativeHash) &&
		check_numeric_i(analyzed, nativeAnalyzed))
	{
		m_value = boost::make_shared< _CppFile<EncodingT> >(nativePath,
				nativeName,
				nativeLinesCount,
				nativeHash,
				nativeAnalyzed);
	}
}

template <class EncodingT>
boost::shared_ptr< _CppFile<EncodingT> > CppFileInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void CppFileInterpreter<EncodingT>::value(boost::shared_ptr< _CppFile<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getPath() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getPath()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getLinesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLinesCount()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getHash() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getHash()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getAnalyzed() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getAnalyzed()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getTextFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new TextFileInterpreter<EncodingT>(m_value->getTextFile()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppFileType()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFileTypeInterpreter<EncodingT>(m_value->getCppFileType()) );
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::setTextFile(boost::shared_ptr< Base<EncodingT> > const& textFile)
{
	boost::shared_ptr< _TextFile<EncodingT> > nativeTextFile;
	if (check_textFile(textFile, nativeTextFile))
	{
		m_value->setTextFile(nativeTextFile);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::setPath(boost::shared_ptr< Base<EncodingT> > const& path)
{
	typename EncodingT::string_t nativePath;
	if (check_string<EncodingT>(path, nativePath))
	{
		m_value->setPath(nativePath);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		m_value->setName(nativeName);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::setCppFileType(boost::shared_ptr< Base<EncodingT> > const& cppFileType)
{
	boost::shared_ptr< _CppFileType<EncodingT> > nativeCppFileType;
	if (check_cppFileType(cppFileType, nativeCppFileType))
	{
		m_value->setCppFileType(nativeCppFileType);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::setLinesCount(boost::shared_ptr< Base<EncodingT> > const& linesCount)
{
	long long nativeLinesCount;
	if (check_numeric_i(linesCount, nativeLinesCount))
	{
		m_value->setLinesCount(nativeLinesCount);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::setHash(boost::shared_ptr< Base<EncodingT> > const& hash)
{
	long long nativeHash;
	if (check_numeric_i(hash, nativeHash))
	{
		m_value->setHash(nativeHash);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::setAnalyzed(boost::shared_ptr< Base<EncodingT> > const& analyzed)
{
	long long nativeAnalyzed;
	if (check_numeric_i(analyzed, nativeAnalyzed))
	{
		m_value->setAnalyzed(nativeAnalyzed);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasTextFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullTextFile()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppFileType() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppFileType()) );
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeTextFile()
{
	m_value->eraseTextFile();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppFileType()
{
	m_value->eraseCppFileType();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppDeclarationFunction(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppDeclarationFunction(m_value->getCppDeclarationFunctionsBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppDefinitionFunction(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppDefinitionFunction(m_value->getCppDefinitionFunctionsBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppClass(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppClass(m_value->getCppClasssBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppInclude(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppInclude(m_value->getCppIncludesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppVariable(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppVariable(m_value->getCppVariablesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppEnum(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppEnum(m_value->getCppEnumsBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCMacro(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCMacro(m_value->getCMacrosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppNotice(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppNotice(m_value->getCppNoticesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCppDeclarationFunction(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppDeclarationFunction)
{
	size_t nativePosition;
	boost::shared_ptr< _CppFunction<EncodingT> > nativeCppDeclarationFunction;
	if (check_numeric_i(n, nativePosition) &&
		check_cppFunction(cppDeclarationFunction, nativeCppDeclarationFunction))
	{
		m_value->insertCppDeclarationFunction(m_value->getCppDeclarationFunctionsBeginning()+nativePosition, nativeCppDeclarationFunction);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCppDefinitionFunction(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppDefinitionFunction)
{
	size_t nativePosition;
	boost::shared_ptr< _CppFunction<EncodingT> > nativeCppDefinitionFunction;
	if (check_numeric_i(n, nativePosition) &&
		check_cppFunction(cppDefinitionFunction, nativeCppDefinitionFunction))
	{
		m_value->insertCppDefinitionFunction(m_value->getCppDefinitionFunctionsBeginning()+nativePosition, nativeCppDefinitionFunction);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCppClass(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppClass)
{
	size_t nativePosition;
	boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
	if (check_numeric_i(n, nativePosition) &&
		check_cppClass(cppClass, nativeCppClass))
	{
		m_value->insertCppClass(m_value->getCppClasssBeginning()+nativePosition, nativeCppClass);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCppInclude(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppInclude)
{
	size_t nativePosition;
	boost::shared_ptr< _CppInclude<EncodingT> > nativeCppInclude;
	if (check_numeric_i(n, nativePosition) &&
		check_cppInclude(cppInclude, nativeCppInclude))
	{
		m_value->insertCppInclude(m_value->getCppIncludesBeginning()+nativePosition, nativeCppInclude);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCppVariable(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppVariable)
{
	size_t nativePosition;
	boost::shared_ptr< _CppVariable<EncodingT> > nativeCppVariable;
	if (check_numeric_i(n, nativePosition) &&
		check_cppVariable(cppVariable, nativeCppVariable))
	{
		m_value->insertCppVariable(m_value->getCppVariablesBeginning()+nativePosition, nativeCppVariable);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCppEnum(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppEnum)
{
	size_t nativePosition;
	boost::shared_ptr< _CppEnum<EncodingT> > nativeCppEnum;
	if (check_numeric_i(n, nativePosition) &&
		check_cppEnum(cppEnum, nativeCppEnum))
	{
		m_value->insertCppEnum(m_value->getCppEnumsBeginning()+nativePosition, nativeCppEnum);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCMacro(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cMacro)
{
	size_t nativePosition;
	boost::shared_ptr< _CMacro<EncodingT> > nativeCMacro;
	if (check_numeric_i(n, nativePosition) &&
		check_cMacro(cMacro, nativeCMacro))
	{
		m_value->insertCMacro(m_value->getCMacrosBeginning()+nativePosition, nativeCMacro);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCppNotice(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppNotice)
{
	size_t nativePosition;
	boost::shared_ptr< _CppNotice<EncodingT> > nativeCppNotice;
	if (check_numeric_i(n, nativePosition) &&
		check_cppNotice(cppNotice, nativeCppNotice))
	{
		m_value->insertCppNotice(m_value->getCppNoticesBeginning()+nativePosition, nativeCppNotice);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppDeclarationFunction(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppFunctionInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new CppFunctionInterpreter<EncodingT>(m_value->getCppDeclarationFunctionAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppDefinitionFunction(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppFunctionInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new CppFunctionInterpreter<EncodingT>(m_value->getCppDefinitionFunctionAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppClass(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppClassInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new CppClassInterpreter<EncodingT>(m_value->getCppClassAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppInclude(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppIncludeInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new CppIncludeInterpreter<EncodingT>(m_value->getCppIncludeAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppVariable(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppVariableInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new CppVariableInterpreter<EncodingT>(m_value->getCppVariableAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppEnum(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppEnumInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new CppEnumInterpreter<EncodingT>(m_value->getCppEnumAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCMacro(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CMacroInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new CMacroInterpreter<EncodingT>(m_value->getCMacroAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppNotice(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppNoticeInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new CppNoticeInterpreter<EncodingT>(m_value->getCppNoticeAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCppDeclarationFunctions()
{
	m_value->clearCppDeclarationFunctions();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCppDefinitionFunctions()
{
	m_value->clearCppDefinitionFunctions();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCppClasss()
{
	m_value->clearCppClasss();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCppIncludes()
{
	m_value->clearCppIncludes();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCppVariables()
{
	m_value->clearCppVariables();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCppEnums()
{
	m_value->clearCppEnums();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCMacros()
{
	m_value->clearCMacros();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCppNotices()
{
	m_value->clearCppNotices();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppDeclarationFunctions() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppDeclarationFunctionsEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppDefinitionFunctions() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppDefinitionFunctionsEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppClasss() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppClasssEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppIncludes() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppIncludesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppVariables() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppVariablesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppEnums() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppEnumsEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCMacros() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCMacrosEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppNotices() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppNoticesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cppDeclarationFunctionsCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppDeclarationFunctionsSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cppDefinitionFunctionsCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppDefinitionFunctionsSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cppClasssCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppClasssSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cppIncludesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppIncludesSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cppVariablesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppVariablesSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cppEnumsCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppEnumsSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cMacrosCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCMacrosSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cppNoticesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppNoticesSize()));
}

template <class EncodingT>
typename EncodingT::string_t CppFileInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppFileInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t CppFileInterpreter<EncodingT>::getClassName() const
{
	return C("CppFile");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppFile"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppFile, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppFile(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppFile<EncodingT> >& o)
{
	boost::shared_ptr< CppFileInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppFileInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppFile expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cppFile(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppFile<EncodingT> > const& o)
{
	boost::shared_ptr< CppFileInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppFileInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppFile expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

