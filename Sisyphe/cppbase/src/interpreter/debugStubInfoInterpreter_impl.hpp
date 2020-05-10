#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugStubInfoInterpreter<EncodingT>::DebugStubInfoInterpreter()
{
	m_value = boost::make_shared< _DebugStubInfo<EncodingT> >();
}

template <class EncodingT>
DebugStubInfoInterpreter<EncodingT>::DebugStubInfoInterpreter(boost::shared_ptr< _DebugStubInfo<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
DebugStubInfoInterpreter<EncodingT>::DebugStubInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& isLineSkipped)
{
	long long nativeLineNumber;
	long long nativeIsLineSkipped;
	if (check_numeric_i(lineNumber, nativeLineNumber) &&
		check_numeric_i(isLineSkipped, nativeIsLineSkipped))
	{
		m_value = boost::make_shared< _DebugStubInfo<EncodingT> >(nativeLineNumber,
				nativeIsLineSkipped);
	}
}

template <class EncodingT>
boost::shared_ptr< _DebugStubInfo<EncodingT> > DebugStubInfoInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void DebugStubInfoInterpreter<EncodingT>::value(boost::shared_ptr< _DebugStubInfo<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreter<EncodingT>::getIsLineSkipped() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsLineSkipped()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreter<EncodingT>::getDebugFileInfo()
{
	return boost::shared_ptr< Base<EncodingT> >( new DebugFileInfoInterpreter<EncodingT>(m_value->getDebugFileInfo()) );
}


template <class EncodingT>
void DebugStubInfoInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	long long nativeLineNumber;
	if (check_numeric_i(lineNumber, nativeLineNumber))
	{
		m_value->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void DebugStubInfoInterpreter<EncodingT>::setIsLineSkipped(boost::shared_ptr< Base<EncodingT> > const& isLineSkipped)
{
	long long nativeIsLineSkipped;
	if (check_numeric_i(isLineSkipped, nativeIsLineSkipped))
	{
		m_value->setIsLineSkipped(nativeIsLineSkipped);
	}
}


template <class EncodingT>
void DebugStubInfoInterpreter<EncodingT>::setDebugFileInfo(boost::shared_ptr< Base<EncodingT> > const& debugFileInfo)
{
	boost::shared_ptr< _DebugFileInfo<EncodingT> > nativeDebugFileInfo;
	if (check_debugFileInfo(debugFileInfo, nativeDebugFileInfo))
	{
		m_value->setDebugFileInfo(nativeDebugFileInfo);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreter<EncodingT>::hasDebugFileInfo() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullDebugFileInfo()) );
}


template <class EncodingT>
void DebugStubInfoInterpreter<EncodingT>::removeDebugFileInfo()
{
	m_value->eraseDebugFileInfo();
}


template <class EncodingT>
void DebugStubInfoInterpreter<EncodingT>::removeDebugValueInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseDebugValueInfo(m_value->getDebugValueInfosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void DebugStubInfoInterpreter<EncodingT>::insertDebugValueInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugValueInfo)
{
	size_t nativePosition;
	boost::shared_ptr< _DebugValueInfo<EncodingT> > nativeDebugValueInfo;
	if (check_numeric_i(n, nativePosition) &&
		check_debugValueInfo(debugValueInfo, nativeDebugValueInfo))
	{
		m_value->insertDebugValueInfo(m_value->getDebugValueInfosBeginning()+nativePosition, nativeDebugValueInfo);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreter<EncodingT>::getDebugValueInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< Base<EncodingT> > res(new DebugValueInfoInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res.reset(new DebugValueInfoInterpreter<EncodingT>(m_value->getDebugValueInfoAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void DebugStubInfoInterpreter<EncodingT>::clearDebugValueInfos()
{
	m_value->clearDebugValueInfos();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreter<EncodingT>::hasDebugValueInfos() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isDebugValueInfosEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreter<EncodingT>::debugValueInfosCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getDebugValueInfosSize()));
}

template <class EncodingT>
typename EncodingT::string_t DebugStubInfoInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugStubInfoInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t DebugStubInfoInterpreter<EncodingT>::getClassName() const
{
	return UCS("DebugStubInfo");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStubInfoInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugStubInfo"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugStubInfo, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_debugStubInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugStubInfo<EncodingT> >& o)
{
	boost::shared_ptr< DebugStubInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugStubInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugStubInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_debugStubInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugStubInfo<EncodingT> > const& o)
{
	boost::shared_ptr< DebugStubInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugStubInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugStubInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

