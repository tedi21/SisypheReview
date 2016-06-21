#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppEnumInterpreter<EncodingT>::CppEnumInterpreter()
{
	setValue( shared_ptr< _CppEnum<EncodingT> > (new _CppEnum<EncodingT>()) );
}

template <class EncodingT>
CppEnumInterpreter<EncodingT>::CppEnumInterpreter(shared_ptr< _CppEnum<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CppEnumInterpreter<EncodingT>::CppEnumInterpreter(shared_ptr< Base<EncodingT> > const& name,
				shared_ptr< Base<EncodingT> > const& lineNumber,
				shared_ptr< Base<EncodingT> > const& startBlock,
				shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	typename EncodingT::string_t nativeName;
	int nativeLineNumber;
	int nativeStartBlock;
	int nativeLengthBlock;
	if (check_string<EncodingT>(name, nativeName) &&
		check_numeric(lineNumber, nativeLineNumber) &&
		check_numeric(startBlock, nativeStartBlock) &&
		check_numeric(lengthBlock, nativeLengthBlock))
	{
		setValue(shared_ptr< _CppEnum<EncodingT> >(new _CppEnum<EncodingT>(nativeName,
				nativeLineNumber,
				nativeStartBlock,
				nativeLengthBlock)));
	}
}

template <class EncodingT>
CppEnumInterpreter<EncodingT>::~CppEnumInterpreter()
{}

template <class EncodingT>
shared_ptr< _CppEnum<EncodingT> > CppEnumInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppEnumInterpreter<EncodingT>::setValue(shared_ptr< _CppEnum<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getIdentifier() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getName() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getName()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getLineNumber() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLineNumber()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getStartBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getLengthBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getCppFile()
{
	return shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(getValue()->getCppFile()) );
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::setName(shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		getValue()->setName(nativeName);
	}
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::setCppFile(shared_ptr< Base<EncodingT> > const& cppFile)
{
	shared_ptr< _CppFile<EncodingT> > nativeCppFile;
	if (check_cppFile(cppFile, nativeCppFile))
	{
		getValue()->setCppFile(nativeCppFile);
	}
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::setLineNumber(shared_ptr< Base<EncodingT> > const& lineNumber)
{
	int nativeLineNumber;
	if (check_numeric(lineNumber, nativeLineNumber))
	{
		getValue()->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::setStartBlock(shared_ptr< Base<EncodingT> > const& startBlock)
{
	int nativeStartBlock;
	if (check_numeric(startBlock, nativeStartBlock))
	{
		getValue()->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::setLengthBlock(shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	int nativeLengthBlock;
	if (check_numeric(lengthBlock, nativeLengthBlock))
	{
		getValue()->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::hasCppFile() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppFile()) );
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::removeCppFile()
{
	getValue()->eraseCppFile();
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::removeCppEnumConstant(shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseCppEnumConstant(getValue()->getCppEnumConstantsBeginning()+nativePosition);
	}
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::insertCppEnumConstant(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& cppEnumConstant)
{
	int nativePosition;
	shared_ptr< _CppEnumConstant<EncodingT> > nativeCppEnumConstant;
	if (check_numeric(n, nativePosition) &&
		check_cppEnumConstant(cppEnumConstant, nativeCppEnumConstant))
	{
		getValue()->insertCppEnumConstant(getValue()->getCppEnumConstantsBeginning()+nativePosition, nativeCppEnumConstant);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::getCppEnumConstant(shared_ptr< Base<EncodingT> > const& n)
{
	shared_ptr< Base<EncodingT> > res(new CppEnumConstantInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new CppEnumConstantInterpreter<EncodingT>(getValue()->getCppEnumConstantAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void CppEnumInterpreter<EncodingT>::clearCppEnumConstants()
{
	getValue()->clearCppEnumConstants();
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::hasCppEnumConstants() const
{
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isCppEnumConstantsEmpty()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::cppEnumConstantsCount() const
{
	return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getCppEnumConstantsSize()));
}

template <class EncodingT>
typename EncodingT::string_t CppEnumInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new CppEnumInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CppEnumInterpreter<EncodingT>::getClassName() const
{
	return C("CppEnum");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppEnum"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppEnum, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppEnum(shared_ptr< Base<EncodingT> > const& val, shared_ptr< _CppEnum<EncodingT> >& o)
{
	shared_ptr< CppEnumInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppEnumInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppEnum expected, got " << A(val->getClassName());
	}
	return value;
}

template <class EncodingT>
bool reset_cppEnum(shared_ptr< Base<EncodingT> >& val, shared_ptr< _CppEnum<EncodingT> > const& o)
{
	shared_ptr< CppEnumInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppEnumInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppEnum expected, got " << A(val->getClassName());
	}
	return value;
}

NAMESPACE_END

#undef C
#undef A

