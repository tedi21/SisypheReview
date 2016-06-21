#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppFileInterpreter<EncodingT>::CppFileInterpreter()
{
	setValue( shared_ptr< _CppFile<EncodingT> > (new _CppFile<EncodingT>()) );
}

template <class EncodingT>
CppFileInterpreter<EncodingT>::CppFileInterpreter(shared_ptr< _CppFile<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CppFileInterpreter<EncodingT>::CppFileInterpreter(shared_ptr< Base<EncodingT> > const& textFile,
				shared_ptr< Base<EncodingT> > const& path,
				shared_ptr< Base<EncodingT> > const& name,
				shared_ptr< Base<EncodingT> > const& linesCount)
{
	shared_ptr< _TextFile<EncodingT> > nativeTextFile;
	typename EncodingT::string_t nativePath;
	typename EncodingT::string_t nativeName;
	int nativeLinesCount;
	if (check_textFile(textFile, nativeTextFile) &&
		check_string<EncodingT>(path, nativePath) &&
		check_string<EncodingT>(name, nativeName) &&
		check_numeric(linesCount, nativeLinesCount))
	{
		setValue(shared_ptr< _CppFile<EncodingT> >(new _CppFile<EncodingT>(nativeTextFile,
				nativePath,
				nativeName,
				nativeLinesCount)));
	}
}

template <class EncodingT>
CppFileInterpreter<EncodingT>::~CppFileInterpreter()
{}

template <class EncodingT>
shared_ptr< _CppFile<EncodingT> > CppFileInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppFileInterpreter<EncodingT>::setValue(shared_ptr< _CppFile<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getPath() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getPath()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getName() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getName()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getLinesCount() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLinesCount()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getTextFile()
{
	return shared_ptr< Base<EncodingT> >( new TextFileInterpreter<EncodingT>(getValue()->getTextFile()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppFileType()
{
	return shared_ptr< Base<EncodingT> >( new CppFileTypeInterpreter<EncodingT>(getValue()->getCppFileType()) );
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::setTextFile(shared_ptr< Base<EncodingT> > const& textFile)
{
	shared_ptr< _TextFile<EncodingT> > nativeTextFile;
	if (check_textFile(textFile, nativeTextFile))
	{
		getValue()->setTextFile(nativeTextFile);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::setPath(shared_ptr< Base<EncodingT> > const& path)
{
	typename EncodingT::string_t nativePath;
	if (check_string<EncodingT>(path, nativePath))
	{
		getValue()->setPath(nativePath);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::setName(shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		getValue()->setName(nativeName);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::setCppFileType(shared_ptr< Base<EncodingT> > const& cppFileType)
{
	shared_ptr< _CppFileType<EncodingT> > nativeCppFileType;
	if (check_cppFileType(cppFileType, nativeCppFileType))
	{
		getValue()->setCppFileType(nativeCppFileType);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::setLinesCount(shared_ptr< Base<EncodingT> > const& linesCount)
{
	int nativeLinesCount;
	if (check_numeric(linesCount, nativeLinesCount))
	{
		getValue()->setLinesCount(nativeLinesCount);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasTextFile() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullTextFile()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppFileType() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppFileType()) );
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeTextFile()
{
	getValue()->eraseTextFile();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppFileType()
{
	getValue()->eraseCppFileType();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppDeclarationFunction(shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppDeclarationFunction(getValue()->getCppDeclarationFunctionsBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppDefinitionFunction(shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppDefinitionFunction(getValue()->getCppDefinitionFunctionsBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppInclude(shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppInclude(getValue()->getCppIncludesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppClass(shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppClass(getValue()->getCppClasssBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCppEnum(shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppEnum(getValue()->getCppEnumsBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeCMacro(shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCMacro(getValue()->getCMacrosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::removeDebugFileInfo(shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseDebugFileInfo(getValue()->getDebugFileInfosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCppDeclarationFunction(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& cppDeclarationFunction)
{
	int nativePosition;
	shared_ptr< _CppFunction<EncodingT> > nativeCppDeclarationFunction;
	if (check_numeric(n, nativePosition) &&
		check_cppFunction(cppDeclarationFunction, nativeCppDeclarationFunction))
	{
		getValue()->insertCppDeclarationFunction(getValue()->getCppDeclarationFunctionsBeginning()+nativePosition, nativeCppDeclarationFunction);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCppDefinitionFunction(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& cppDefinitionFunction)
{
	int nativePosition;
	shared_ptr< _CppFunction<EncodingT> > nativeCppDefinitionFunction;
	if (check_numeric(n, nativePosition) &&
		check_cppFunction(cppDefinitionFunction, nativeCppDefinitionFunction))
	{
		getValue()->insertCppDefinitionFunction(getValue()->getCppDefinitionFunctionsBeginning()+nativePosition, nativeCppDefinitionFunction);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCppInclude(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& cppInclude)
{
	int nativePosition;
	shared_ptr< _CppInclude<EncodingT> > nativeCppInclude;
	if (check_numeric(n, nativePosition) &&
		check_cppInclude(cppInclude, nativeCppInclude))
	{
		getValue()->insertCppInclude(getValue()->getCppIncludesBeginning()+nativePosition, nativeCppInclude);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCppClass(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& cppClass)
{
	int nativePosition;
	shared_ptr< _CppClass<EncodingT> > nativeCppClass;
	if (check_numeric(n, nativePosition) &&
		check_cppClass(cppClass, nativeCppClass))
	{
		getValue()->insertCppClass(getValue()->getCppClasssBeginning()+nativePosition, nativeCppClass);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCppEnum(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& cppEnum)
{
	int nativePosition;
	shared_ptr< _CppEnum<EncodingT> > nativeCppEnum;
	if (check_numeric(n, nativePosition) &&
		check_cppEnum(cppEnum, nativeCppEnum))
	{
		getValue()->insertCppEnum(getValue()->getCppEnumsBeginning()+nativePosition, nativeCppEnum);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertCMacro(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& cMacro)
{
	int nativePosition;
	shared_ptr< _CMacro<EncodingT> > nativeCMacro;
	if (check_numeric(n, nativePosition) &&
		check_cMacro(cMacro, nativeCMacro))
	{
		getValue()->insertCMacro(getValue()->getCMacrosBeginning()+nativePosition, nativeCMacro);
	}
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::insertDebugFileInfo(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& debugFileInfo)
{
	int nativePosition;
	shared_ptr< _DebugFileInfo<EncodingT> > nativeDebugFileInfo;
	if (check_numeric(n, nativePosition) &&
		check_debugFileInfo(debugFileInfo, nativeDebugFileInfo))
	{
		getValue()->insertDebugFileInfo(getValue()->getDebugFileInfosBeginning()+nativePosition, nativeDebugFileInfo);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppDeclarationFunction(shared_ptr< Base<EncodingT> > const& n)
{
	shared_ptr< Base<EncodingT> > res(new CppFunctionInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppFunctionInterpreter<EncodingT>(getValue()->getCppDeclarationFunctionAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppDefinitionFunction(shared_ptr< Base<EncodingT> > const& n)
{
	shared_ptr< Base<EncodingT> > res(new CppFunctionInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppFunctionInterpreter<EncodingT>(getValue()->getCppDefinitionFunctionAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppInclude(shared_ptr< Base<EncodingT> > const& n)
{
	shared_ptr< Base<EncodingT> > res(new CppIncludeInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppIncludeInterpreter<EncodingT>(getValue()->getCppIncludeAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppClass(shared_ptr< Base<EncodingT> > const& n)
{
	shared_ptr< Base<EncodingT> > res(new CppClassInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppClassInterpreter<EncodingT>(getValue()->getCppClassAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCppEnum(shared_ptr< Base<EncodingT> > const& n)
{
	shared_ptr< Base<EncodingT> > res(new CppEnumInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppEnumInterpreter<EncodingT>(getValue()->getCppEnumAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getCMacro(shared_ptr< Base<EncodingT> > const& n)
{
	shared_ptr< Base<EncodingT> > res(new CMacroInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CMacroInterpreter<EncodingT>(getValue()->getCMacroAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::getDebugFileInfo(shared_ptr< Base<EncodingT> > const& n)
{
	shared_ptr< Base<EncodingT> > res(new DebugFileInfoInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new DebugFileInfoInterpreter<EncodingT>(getValue()->getDebugFileInfoAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCppDeclarationFunctions()
{
	getValue()->clearCppDeclarationFunctions();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCppDefinitionFunctions()
{
	getValue()->clearCppDefinitionFunctions();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCppIncludes()
{
	getValue()->clearCppIncludes();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCppClasss()
{
	getValue()->clearCppClasss();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCppEnums()
{
	getValue()->clearCppEnums();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearCMacros()
{
	getValue()->clearCMacros();
}


template <class EncodingT>
void CppFileInterpreter<EncodingT>::clearDebugFileInfos()
{
	getValue()->clearDebugFileInfos();
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppDeclarationFunctions() const
{
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppDeclarationFunctionsEmpty()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppDefinitionFunctions() const
{
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppDefinitionFunctionsEmpty()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppIncludes() const
{
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppIncludesEmpty()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppClasss() const
{
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppClasssEmpty()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCppEnums() const
{
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppEnumsEmpty()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasCMacros() const
{
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCMacrosEmpty()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::hasDebugFileInfos() const
{
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isDebugFileInfosEmpty()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cppDeclarationFunctionsCount() const
{
	return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppDeclarationFunctionsSize()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cppDefinitionFunctionsCount() const
{
	return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppDefinitionFunctionsSize()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cppIncludesCount() const
{
	return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppIncludesSize()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cppClasssCount() const
{
	return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppClasssSize()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cppEnumsCount() const
{
	return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppEnumsSize()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::cMacrosCount() const
{
	return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCMacrosSize()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::debugFileInfosCount() const
{
	return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getDebugFileInfosSize()));
}

template <class EncodingT>
typename EncodingT::string_t CppFileInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new CppFileInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CppFileInterpreter<EncodingT>::getClassName() const
{
	return C("CppFile");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppFileInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppFile"), method, args, ret) ||
			tryInvoke(this, C("String"), method, args, ret))
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
bool check_cppFile(shared_ptr< Base<EncodingT> > const& val, shared_ptr< _CppFile<EncodingT> >& o)
{
	shared_ptr< CppFileInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppFileInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppFile expected, got " << A(val->getClassName());
	}
	return value;
}

template <class EncodingT>
bool reset_cppFile(shared_ptr< Base<EncodingT> >& val, shared_ptr< _CppFile<EncodingT> > const& o)
{
	shared_ptr< CppFileInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppFileInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppFile expected, got " << A(val->getClassName());
	}
	return value;
}

NAMESPACE_END

#undef C
#undef A

