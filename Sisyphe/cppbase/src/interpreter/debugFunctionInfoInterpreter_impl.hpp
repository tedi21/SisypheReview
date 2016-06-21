#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugFunctionInfoInterpreter<EncodingT>::DebugFunctionInfoInterpreter()
{
	setValue( shared_ptr< _DebugFunctionInfo<EncodingT> > (new _DebugFunctionInfo<EncodingT>()) );
}

template <class EncodingT>
DebugFunctionInfoInterpreter<EncodingT>::DebugFunctionInfoInterpreter(shared_ptr< _DebugFunctionInfo<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
DebugFunctionInfoInterpreter<EncodingT>::DebugFunctionInfoInterpreter(shared_ptr< Base<EncodingT> > const& lineNumber,
				shared_ptr< Base<EncodingT> > const& address,
				shared_ptr< Base<EncodingT> > const& debugStart,
				shared_ptr< Base<EncodingT> > const& debugEnd)
{
	int nativeLineNumber;
	int nativeAddress;
	int nativeDebugStart;
	int nativeDebugEnd;
	if (check_numeric(lineNumber, nativeLineNumber) &&
		check_numeric(address, nativeAddress) &&
		check_numeric(debugStart, nativeDebugStart) &&
		check_numeric(debugEnd, nativeDebugEnd))
	{
		setValue(shared_ptr< _DebugFunctionInfo<EncodingT> >(new _DebugFunctionInfo<EncodingT>(nativeLineNumber,
				nativeAddress,
				nativeDebugStart,
				nativeDebugEnd)));
	}
}

template <class EncodingT>
DebugFunctionInfoInterpreter<EncodingT>::~DebugFunctionInfoInterpreter()
{}

template <class EncodingT>
shared_ptr< _DebugFunctionInfo<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setValue(shared_ptr< _DebugFunctionInfo<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getIdentifier() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getLineNumber() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLineNumber()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getAddress() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getAddress()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getDebugStart() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getDebugStart()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getDebugEnd() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getDebugEnd()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getCppFunction()
{
	return shared_ptr< Base<EncodingT> >( new CppFunctionInterpreter<EncodingT>(getValue()->getCppFunction()) );
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setLineNumber(shared_ptr< Base<EncodingT> > const& lineNumber)
{
	int nativeLineNumber;
	if (check_numeric(lineNumber, nativeLineNumber))
	{
		getValue()->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setAddress(shared_ptr< Base<EncodingT> > const& address)
{
	int nativeAddress;
	if (check_numeric(address, nativeAddress))
	{
		getValue()->setAddress(nativeAddress);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setDebugStart(shared_ptr< Base<EncodingT> > const& debugStart)
{
	int nativeDebugStart;
	if (check_numeric(debugStart, nativeDebugStart))
	{
		getValue()->setDebugStart(nativeDebugStart);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setDebugEnd(shared_ptr< Base<EncodingT> > const& debugEnd)
{
	int nativeDebugEnd;
	if (check_numeric(debugEnd, nativeDebugEnd))
	{
		getValue()->setDebugEnd(nativeDebugEnd);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setCppFunction(shared_ptr< Base<EncodingT> > const& cppFunction)
{
	shared_ptr< _CppFunction<EncodingT> > nativeCppFunction;
	if (check_cppFunction(cppFunction, nativeCppFunction))
	{
		getValue()->setCppFunction(nativeCppFunction);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::hasCppFunction() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppFunction()) );
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::removeCppFunction()
{
	getValue()->eraseCppFunction();
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::removeDebugVariableInfo(shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseDebugVariableInfo(getValue()->getDebugVariableInfosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::insertDebugVariableInfo(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& debugVariableInfo)
{
	int nativePosition;
	shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
	if (check_numeric(n, nativePosition) &&
		check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
	{
		getValue()->insertDebugVariableInfo(getValue()->getDebugVariableInfosBeginning()+nativePosition, nativeDebugVariableInfo);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getDebugVariableInfo(shared_ptr< Base<EncodingT> > const& n)
{
	shared_ptr< Base<EncodingT> > res(new DebugVariableInfoInterpreter<EncodingT>());
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
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::hasDebugVariableInfos() const
{
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isDebugVariableInfosEmpty()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::debugVariableInfosCount() const
{
	return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getDebugVariableInfosSize()));
}

template <class EncodingT>
typename EncodingT::string_t DebugFunctionInfoInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new DebugFunctionInfoInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t DebugFunctionInfoInterpreter<EncodingT>::getClassName() const
{
	return C("DebugFunctionInfo");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

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
bool check_debugFunctionInfo(shared_ptr< Base<EncodingT> > const& val, shared_ptr< _DebugFunctionInfo<EncodingT> >& o)
{
	shared_ptr< DebugFunctionInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugFunctionInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugFunctionInfo expected, got " << A(val->getClassName());
	}
	return value;
}

template <class EncodingT>
bool reset_debugFunctionInfo(shared_ptr< Base<EncodingT> >& val, shared_ptr< _DebugFunctionInfo<EncodingT> > const& o)
{
	shared_ptr< DebugFunctionInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugFunctionInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugFunctionInfo expected, got " << A(val->getClassName());
	}
	return value;
}

NAMESPACE_END

#undef C
#undef A

