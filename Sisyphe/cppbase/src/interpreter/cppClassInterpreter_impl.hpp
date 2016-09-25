#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppClassInterpreter<EncodingT>::CppClassInterpreter()
{
	setValue( boost::shared_ptr< _CppClass<EncodingT> > (new _CppClass<EncodingT>()) );
}

template <class EncodingT>
CppClassInterpreter<EncodingT>::CppClassInterpreter(boost::shared_ptr< _CppClass<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CppClassInterpreter<EncodingT>::CppClassInterpreter(boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& isStruct,
				boost::shared_ptr< Base<EncodingT> > const& isInterface,
				boost::shared_ptr< Base<EncodingT> > const& isAbstract,
				boost::shared_ptr< Base<EncodingT> > const& linesCount,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	typename EncodingT::string_t nativeName;
	int nativeIsStruct;
	int nativeIsInterface;
	int nativeIsAbstract;
	int nativeLinesCount;
	int nativeLineNumber;
	int nativeStartBlock;
	int nativeLengthBlock;
	if (check_string<EncodingT>(name, nativeName) &&
		check_numeric(isStruct, nativeIsStruct) &&
		check_numeric(isInterface, nativeIsInterface) &&
		check_numeric(isAbstract, nativeIsAbstract) &&
		check_numeric(linesCount, nativeLinesCount) &&
		check_numeric(lineNumber, nativeLineNumber) &&
		check_numeric(startBlock, nativeStartBlock) &&
		check_numeric(lengthBlock, nativeLengthBlock))
	{
		setValue(boost::shared_ptr< _CppClass<EncodingT> >(new _CppClass<EncodingT>(nativeName,
				nativeIsStruct,
				nativeIsInterface,
				nativeIsAbstract,
				nativeLinesCount,
				nativeLineNumber,
				nativeStartBlock,
				nativeLengthBlock)));
	}
}

template <class EncodingT>
CppClassInterpreter<EncodingT>::~CppClassInterpreter()
{}

template <class EncodingT>
boost::shared_ptr< _CppClass<EncodingT> > CppClassInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppClassInterpreter<EncodingT>::setValue(boost::shared_ptr< _CppClass<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getIsStruct() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsStruct()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getIsInterface() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsInterface()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getIsAbstract() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsAbstract()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getLinesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLinesCount()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getStartBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getLengthBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getCppFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(getValue()->getCppFile()) );
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		getValue()->setName(nativeName);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setIsStruct(boost::shared_ptr< Base<EncodingT> > const& isStruct)
{
	int nativeIsStruct;
	if (check_numeric(isStruct, nativeIsStruct))
	{
		getValue()->setIsStruct(nativeIsStruct);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setIsInterface(boost::shared_ptr< Base<EncodingT> > const& isInterface)
{
	int nativeIsInterface;
	if (check_numeric(isInterface, nativeIsInterface))
	{
		getValue()->setIsInterface(nativeIsInterface);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setIsAbstract(boost::shared_ptr< Base<EncodingT> > const& isAbstract)
{
	int nativeIsAbstract;
	if (check_numeric(isAbstract, nativeIsAbstract))
	{
		getValue()->setIsAbstract(nativeIsAbstract);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setLinesCount(boost::shared_ptr< Base<EncodingT> > const& linesCount)
{
	int nativeLinesCount;
	if (check_numeric(linesCount, nativeLinesCount))
	{
		getValue()->setLinesCount(nativeLinesCount);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setCppFile(boost::shared_ptr< Base<EncodingT> > const& cppFile)
{
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
	if (check_cppFile(cppFile, nativeCppFile))
	{
		getValue()->setCppFile(nativeCppFile);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	int nativeLineNumber;
	if (check_numeric(lineNumber, nativeLineNumber))
	{
		getValue()->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock)
{
	int nativeStartBlock;
	if (check_numeric(startBlock, nativeStartBlock))
	{
		getValue()->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	int nativeLengthBlock;
	if (check_numeric(lengthBlock, nativeLengthBlock))
	{
		getValue()->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::hasCppFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppFile()) );
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::removeCppFile()
{
	getValue()->eraseCppFile();
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::removeCppInheritance(boost::shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppInheritance(getValue()->getCppInheritancesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::removeCppFunction(boost::shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppFunction(getValue()->getCppFunctionsBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::removeCppAttribute(boost::shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppAttribute(getValue()->getCppAttributesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::insertCppInheritance(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppInheritance)
{
	int nativePosition;
	boost::shared_ptr< _CppInheritance<EncodingT> > nativeCppInheritance;
	if (check_numeric(n, nativePosition) &&
		check_cppInheritance(cppInheritance, nativeCppInheritance))
	{
		getValue()->insertCppInheritance(getValue()->getCppInheritancesBeginning()+nativePosition, nativeCppInheritance);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::insertCppFunction(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppFunction)
{
	int nativePosition;
	boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
	if (check_numeric(n, nativePosition) &&
		check_cppFunction(cppFunction, nativeCppFunction))
	{
		getValue()->insertCppFunction(getValue()->getCppFunctionsBeginning()+nativePosition, nativeCppFunction);
	}
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::insertCppAttribute(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppAttribute)
{
	int nativePosition;
	boost::shared_ptr< _CppAttribute<EncodingT> > nativeCppAttribute;
	if (check_numeric(n, nativePosition) &&
		check_cppAttribute(cppAttribute, nativeCppAttribute))
	{
		getValue()->insertCppAttribute(getValue()->getCppAttributesBeginning()+nativePosition, nativeCppAttribute);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getCppInheritance(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppInheritanceInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppInheritanceInterpreter<EncodingT>(getValue()->getCppInheritanceAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getCppFunction(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppFunctionInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppFunctionInterpreter<EncodingT>(getValue()->getCppFunctionAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::getCppAttribute(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new CppAttributeInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppAttributeInterpreter<EncodingT>(getValue()->getCppAttributeAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::clearCppInheritances()
{
	getValue()->clearCppInheritances();
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::clearCppFunctions()
{
	getValue()->clearCppFunctions();
}


template <class EncodingT>
void CppClassInterpreter<EncodingT>::clearCppAttributes()
{
	getValue()->clearCppAttributes();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::hasCppInheritances() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppInheritancesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::hasCppFunctions() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppFunctionsEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::hasCppAttributes() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppAttributesEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::cppInheritancesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppInheritancesSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::cppFunctionsCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppFunctionsSize()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::cppAttributesCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppAttributesSize()));
}

template <class EncodingT>
typename EncodingT::string_t CppClassInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppClassInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CppClassInterpreter<EncodingT>::getClassName() const
{
	return C("CppClass");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppClassInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppClass"), method, args, ret) ||
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
		o = value->getValue();
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
		value->setValue(o);
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

