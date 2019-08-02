#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugFunctionInfoInterpreter<EncodingT>::DebugFunctionInfoInterpreter()
{
	m_value = boost::make_shared< _DebugFunctionInfo<EncodingT> >();
}

template <class EncodingT>
DebugFunctionInfoInterpreter<EncodingT>::DebugFunctionInfoInterpreter(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
DebugFunctionInfoInterpreter<EncodingT>::DebugFunctionInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& firstLineNumber,
				boost::shared_ptr< Base<EncodingT> > const& lastLineNumber,
				boost::shared_ptr< Base<EncodingT> > const& address)
{
	typename EncodingT::string_t nativeName;
	long long nativeFirstLineNumber;
	long long nativeLastLineNumber;
	long long nativeAddress;
	if (check_string<EncodingT>(name, nativeName) &&
		check_numeric_i(firstLineNumber, nativeFirstLineNumber) &&
		check_numeric_i(lastLineNumber, nativeLastLineNumber) &&
		check_numeric_i(address, nativeAddress))
	{
		m_value = boost::make_shared< _DebugFunctionInfo<EncodingT> >(nativeName,
				nativeFirstLineNumber,
				nativeLastLineNumber,
				nativeAddress);
	}
}

template <class EncodingT>
boost::shared_ptr< _DebugFunctionInfo<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::value(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getFirstLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getFirstLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getLastLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLastLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getAddress() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getAddress()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getDebugTypeInfo()
{
	return boost::shared_ptr< Base<EncodingT> >( new DebugTypeInfoInterpreter<EncodingT>(m_value->getDebugTypeInfo()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getDebugFileInfo()
{
	return boost::shared_ptr< Base<EncodingT> >( new DebugFileInfoInterpreter<EncodingT>(m_value->getDebugFileInfo()) );
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		m_value->setName(nativeName);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setFirstLineNumber(boost::shared_ptr< Base<EncodingT> > const& firstLineNumber)
{
	long long nativeFirstLineNumber;
	if (check_numeric_i(firstLineNumber, nativeFirstLineNumber))
	{
		m_value->setFirstLineNumber(nativeFirstLineNumber);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setLastLineNumber(boost::shared_ptr< Base<EncodingT> > const& lastLineNumber)
{
	long long nativeLastLineNumber;
	if (check_numeric_i(lastLineNumber, nativeLastLineNumber))
	{
		m_value->setLastLineNumber(nativeLastLineNumber);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setAddress(boost::shared_ptr< Base<EncodingT> > const& address)
{
	long long nativeAddress;
	if (check_numeric_i(address, nativeAddress))
	{
		m_value->setAddress(nativeAddress);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setDebugTypeInfo(boost::shared_ptr< Base<EncodingT> > const& debugTypeInfo)
{
	boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
	if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo))
	{
		m_value->setDebugTypeInfo(nativeDebugTypeInfo);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::setDebugFileInfo(boost::shared_ptr< Base<EncodingT> > const& debugFileInfo)
{
	boost::shared_ptr< _DebugFileInfo<EncodingT> > nativeDebugFileInfo;
	if (check_debugFileInfo(debugFileInfo, nativeDebugFileInfo))
	{
		m_value->setDebugFileInfo(nativeDebugFileInfo);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::hasDebugTypeInfo() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullDebugTypeInfo()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::hasDebugFileInfo() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullDebugFileInfo()) );
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::removeDebugTypeInfo()
{
	m_value->eraseDebugTypeInfo();
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::removeDebugFileInfo()
{
	m_value->eraseDebugFileInfo();
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::removeDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseDebugVariableInfo(m_value->getDebugVariableInfosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::insertDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugVariableInfo)
{
	size_t nativePosition;
	boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
	if (check_numeric_i(n, nativePosition) &&
		check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
	{
		m_value->insertDebugVariableInfo(m_value->getDebugVariableInfosBeginning()+nativePosition, nativeDebugVariableInfo);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::getDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugVariableInfoInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new DebugVariableInfoInterpreter<EncodingT>(m_value->getDebugVariableInfoAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void DebugFunctionInfoInterpreter<EncodingT>::clearDebugVariableInfos()
{
	m_value->clearDebugVariableInfos();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::hasDebugVariableInfos() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isDebugVariableInfosEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::debugVariableInfosCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getDebugVariableInfosSize()));
}

template <class EncodingT>
typename EncodingT::string_t DebugFunctionInfoInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugFunctionInfoInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t DebugFunctionInfoInterpreter<EncodingT>::getClassName() const
{
	return UCS("DebugFunctionInfo");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugFunctionInfoInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugFunctionInfo"), method, args, ret) ||
			tryInvoke(this, UCS("Base"), method, args, ret))
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
		o = value->value();
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
		value->value(o);
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

