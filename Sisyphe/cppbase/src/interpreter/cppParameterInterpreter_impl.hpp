#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppParameterInterpreter<EncodingT>::CppParameterInterpreter()
{
	setValue( boost::shared_ptr< _CppParameter<EncodingT> > (new _CppParameter<EncodingT>()) );
}

template <class EncodingT>
CppParameterInterpreter<EncodingT>::CppParameterInterpreter(boost::shared_ptr< _CppParameter<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CppParameterInterpreter<EncodingT>::CppParameterInterpreter(boost::shared_ptr< Base<EncodingT> > const& paramOrder,
				boost::shared_ptr< Base<EncodingT> > const& paramType,
				boost::shared_ptr< Base<EncodingT> > const& defaultValue,
				boost::shared_ptr< Base<EncodingT> > const& decName,
				boost::shared_ptr< Base<EncodingT> > const& startDecBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthDecBlock,
				boost::shared_ptr< Base<EncodingT> > const& defName,
				boost::shared_ptr< Base<EncodingT> > const& startDefBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthDefBlock)
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
		setValue(boost::shared_ptr< _CppParameter<EncodingT> >(new _CppParameter<EncodingT>(nativeParamOrder,
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
boost::shared_ptr< _CppParameter<EncodingT> > CppParameterInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setValue(boost::shared_ptr< _CppParameter<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getParamOrder() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getParamOrder()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getParamType() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getParamType()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getDefaultValue() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getDefaultValue()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getDecName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getDecName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getStartDecBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartDecBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getLengthDecBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthDecBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getDefName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getDefName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getStartDefBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartDefBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getLengthDefBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthDefBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::getCppFunction()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFunctionInterpreter<EncodingT>(getValue()->getCppFunction()) );
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setParamOrder(boost::shared_ptr< Base<EncodingT> > const& paramOrder)
{
	int nativeParamOrder;
	if (check_numeric(paramOrder, nativeParamOrder))
	{
		getValue()->setParamOrder(nativeParamOrder);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setParamType(boost::shared_ptr< Base<EncodingT> > const& paramType)
{
	typename EncodingT::string_t nativeParamType;
	if (check_string<EncodingT>(paramType, nativeParamType))
	{
		getValue()->setParamType(nativeParamType);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setDefaultValue(boost::shared_ptr< Base<EncodingT> > const& defaultValue)
{
	typename EncodingT::string_t nativeDefaultValue;
	if (check_string<EncodingT>(defaultValue, nativeDefaultValue))
	{
		getValue()->setDefaultValue(nativeDefaultValue);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setCppFunction(boost::shared_ptr< Base<EncodingT> > const& cppFunction)
{
	boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
	if (check_cppFunction(cppFunction, nativeCppFunction))
	{
		getValue()->setCppFunction(nativeCppFunction);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setDecName(boost::shared_ptr< Base<EncodingT> > const& decName)
{
	typename EncodingT::string_t nativeDecName;
	if (check_string<EncodingT>(decName, nativeDecName))
	{
		getValue()->setDecName(nativeDecName);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setStartDecBlock(boost::shared_ptr< Base<EncodingT> > const& startDecBlock)
{
	int nativeStartDecBlock;
	if (check_numeric(startDecBlock, nativeStartDecBlock))
	{
		getValue()->setStartDecBlock(nativeStartDecBlock);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setLengthDecBlock(boost::shared_ptr< Base<EncodingT> > const& lengthDecBlock)
{
	int nativeLengthDecBlock;
	if (check_numeric(lengthDecBlock, nativeLengthDecBlock))
	{
		getValue()->setLengthDecBlock(nativeLengthDecBlock);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setDefName(boost::shared_ptr< Base<EncodingT> > const& defName)
{
	typename EncodingT::string_t nativeDefName;
	if (check_string<EncodingT>(defName, nativeDefName))
	{
		getValue()->setDefName(nativeDefName);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setStartDefBlock(boost::shared_ptr< Base<EncodingT> > const& startDefBlock)
{
	int nativeStartDefBlock;
	if (check_numeric(startDefBlock, nativeStartDefBlock))
	{
		getValue()->setStartDefBlock(nativeStartDefBlock);
	}
}


template <class EncodingT>
void CppParameterInterpreter<EncodingT>::setLengthDefBlock(boost::shared_ptr< Base<EncodingT> > const& lengthDefBlock)
{
	int nativeLengthDefBlock;
	if (check_numeric(lengthDefBlock, nativeLengthDefBlock))
	{
		getValue()->setLengthDefBlock(nativeLengthDefBlock);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::hasCppFunction() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppFunction()) );
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
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppParameterInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CppParameterInterpreter<EncodingT>::getClassName() const
{
	return C("CppParameter");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppParameterInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

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
bool check_cppParameter(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppParameter<EncodingT> >& o)
{
	boost::shared_ptr< CppParameterInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppParameterInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppParameter expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cppParameter(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppParameter<EncodingT> > const& o)
{
	boost::shared_ptr< CppParameterInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppParameterInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppParameter expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

