#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugFunctionInfoInterpreter<EncodingT>::DebugFunctionInfoInterpreter()
{
	setValue( boost::shared_ptr< _DebugFunctionInfo<EncodingT> > (new _DebugFunctionInfo<EncodingT>()) );
}

template <class EncodingT>
DebugFunctionInfoInterpreter<EncodingT>::DebugFunctionInfoInterpreter(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
DebugFunctionInfoInterpreter<EncodingT>::DebugFunctionInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& address,
				boost::shared_ptr< Base<EncodingT> > const& debugStart,
				boost::shared_ptr< Base<EncodingT> > const& debugEnd,
				boost::shared_ptr< Base<EncodingT> > const& debugReturnType)
{
	int nativeLineNumber;
	int nativeAddress;
	int nativeDebugStart;
	int nativeDebugEnd;
	typename EncodingT::string_t nativeDebugReturnType;
	if (check_numeric(lineNumber, nativeLineNumber) &&
		check_numeric(address, nativeAddress) &&
		check_numeric(debugStart, nativeDebugStart) &&
		check_numeric(debugEnd, nativeDebugEnd) &&
		check_string<EncodingT>(debugReturnType, nativeDebugReturnType))
	{
		setValue(boost::shared_ptr< _DebugFunctionInfo<EncodingT> >(new _DebugFunctionInfo<EncodingT>(nativeLineNumber,
				nativeAddress,
				nativeDebugStart,
				nativeDebugEnd,
				nativeDebugReturnType)));
	}
}

template <class EncodingT>
DebugFunctionInfoInterpreter<EncodingT>::~DebugFunctionInfoInterpreter()
{}

template <class EncodingT>
boost::shared_ptr< _DebugFunctionInfo<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setValue(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getAddress() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getAddress()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getDebugStart() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getDebugStart()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getDebugEnd() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getDebugEnd()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getDebugReturnType() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getDebugReturnType()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getCppFunction()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFunctionInterpreter<EncodingT>(getValue()->getCppFunction()) );
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	int nativeLineNumber;
	if (check_numeric(lineNumber, nativeLineNumber))
	{
		getValue()->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setAddress(boost::shared_ptr< Base<EncodingT> > const& address)
{
	int nativeAddress;
	if (check_numeric(address, nativeAddress))
	{
		getValue()->setAddress(nativeAddress);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setDebugStart(boost::shared_ptr< Base<EncodingT> > const& debugStart)
{
	int nativeDebugStart;
	if (check_numeric(debugStart, nativeDebugStart))
	{
		getValue()->setDebugStart(nativeDebugStart);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setDebugEnd(boost::shared_ptr< Base<EncodingT> > const& debugEnd)
{
	int nativeDebugEnd;
	if (check_numeric(debugEnd, nativeDebugEnd))
	{
		getValue()->setDebugEnd(nativeDebugEnd);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setDebugReturnType(boost::shared_ptr< Base<EncodingT> > const& debugReturnType)
{
	typename EncodingT::string_t nativeDebugReturnType;
	if (check_string<EncodingT>(debugReturnType, nativeDebugReturnType))
	{
		getValue()->setDebugReturnType(nativeDebugReturnType);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setCppFunction(boost::shared_ptr< Base<EncodingT> > const& cppFunction)
{
	boost::shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
	if (check_cppFunction(cppFunction, nativeCppFunction))
	{
		getValue()->setCppFunction(nativeCppFunction);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::hasCppFunction() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppFunction()) );
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::removeCppFunction()
{
	getValue()->eraseCppFunction();
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::removeDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseDebugVariableInfo(getValue()->getDebugVariableInfosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::insertDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugVariableInfo)
{
	int nativePosition;
	boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
	if (check_numeric(n, nativePosition) &&
		check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
	{
		getValue()->insertDebugVariableInfo(getValue()->getDebugVariableInfosBeginning()+nativePosition, nativeDebugVariableInfo);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugVariableInfoInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new DebugVariableInfoInterpreter<EncodingT>(getValue()->getDebugVariableInfoAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::clearDebugVariableInfos()
{
	getValue()->clearDebugVariableInfos();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::hasDebugVariableInfos() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isDebugVariableInfosEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::debugVariableInfosCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getDebugVariableInfosSize()));
}

template <class EncodingT>
typename EncodingT::string_t DebugFunctionInfoInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugFunctionInfoInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t DebugFunctionInfoInterpreter<EncodingT>::getClassName() const
{
	return C("DebugFunctionInfo");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("DebugFunctionInfo"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugFunctionInfo, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_debugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugFunctionInfo<EncodingT> >& o)
{
	boost::shared_ptr< DebugFunctionInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugFunctionInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugFunctionInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_debugFunctionInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugFunctionInfo<EncodingT> > const& o)
{
	boost::shared_ptr< DebugFunctionInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugFunctionInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugFunctionInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

