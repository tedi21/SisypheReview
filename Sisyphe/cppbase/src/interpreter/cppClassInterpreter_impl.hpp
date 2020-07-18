#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppClassInterpreter<EncodingT>::CppClassInterpreter()
{
	m_value = boost::make_shared< _CppClass<EncodingT> >();
}

template <class EncodingT>
CppClassInterpreter<EncodingT>::CppClassInterpreter(boost::shared_ptr< _CppClass<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
CppClassInterpreter<EncodingT>::CppClassInterpreter(boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& fullName,
				boost::shared_ptr< Base<EncodingT> > const& accessSpecifier,
				boost::shared_ptr< Base<EncodingT> > const& isStruct,
				boost::shared_ptr< Base<EncodingT> > const& isInterface,
				boost::shared_ptr< Base<EncodingT> > const& isAbstract,
				boost::shared_ptr< Base<EncodingT> > const& isTemplate,
				boost::shared_ptr< Base<EncodingT> > const& linesCount,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	typename EncodingT::string_t nativeName;
	typename EncodingT::string_t nativeFullName;
	typename EncodingT::string_t nativeAccessSpecifier;
	long long nativeIsStruct;
	long long nativeIsInterface;
	long long nativeIsAbstract;
	long long nativeIsTemplate;
	long long nativeLinesCount;
	long long nativeLineNumber;
	long long nativeStartBlock;
	long long nativeLengthBlock;
	if (check_string<EncodingT>(name, nativeName) &&
		check_string<EncodingT>(fullName, nativeFullName) &&
		check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier) &&
		check_numeric_i(isStruct, nativeIsStruct) &&
		check_numeric_i(isInterface, nativeIsInterface) &&
		check_numeric_i(isAbstract, nativeIsAbstract) &&
		check_numeric_i(isTemplate, nativeIsTemplate) &&
		check_numeric_i(linesCount, nativeLinesCount) &&
		check_numeric_i(lineNumber, nativeLineNumber) &&
		check_numeric_i(startBlock, nativeStartBlock) &&
		check_numeric_i(lengthBlock, nativeLengthBlock))
	{
		m_value = boost::make_shared< _CppClass<EncodingT> >(nativeName,
				nativeFullName,
				nativeAccessSpecifier,
				nativeIsStruct,
				nativeIsInterface,
				nativeIsAbstract,
				nativeIsTemplate,
				nativeLinesCount,
				nativeLineNumber,
				nativeStartBlock,
				nativeLengthBlock);
	}
}

template <class EncodingT>
boost::shared_ptr< _CppClass<EncodingT> > CppClassInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void CppClassInterpreter<EncodingT>::value(boost::shared_ptr< _CppClass<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getFullName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getFullName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getAccessSpecifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getAccessSpecifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getIsStruct() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsStruct()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getIsInterface() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsInterface()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getIsAbstract() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsAbstract()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getIsTemplate() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsTemplate()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getLinesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLinesCount()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getStartBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getStartBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getLengthBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLengthBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getEncapsulationClass()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppClassInterpreter<EncodingT>(m_value->getEncapsulationClass()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getCppFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(m_value->getCppFile()) );
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setEncapsulationClass(boost::shared_ptr< Base<EncodingT> > const& encapsulationClass)
{
	boost::shared_ptr< _CppClass<EncodingT> > nativeEncapsulationClass;
	if (check_cppClass(encapsulationClass, nativeEncapsulationClass))
	{
		m_value->setEncapsulationClass(nativeEncapsulationClass);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		m_value->setName(nativeName);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setFullName(boost::shared_ptr< Base<EncodingT> > const& fullName)
{
	typename EncodingT::string_t nativeFullName;
	if (check_string<EncodingT>(fullName, nativeFullName))
	{
		m_value->setFullName(nativeFullName);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setAccessSpecifier(boost::shared_ptr< Base<EncodingT> > const& accessSpecifier)
{
	typename EncodingT::string_t nativeAccessSpecifier;
	if (check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier))
	{
		m_value->setAccessSpecifier(nativeAccessSpecifier);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setIsStruct(boost::shared_ptr< Base<EncodingT> > const& isStruct)
{
	long long nativeIsStruct;
	if (check_numeric_i(isStruct, nativeIsStruct))
	{
		m_value->setIsStruct(nativeIsStruct);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setIsInterface(boost::shared_ptr< Base<EncodingT> > const& isInterface)
{
	long long nativeIsInterface;
	if (check_numeric_i(isInterface, nativeIsInterface))
	{
		m_value->setIsInterface(nativeIsInterface);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setIsAbstract(boost::shared_ptr< Base<EncodingT> > const& isAbstract)
{
	long long nativeIsAbstract;
	if (check_numeric_i(isAbstract, nativeIsAbstract))
	{
		m_value->setIsAbstract(nativeIsAbstract);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setIsTemplate(boost::shared_ptr< Base<EncodingT> > const& isTemplate)
{
	long long nativeIsTemplate;
	if (check_numeric_i(isTemplate, nativeIsTemplate))
	{
		m_value->setIsTemplate(nativeIsTemplate);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setLinesCount(boost::shared_ptr< Base<EncodingT> > const& linesCount)
{
	long long nativeLinesCount;
	if (check_numeric_i(linesCount, nativeLinesCount))
	{
		m_value->setLinesCount(nativeLinesCount);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setCppFile(boost::shared_ptr< Base<EncodingT> > const& cppFile)
{
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
	if (check_cppFile(cppFile, nativeCppFile))
	{
		m_value->setCppFile(nativeCppFile);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	long long nativeLineNumber;
	if (check_numeric_i(lineNumber, nativeLineNumber))
	{
		m_value->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock)
{
	long long nativeStartBlock;
	if (check_numeric_i(startBlock, nativeStartBlock))
	{
		m_value->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	long long nativeLengthBlock;
	if (check_numeric_i(lengthBlock, nativeLengthBlock))
	{
		m_value->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::hasEncapsulationClass() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullEncapsulationClass()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::hasCppFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppFile()) );
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::removeEncapsulationClass()
{
	m_value->eraseEncapsulationClass();
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::removeCppFile()
{
	m_value->eraseCppFile();
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::removeCppInheritance(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppInheritance(m_value->getCppInheritancesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::removeCppFunction(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppFunction(m_value->getCppFunctionsBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::removeInternClasse(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseInternClasse(m_value->getInternClassesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::removeCppAttribute(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppAttribute(m_value->getCppAttributesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::removeCppEnum(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseCppEnum(m_value->getCppEnumsBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::insertCppInheritance(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppInheritance)
{
	size_t nativePosition;
	boost::shared_ptr< _CppInheritance<EncodingT> > nativeCppInheritance;
	if (check_numeric_i(n, nativePosition) &&
		check_cppInheritance(cppInheritance, nativeCppInheritance))
	{
		m_value->insertCppInheritance(m_value->getCppInheritancesBeginning()+nativePosition, nativeCppInheritance);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::insertCppFunction(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppFunction)
{
	size_t nativePosition;
	boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
	if (check_numeric_i(n, nativePosition) &&
		check_cppFunction(cppFunction, nativeCppFunction))
	{
		m_value->insertCppFunction(m_value->getCppFunctionsBeginning()+nativePosition, nativeCppFunction);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::insertInternClasse(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& internClasse)
{
	size_t nativePosition;
	boost::shared_ptr< _CppClass<EncodingT> > nativeInternClasse;
	if (check_numeric_i(n, nativePosition) &&
		check_cppClass(internClasse, nativeInternClasse))
	{
		m_value->insertInternClasse(m_value->getInternClassesBeginning()+nativePosition, nativeInternClasse);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::insertCppAttribute(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppAttribute)
{
	size_t nativePosition;
	boost::shared_ptr< _CppAttribute<EncodingT> > nativeCppAttribute;
	if (check_numeric_i(n, nativePosition) &&
		check_cppAttribute(cppAttribute, nativeCppAttribute))
	{
		m_value->insertCppAttribute(m_value->getCppAttributesBeginning()+nativePosition, nativeCppAttribute);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::insertCppEnum(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppEnum)
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
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getCppInheritance(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< CppInheritanceInterpreter<EncodingT> > res(new CppInheritanceInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res->value(m_value->getCppInheritanceAt(nativePosition));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getCppFunction(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< CppFunctionInterpreter<EncodingT> > res(new CppFunctionInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res->value(m_value->getCppFunctionAt(nativePosition));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getInternClasse(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< CppClassInterpreter<EncodingT> > res(new CppClassInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res->value(m_value->getInternClasseAt(nativePosition));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getCppAttribute(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< CppAttributeInterpreter<EncodingT> > res(new CppAttributeInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res->value(m_value->getCppAttributeAt(nativePosition));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getCppEnum(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< CppEnumInterpreter<EncodingT> > res(new CppEnumInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res->value(m_value->getCppEnumAt(nativePosition));
	}
	return res;
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::clearCppInheritances()
{
	m_value->clearCppInheritances();
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::clearCppFunctions()
{
	m_value->clearCppFunctions();
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::clearInternClasses()
{
	m_value->clearInternClasses();
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::clearCppAttributes()
{
	m_value->clearCppAttributes();
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::clearCppEnums()
{
	m_value->clearCppEnums();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::hasCppInheritances() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppInheritancesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::hasCppFunctions() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppFunctionsEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::hasInternClasses() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isInternClassesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::hasCppAttributes() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppAttributesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::hasCppEnums() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isCppEnumsEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::cppInheritancesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppInheritancesSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::cppFunctionsCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppFunctionsSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::internClassesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getInternClassesSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::cppAttributesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppAttributesSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::cppEnumsCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getCppEnumsSize()));
}

template <class EncodingT>
typename EncodingT::string_t CppClassInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppClassInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t CppClassInterpreter<EncodingT>::getClassName() const
{
	return UCS("CppClass");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("CppClass"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppClass, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppClass(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppClass<EncodingT> >& o)
{
	boost::shared_ptr< CppClassInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppClassInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppClass expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cppClass(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppClass<EncodingT> > const& o)
{
	boost::shared_ptr< CppClassInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppClassInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppClass expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

