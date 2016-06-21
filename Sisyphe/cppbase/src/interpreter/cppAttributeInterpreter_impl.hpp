#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppAttributeInterpreter<EncodingT>::CppAttributeInterpreter()
{
	setValue( shared_ptr< _CppAttribute<EncodingT> > (new _CppAttribute<EncodingT>()) );
}

template <class EncodingT>
CppAttributeInterpreter<EncodingT>::CppAttributeInterpreter(shared_ptr< _CppAttribute<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CppAttributeInterpreter<EncodingT>::CppAttributeInterpreter(shared_ptr< Base<EncodingT> > const& attrType,
				shared_ptr< Base<EncodingT> > const& name,
				shared_ptr< Base<EncodingT> > const& accessSpecifier,
				shared_ptr< Base<EncodingT> > const& isStatic,
				shared_ptr< Base<EncodingT> > const& isConst,
				shared_ptr< Base<EncodingT> > const& constValue,
				shared_ptr< Base<EncodingT> > const& lineNumber,
				shared_ptr< Base<EncodingT> > const& startBlock,
				shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	typename EncodingT::string_t nativeAttrType;
	typename EncodingT::string_t nativeName;
	typename EncodingT::string_t nativeAccessSpecifier;
	int nativeIsStatic;
	int nativeIsConst;
	typename EncodingT::string_t nativeConstValue;
	int nativeLineNumber;
	int nativeStartBlock;
	int nativeLengthBlock;
	if (check_string<EncodingT>(attrType, nativeAttrType) &&
		check_string<EncodingT>(name, nativeName) &&
		check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier) &&
		check_numeric(isStatic, nativeIsStatic) &&
		check_numeric(isConst, nativeIsConst) &&
		check_string<EncodingT>(constValue, nativeConstValue) &&
		check_numeric(lineNumber, nativeLineNumber) &&
		check_numeric(startBlock, nativeStartBlock) &&
		check_numeric(lengthBlock, nativeLengthBlock))
	{
		setValue(shared_ptr< _CppAttribute<EncodingT> >(new _CppAttribute<EncodingT>(nativeAttrType,
				nativeName,
				nativeAccessSpecifier,
				nativeIsStatic,
				nativeIsConst,
				nativeConstValue,
				nativeLineNumber,
				nativeStartBlock,
				nativeLengthBlock)));
	}
}

template <class EncodingT>
CppAttributeInterpreter<EncodingT>::~CppAttributeInterpreter()
{}

template <class EncodingT>
shared_ptr< _CppAttribute<EncodingT> > CppAttributeInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setValue(shared_ptr< _CppAttribute<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getIdentifier() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getAttrType() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getAttrType()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getName() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getName()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getAccessSpecifier() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getAccessSpecifier()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getIsStatic() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsStatic()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getIsConst() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsConst()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getConstValue() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getConstValue()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getLineNumber() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLineNumber()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getStartBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getLengthBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getCppClass()
{
	return shared_ptr< Base<EncodingT> >( new CppClassInterpreter<EncodingT>(getValue()->getCppClass()) );
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setAttrType(shared_ptr< Base<EncodingT> > const& attrType)
{
	typename EncodingT::string_t nativeAttrType;
	if (check_string<EncodingT>(attrType, nativeAttrType))
	{
		getValue()->setAttrType(nativeAttrType);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setName(shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		getValue()->setName(nativeName);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setAccessSpecifier(shared_ptr< Base<EncodingT> > const& accessSpecifier)
{
	typename EncodingT::string_t nativeAccessSpecifier;
	if (check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier))
	{
		getValue()->setAccessSpecifier(nativeAccessSpecifier);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setIsStatic(shared_ptr< Base<EncodingT> > const& isStatic)
{
	int nativeIsStatic;
	if (check_numeric(isStatic, nativeIsStatic))
	{
		getValue()->setIsStatic(nativeIsStatic);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setIsConst(shared_ptr< Base<EncodingT> > const& isConst)
{
	int nativeIsConst;
	if (check_numeric(isConst, nativeIsConst))
	{
		getValue()->setIsConst(nativeIsConst);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setConstValue(shared_ptr< Base<EncodingT> > const& constValue)
{
	typename EncodingT::string_t nativeConstValue;
	if (check_string<EncodingT>(constValue, nativeConstValue))
	{
		getValue()->setConstValue(nativeConstValue);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setCppClass(shared_ptr< Base<EncodingT> > const& cppClass)
{
	shared_ptr< _CppClass<EncodingT> > nativeCppClass;
	if (check_cppClass(cppClass, nativeCppClass))
	{
		getValue()->setCppClass(nativeCppClass);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setLineNumber(shared_ptr< Base<EncodingT> > const& lineNumber)
{
	int nativeLineNumber;
	if (check_numeric(lineNumber, nativeLineNumber))
	{
		getValue()->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setStartBlock(shared_ptr< Base<EncodingT> > const& startBlock)
{
	int nativeStartBlock;
	if (check_numeric(startBlock, nativeStartBlock))
	{
		getValue()->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setLengthBlock(shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	int nativeLengthBlock;
	if (check_numeric(lengthBlock, nativeLengthBlock))
	{
		getValue()->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::hasCppClass() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppClass()) );
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::removeCppClass()
{
	getValue()->eraseCppClass();
}

template <class EncodingT>
typename EncodingT::string_t CppAttributeInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new CppAttributeInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CppAttributeInterpreter<EncodingT>::getClassName() const
{
	return C("CppAttribute");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppAttribute"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppAttribute, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppAttribute(shared_ptr< Base<EncodingT> > const& val, shared_ptr< _CppAttribute<EncodingT> >& o)
{
	shared_ptr< CppAttributeInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppAttributeInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppAttribute expected, got " << A(val->getClassName());
	}
	return value;
}

template <class EncodingT>
bool reset_cppAttribute(shared_ptr< Base<EncodingT> >& val, shared_ptr< _CppAttribute<EncodingT> > const& o)
{
	shared_ptr< CppAttributeInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppAttributeInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppAttribute expected, got " << A(val->getClassName());
	}
	return value;
}

NAMESPACE_END

#undef C
#undef A

