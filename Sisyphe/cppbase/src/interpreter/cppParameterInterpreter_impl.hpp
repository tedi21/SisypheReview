#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppParameterInterpreter<EncodingT>::CppParameterInterpreter()
{
	setValue( shared_ptr< _CppParameter<EncodingT> > (new _CppParameter<EncodingT>()) );
}

template <class EncodingT>
CppParameterInterpreter<EncodingT>::CppParameterInterpreter(shared_ptr< _CppParameter<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CppParameterInterpreter<EncodingT>::CppParameterInterpreter(shared_ptr< Base<EncodingT> > const& paramOrder,
				shared_ptr< Base<EncodingT> > const& paramType,
				shared_ptr< Base<EncodingT> > const& defaultValue,
				shared_ptr< Base<EncodingT> > const& decName,
				shared_ptr< Base<EncodingT> > const& startDecBlock,
				shared_ptr< Base<EncodingT> > const& lengthDecBlock,
				shared_ptr< Base<EncodingT> > const& defName,
				shared_ptr< Base<EncodingT> > const& startDefBlock,
				shared_ptr< Base<EncodingT> > const& lengthDefBlock)
{
	int nativeParamOrder;
	typename EncodingT::string_t nativeParamType;
	typename EncodingT::string_t nativeDefaultValue;
	typename EncodingT::string_t nativeDecName;
	int nativeStartDecBlock;
	int nativeLengthDecBlock;
	typename EncodingT::string_t nativeDefName;
	int nativeStartDefBlock;
	int nativeLengthDefBlock;
	if (check_numeric(paramOrder, nativeParamOrder) &&
		check_string<EncodingT>(paramType, nativeParamType) &&
		check_string<EncodingT>(defaultValue, nativeDefaultValue) &&
		check_string<EncodingT>(decName, nativeDecName) &&
		check_numeric(startDecBlock, nativeStartDecBlock) &&
		check_numeric(lengthDecBlock, nativeLengthDecBlock) &&
		check_string<EncodingT>(defName, nativeDefName) &&
		check_numeric(startDefBlock, nativeStartDefBlock) &&
		check_numeric(lengthDefBlock, nativeLengthDefBlock))
	{
		setValue(shared_ptr< _CppParameter<EncodingT> >(new _CppParameter<EncodingT>(nativeParamOrder,
				nativeParamType,
				nativeDefaultValue,
				nativeDecName,
				nativeStartDecBlock,
				nativeLengthDecBlock,
				nativeDefName,
				nativeStartDefBlock,
				nativeLengthDefBlock)));
	}
}

template <class EncodingT>
CppParameterInterpreter<EncodingT>::~CppParameterInterpreter()
{}

template <class EncodingT>
shared_ptr< _CppParameter<EncodingT> > CppParameterInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setValue(shared_ptr< _CppParameter<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getIdentifier() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getParamOrder() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getParamOrder()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getParamType() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getParamType()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getDefaultValue() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getDefaultValue()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getDecName() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getDecName()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getStartDecBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartDecBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getLengthDecBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthDecBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getDefName() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getDefName()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getStartDefBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartDefBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getLengthDefBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthDefBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getCppFunction()
{
	return shared_ptr< Base<EncodingT> >( new CppFunctionInterpreter<EncodingT>(getValue()->getCppFunction()) );
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setParamOrder(shared_ptr< Base<EncodingT> > const& paramOrder)
{
	int nativeParamOrder;
	if (check_numeric(paramOrder, nativeParamOrder))
	{
		getValue()->setParamOrder(nativeParamOrder);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setParamType(shared_ptr< Base<EncodingT> > const& paramType)
{
	typename EncodingT::string_t nativeParamType;
	if (check_string<EncodingT>(paramType, nativeParamType))
	{
		getValue()->setParamType(nativeParamType);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setDefaultValue(shared_ptr< Base<EncodingT> > const& defaultValue)
{
	typename EncodingT::string_t nativeDefaultValue;
	if (check_string<EncodingT>(defaultValue, nativeDefaultValue))
	{
		getValue()->setDefaultValue(nativeDefaultValue);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setCppFunction(shared_ptr< Base<EncodingT> > const& cppFunction)
{
	shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
	if (check_cppFunction(cppFunction, nativeCppFunction))
	{
		getValue()->setCppFunction(nativeCppFunction);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setDecName(shared_ptr< Base<EncodingT> > const& decName)
{
	typename EncodingT::string_t nativeDecName;
	if (check_string<EncodingT>(decName, nativeDecName))
	{
		getValue()->setDecName(nativeDecName);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setStartDecBlock(shared_ptr< Base<EncodingT> > const& startDecBlock)
{
	int nativeStartDecBlock;
	if (check_numeric(startDecBlock, nativeStartDecBlock))
	{
		getValue()->setStartDecBlock(nativeStartDecBlock);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setLengthDecBlock(shared_ptr< Base<EncodingT> > const& lengthDecBlock)
{
	int nativeLengthDecBlock;
	if (check_numeric(lengthDecBlock, nativeLengthDecBlock))
	{
		getValue()->setLengthDecBlock(nativeLengthDecBlock);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setDefName(shared_ptr< Base<EncodingT> > const& defName)
{
	typename EncodingT::string_t nativeDefName;
	if (check_string<EncodingT>(defName, nativeDefName))
	{
		getValue()->setDefName(nativeDefName);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setStartDefBlock(shared_ptr< Base<EncodingT> > const& startDefBlock)
{
	int nativeStartDefBlock;
	if (check_numeric(startDefBlock, nativeStartDefBlock))
	{
		getValue()->setStartDefBlock(nativeStartDefBlock);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setLengthDefBlock(shared_ptr< Base<EncodingT> > const& lengthDefBlock)
{
	int nativeLengthDefBlock;
	if (check_numeric(lengthDefBlock, nativeLengthDefBlock))
	{
		getValue()->setLengthDefBlock(nativeLengthDefBlock);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::hasCppFunction() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppFunction()) );
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::removeCppFunction()
{
	getValue()->eraseCppFunction();
}

template <class EncodingT>
typename EncodingT::string_t CppParameterInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new CppParameterInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CppParameterInterpreter<EncodingT>::getClassName() const
{
	return C("CppParameter");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppParameter"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppParameter, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppParameter(shared_ptr< Base<EncodingT> > const& val, shared_ptr< _CppParameter<EncodingT> >& o)
{
	shared_ptr< CppParameterInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppParameterInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppParameter expected, got " << A(val->getClassName());
	}
	return value;
}

template <class EncodingT>
bool reset_cppParameter(shared_ptr< Base<EncodingT> >& val, shared_ptr< _CppParameter<EncodingT> > const& o)
{
	shared_ptr< CppParameterInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppParameterInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppParameter expected, got " << A(val->getClassName());
	}
	return value;
}

NAMESPACE_END

#undef C
#undef A

