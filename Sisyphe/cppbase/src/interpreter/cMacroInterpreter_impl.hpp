#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CMacroInterpreter<EncodingT>::CMacroInterpreter()
{
	setValue( shared_ptr< _CMacro<EncodingT> > (new _CMacro<EncodingT>()) );
}

template <class EncodingT>
CMacroInterpreter<EncodingT>::CMacroInterpreter(shared_ptr< _CMacro<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CMacroInterpreter<EncodingT>::CMacroInterpreter(shared_ptr< Base<EncodingT> > const& name,
				shared_ptr< Base<EncodingT> > const& isConst,
				shared_ptr< Base<EncodingT> > const& constValue,
				shared_ptr< Base<EncodingT> > const& lineNumber,
				shared_ptr< Base<EncodingT> > const& startBlock,
				shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	typename EncodingT::string_t nativeName;
	int nativeIsConst;
	typename EncodingT::string_t nativeConstValue;
	int nativeLineNumber;
	int nativeStartBlock;
	int nativeLengthBlock;
	if (check_string<EncodingT>(name, nativeName) &&
		check_numeric(isConst, nativeIsConst) &&
		check_string<EncodingT>(constValue, nativeConstValue) &&
		check_numeric(lineNumber, nativeLineNumber) &&
		check_numeric(startBlock, nativeStartBlock) &&
		check_numeric(lengthBlock, nativeLengthBlock))
	{
		setValue(shared_ptr< _CMacro<EncodingT> >(new _CMacro<EncodingT>(nativeName,
				nativeIsConst,
				nativeConstValue,
				nativeLineNumber,
				nativeStartBlock,
				nativeLengthBlock)));
	}
}

template <class EncodingT>
CMacroInterpreter<EncodingT>::~CMacroInterpreter()
{}

template <class EncodingT>
shared_ptr< _CMacro<EncodingT> > CMacroInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CMacroInterpreter<EncodingT>::setValue(shared_ptr< _CMacro<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getIdentifier() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getName() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getName()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getIsConst() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsConst()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getConstValue() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getConstValue()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getLineNumber() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLineNumber()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getStartBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getLengthBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::getCppFile()
{
	return shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(getValue()->getCppFile()) );
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setName(shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		getValue()->setName(nativeName);
	}
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setIsConst(shared_ptr< Base<EncodingT> > const& isConst)
{
	int nativeIsConst;
	if (check_numeric(isConst, nativeIsConst))
	{
		getValue()->setIsConst(nativeIsConst);
	}
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setConstValue(shared_ptr< Base<EncodingT> > const& constValue)
{
	typename EncodingT::string_t nativeConstValue;
	if (check_string<EncodingT>(constValue, nativeConstValue))
	{
		getValue()->setConstValue(nativeConstValue);
	}
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setCppFile(shared_ptr< Base<EncodingT> > const& cppFile)
{
	shared_ptr< _CppFile<EncodingT> > nativeCppFile;
	if (check_cppFile(cppFile, nativeCppFile))
	{
		getValue()->setCppFile(nativeCppFile);
	}
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setLineNumber(shared_ptr< Base<EncodingT> > const& lineNumber)
{
	int nativeLineNumber;
	if (check_numeric(lineNumber, nativeLineNumber))
	{
		getValue()->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setStartBlock(shared_ptr< Base<EncodingT> > const& startBlock)
{
	int nativeStartBlock;
	if (check_numeric(startBlock, nativeStartBlock))
	{
		getValue()->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::setLengthBlock(shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	int nativeLengthBlock;
	if (check_numeric(lengthBlock, nativeLengthBlock))
	{
		getValue()->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::hasCppFile() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppFile()) );
}


template <class EncodingT>
void CMacroInterpreter<EncodingT>::removeCppFile()
{
	getValue()->eraseCppFile();
}

template <class EncodingT>
typename EncodingT::string_t CMacroInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new CMacroInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CMacroInterpreter<EncodingT>::getClassName() const
{
	return C("CMacro");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CMacroInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CMacro"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CMacro, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cMacro(shared_ptr< Base<EncodingT> > const& val, shared_ptr< _CMacro<EncodingT> >& o)
{
	shared_ptr< CMacroInterpreter<EncodingT> > value  = dynamic_pointer_cast< CMacroInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CMacro expected, got " << A(val->getClassName());
	}
	return value;
}

template <class EncodingT>
bool reset_cMacro(shared_ptr< Base<EncodingT> >& val, shared_ptr< _CMacro<EncodingT> > const& o)
{
	shared_ptr< CMacroInterpreter<EncodingT> > value  = dynamic_pointer_cast< CMacroInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CMacro expected, got " << A(val->getClassName());
	}
	return value;
}

NAMESPACE_END

#undef C
#undef A

