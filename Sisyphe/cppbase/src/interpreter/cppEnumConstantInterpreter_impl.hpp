#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppEnumConstantInterpreter<EncodingT>::CppEnumConstantInterpreter()
{
	setValue( shared_ptr< _CppEnumConstant<EncodingT> > (new _CppEnumConstant<EncodingT>()) );
}

template <class EncodingT>
CppEnumConstantInterpreter<EncodingT>::CppEnumConstantInterpreter(shared_ptr< _CppEnumConstant<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CppEnumConstantInterpreter<EncodingT>::CppEnumConstantInterpreter(shared_ptr< Base<EncodingT> > const& name,
				shared_ptr< Base<EncodingT> > const& defaultValue,
				shared_ptr< Base<EncodingT> > const& startBlock,
				shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	typename EncodingT::string_t nativeName;
	int nativeDefaultValue;
	int nativeStartBlock;
	int nativeLengthBlock;
	if (check_string<EncodingT>(name, nativeName) &&
		check_numeric(defaultValue, nativeDefaultValue) &&
		check_numeric(startBlock, nativeStartBlock) &&
		check_numeric(lengthBlock, nativeLengthBlock))
	{
		setValue(shared_ptr< _CppEnumConstant<EncodingT> >(new _CppEnumConstant<EncodingT>(nativeName,
				nativeDefaultValue,
				nativeStartBlock,
				nativeLengthBlock)));
	}
}

template <class EncodingT>
CppEnumConstantInterpreter<EncodingT>::~CppEnumConstantInterpreter()
{}

template <class EncodingT>
shared_ptr< _CppEnumConstant<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::setValue(shared_ptr< _CppEnumConstant<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getIdentifier() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getName() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getName()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getDefaultValue() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getDefaultValue()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getStartBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getLengthBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::getCppEnum()
{
	return shared_ptr< Base<EncodingT> >( new CppEnumInterpreter<EncodingT>(getValue()->getCppEnum()) );
}


template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::setName(shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		getValue()->setName(nativeName);
	}
}


template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::setDefaultValue(shared_ptr< Base<EncodingT> > const& defaultValue)
{
	int nativeDefaultValue;
	if (check_numeric(defaultValue, nativeDefaultValue))
	{
		getValue()->setDefaultValue(nativeDefaultValue);
	}
}


template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::setCppEnum(shared_ptr< Base<EncodingT> > const& cppEnum)
{
	shared_ptr< _CppEnum<EncodingT> > nativeCppEnum;
	if (check_cppEnum(cppEnum, nativeCppEnum))
	{
		getValue()->setCppEnum(nativeCppEnum);
	}
}


template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::setStartBlock(shared_ptr< Base<EncodingT> > const& startBlock)
{
	int nativeStartBlock;
	if (check_numeric(startBlock, nativeStartBlock))
	{
		getValue()->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::setLengthBlock(shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	int nativeLengthBlock;
	if (check_numeric(lengthBlock, nativeLengthBlock))
	{
		getValue()->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::hasCppEnum() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppEnum()) );
}


template <class EncodingT>
void CppEnumConstantInterpreter<EncodingT>::removeCppEnum()
{
	getValue()->eraseCppEnum();
}

template <class EncodingT>
typename EncodingT::string_t CppEnumConstantInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new CppEnumConstantInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CppEnumConstantInterpreter<EncodingT>::getClassName() const
{
	return C("CppEnumConstant");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppEnumConstantInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppEnumConstant"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppEnumConstant, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppEnumConstant(shared_ptr< Base<EncodingT> > const& val, shared_ptr< _CppEnumConstant<EncodingT> >& o)
{
	shared_ptr< CppEnumConstantInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppEnumConstantInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppEnumConstant expected, got " << A(val->getClassName());
	}
	return value;
}

template <class EncodingT>
bool reset_cppEnumConstant(shared_ptr< Base<EncodingT> >& val, shared_ptr< _CppEnumConstant<EncodingT> > const& o)
{
	shared_ptr< CppEnumConstantInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppEnumConstantInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppEnumConstant expected, got " << A(val->getClassName());
	}
	return value;
}

NAMESPACE_END

#undef C
#undef A

