#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppAttributeInterpreter<EncodingT>::CppAttributeInterpreter()
{
	setValue( boost::shared_ptr< _CppAttribute<EncodingT> > (new _CppAttribute<EncodingT>()) );
}

template <class EncodingT>
CppAttributeInterpreter<EncodingT>::CppAttributeInterpreter(boost::shared_ptr< _CppAttribute<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CppAttributeInterpreter<EncodingT>::CppAttributeInterpreter(boost::shared_ptr< Base<EncodingT> > const& attrType,
				boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& accessSpecifier,
				boost::shared_ptr< Base<EncodingT> > const& isStatic,
				boost::shared_ptr< Base<EncodingT> > const& isConst,
				boost::shared_ptr< Base<EncodingT> > const& constValue,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
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
		setValue(boost::shared_ptr< _CppAttribute<EncodingT> >(new _CppAttribute<EncodingT>(nativeAttrType,
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
boost::shared_ptr< _CppAttribute<EncodingT> > CppAttributeInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setValue(boost::shared_ptr< _CppAttribute<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getAttrType() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getAttrType()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getAccessSpecifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getAccessSpecifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getIsStatic() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsStatic()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getIsConst() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIsConst()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getConstValue() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getConstValue()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getStartBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getLengthBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getCppClass()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppClassInterpreter<EncodingT>(getValue()->getCppClass()) );
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setAttrType(boost::shared_ptr< Base<EncodingT> > const& attrType)
{
	typename EncodingT::string_t nativeAttrType;
	if (check_string<EncodingT>(attrType, nativeAttrType))
	{
		getValue()->setAttrType(nativeAttrType);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		getValue()->setName(nativeName);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setAccessSpecifier(boost::shared_ptr< Base<EncodingT> > const& accessSpecifier)
{
	typename EncodingT::string_t nativeAccessSpecifier;
	if (check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier))
	{
		getValue()->setAccessSpecifier(nativeAccessSpecifier);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setIsStatic(boost::shared_ptr< Base<EncodingT> > const& isStatic)
{
	int nativeIsStatic;
	if (check_numeric(isStatic, nativeIsStatic))
	{
		getValue()->setIsStatic(nativeIsStatic);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst)
{
	int nativeIsConst;
	if (check_numeric(isConst, nativeIsConst))
	{
		getValue()->setIsConst(nativeIsConst);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setConstValue(boost::shared_ptr< Base<EncodingT> > const& constValue)
{
	typename EncodingT::string_t nativeConstValue;
	if (check_string<EncodingT>(constValue, nativeConstValue))
	{
		getValue()->setConstValue(nativeConstValue);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setCppClass(boost::shared_ptr< Base<EncodingT> > const& cppClass)
{
	boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
	if (check_cppClass(cppClass, nativeCppClass))
	{
		getValue()->setCppClass(nativeCppClass);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	int nativeLineNumber;
	if (check_numeric(lineNumber, nativeLineNumber))
	{
		getValue()->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock)
{
	int nativeStartBlock;
	if (check_numeric(startBlock, nativeStartBlock))
	{
		getValue()->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	int nativeLengthBlock;
	if (check_numeric(lengthBlock, nativeLengthBlock))
	{
		getValue()->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::hasCppClass() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppClass()) );
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
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppAttributeInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CppAttributeInterpreter<EncodingT>::getClassName() const
{
	return C("CppAttribute");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

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
bool check_cppAttribute(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppAttribute<EncodingT> >& o)
{
	boost::shared_ptr< CppAttributeInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppAttributeInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppAttribute expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cppAttribute(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppAttribute<EncodingT> > const& o)
{
	boost::shared_ptr< CppAttributeInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppAttributeInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppAttribute expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

