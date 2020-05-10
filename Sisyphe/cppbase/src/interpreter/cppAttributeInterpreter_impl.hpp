#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppAttributeInterpreter<EncodingT>::CppAttributeInterpreter()
{
	m_value = boost::make_shared< _CppAttribute<EncodingT> >();
}

template <class EncodingT>
CppAttributeInterpreter<EncodingT>::CppAttributeInterpreter(boost::shared_ptr< _CppAttribute<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
CppAttributeInterpreter<EncodingT>::CppAttributeInterpreter(boost::shared_ptr< Base<EncodingT> > const& attrType,
				boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& accessSpecifier,
				boost::shared_ptr< Base<EncodingT> > const& isStatic,
				boost::shared_ptr< Base<EncodingT> > const& isConst,
				boost::shared_ptr< Base<EncodingT> > const& isConstexpr,
				boost::shared_ptr< Base<EncodingT> > const& constValue,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	typename EncodingT::string_t nativeAttrType;
	typename EncodingT::string_t nativeName;
	typename EncodingT::string_t nativeAccessSpecifier;
	long long nativeIsStatic;
	long long nativeIsConst;
	long long nativeIsConstexpr;
	typename EncodingT::string_t nativeConstValue;
	long long nativeLineNumber;
	long long nativeStartBlock;
	long long nativeLengthBlock;
	if (check_string<EncodingT>(attrType, nativeAttrType) &&
		check_string<EncodingT>(name, nativeName) &&
		check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier) &&
		check_numeric_i(isStatic, nativeIsStatic) &&
		check_numeric_i(isConst, nativeIsConst) &&
		check_numeric_i(isConstexpr, nativeIsConstexpr) &&
		check_string<EncodingT>(constValue, nativeConstValue) &&
		check_numeric_i(lineNumber, nativeLineNumber) &&
		check_numeric_i(startBlock, nativeStartBlock) &&
		check_numeric_i(lengthBlock, nativeLengthBlock))
	{
		m_value = boost::make_shared< _CppAttribute<EncodingT> >(nativeAttrType,
				nativeName,
				nativeAccessSpecifier,
				nativeIsStatic,
				nativeIsConst,
				nativeIsConstexpr,
				nativeConstValue,
				nativeLineNumber,
				nativeStartBlock,
				nativeLengthBlock);
	}
}

template <class EncodingT>
boost::shared_ptr< _CppAttribute<EncodingT> > CppAttributeInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::value(boost::shared_ptr< _CppAttribute<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getAttrType() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getAttrType()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getAccessSpecifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getAccessSpecifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getIsStatic() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsStatic()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getIsConst() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsConst()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getIsConstexpr() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsConstexpr()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getConstValue() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getConstValue()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getStartBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getStartBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getLengthBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLengthBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::getCppClass()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppClassInterpreter<EncodingT>(m_value->getCppClass()) );
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setAttrType(boost::shared_ptr< Base<EncodingT> > const& attrType)
{
	typename EncodingT::string_t nativeAttrType;
	if (check_string<EncodingT>(attrType, nativeAttrType))
	{
		m_value->setAttrType(nativeAttrType);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		m_value->setName(nativeName);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setAccessSpecifier(boost::shared_ptr< Base<EncodingT> > const& accessSpecifier)
{
	typename EncodingT::string_t nativeAccessSpecifier;
	if (check_string<EncodingT>(accessSpecifier, nativeAccessSpecifier))
	{
		m_value->setAccessSpecifier(nativeAccessSpecifier);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setIsStatic(boost::shared_ptr< Base<EncodingT> > const& isStatic)
{
	long long nativeIsStatic;
	if (check_numeric_i(isStatic, nativeIsStatic))
	{
		m_value->setIsStatic(nativeIsStatic);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst)
{
	long long nativeIsConst;
	if (check_numeric_i(isConst, nativeIsConst))
	{
		m_value->setIsConst(nativeIsConst);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setIsConstexpr(boost::shared_ptr< Base<EncodingT> > const& isConstexpr)
{
	long long nativeIsConstexpr;
	if (check_numeric_i(isConstexpr, nativeIsConstexpr))
	{
		m_value->setIsConstexpr(nativeIsConstexpr);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setConstValue(boost::shared_ptr< Base<EncodingT> > const& constValue)
{
	typename EncodingT::string_t nativeConstValue;
	if (check_string<EncodingT>(constValue, nativeConstValue))
	{
		m_value->setConstValue(nativeConstValue);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setCppClass(boost::shared_ptr< Base<EncodingT> > const& cppClass)
{
	boost::shared_ptr< _CppClass<EncodingT> > nativeCppClass;
	if (check_cppClass(cppClass, nativeCppClass))
	{
		m_value->setCppClass(nativeCppClass);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	long long nativeLineNumber;
	if (check_numeric_i(lineNumber, nativeLineNumber))
	{
		m_value->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock)
{
	long long nativeStartBlock;
	if (check_numeric_i(startBlock, nativeStartBlock))
	{
		m_value->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	long long nativeLengthBlock;
	if (check_numeric_i(lengthBlock, nativeLengthBlock))
	{
		m_value->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::hasCppClass() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppClass()) );
}


template <class EncodingT>
void CppAttributeInterpreter<EncodingT>::removeCppClass()
{
	m_value->eraseCppClass();
}

template <class EncodingT>
typename EncodingT::string_t CppAttributeInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppAttributeInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppAttributeInterpreter<EncodingT>(copy_ptr(m_value)));
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
			tryInvoke(this, C("Base"), method, args, ret))
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
		o = value->value();
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
		value->value(o);
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

