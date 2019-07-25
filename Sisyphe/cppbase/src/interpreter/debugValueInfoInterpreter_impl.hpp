#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugValueInfoInterpreter<EncodingT>::DebugValueInfoInterpreter()
{
	m_value = boost::make_shared< _DebugValueInfo<EncodingT> >();
}

template <class EncodingT>
DebugValueInfoInterpreter<EncodingT>::DebugValueInfoInterpreter(boost::shared_ptr< _DebugValueInfo<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
DebugValueInfoInterpreter<EncodingT>::DebugValueInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& textValue)
{
	typename EncodingT::string_t nativeTextValue;
	if (check_string<EncodingT>(textValue, nativeTextValue))
	{
		m_value = boost::make_shared< _DebugValueInfo<EncodingT> >(nativeTextValue);
	}
}

template <class EncodingT>
boost::shared_ptr< _DebugValueInfo<EncodingT> > DebugValueInfoInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void DebugValueInfoInterpreter<EncodingT>::value(boost::shared_ptr< _DebugValueInfo<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreter<EncodingT>::getTextValue() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getTextValue()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreter<EncodingT>::getDebugVariableInfo()
{
	return boost::shared_ptr< Base<EncodingT> >( new DebugVariableInfoInterpreter<EncodingT>(m_value->getDebugVariableInfo()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreter<EncodingT>::getDebugStubInfo()
{
	return boost::shared_ptr< Base<EncodingT> >( new DebugStubInfoInterpreter<EncodingT>(m_value->getDebugStubInfo()) );
}


template <class EncodingT>
void DebugValueInfoInterpreter<EncodingT>::setTextValue(boost::shared_ptr< Base<EncodingT> > const& textValue)
{
	typename EncodingT::string_t nativeTextValue;
	if (check_string<EncodingT>(textValue, nativeTextValue))
	{
		m_value->setTextValue(nativeTextValue);
	}
}


template <class EncodingT>
void DebugValueInfoInterpreter<EncodingT>::setDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& debugVariableInfo)
{
	boost::shared_ptr< _DebugVariableInfo<EncodingT> > nativeDebugVariableInfo;
	if (check_debugVariableInfo(debugVariableInfo, nativeDebugVariableInfo))
	{
		m_value->setDebugVariableInfo(nativeDebugVariableInfo);
	}
}


template <class EncodingT>
void DebugValueInfoInterpreter<EncodingT>::setDebugStubInfo(boost::shared_ptr< Base<EncodingT> > const& debugStubInfo)
{
	boost::shared_ptr< _DebugStubInfo<EncodingT> > nativeDebugStubInfo;
	if (check_debugStubInfo(debugStubInfo, nativeDebugStubInfo))
	{
		m_value->setDebugStubInfo(nativeDebugStubInfo);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreter<EncodingT>::hasDebugVariableInfo() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullDebugVariableInfo()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreter<EncodingT>::hasDebugStubInfo() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullDebugStubInfo()) );
}


template <class EncodingT>
void DebugValueInfoInterpreter<EncodingT>::removeDebugVariableInfo()
{
	m_value->eraseDebugVariableInfo();
}


template <class EncodingT>
void DebugValueInfoInterpreter<EncodingT>::removeDebugStubInfo()
{
	m_value->eraseDebugStubInfo();
}

template <class EncodingT>
typename EncodingT::string_t DebugValueInfoInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugValueInfoInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t DebugValueInfoInterpreter<EncodingT>::getClassName() const
{
	return C("DebugValueInfo");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInfoInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("DebugValueInfo"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugValueInfo, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_debugValueInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugValueInfo<EncodingT> >& o)
{
	boost::shared_ptr< DebugValueInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugValueInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugValueInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_debugValueInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugValueInfo<EncodingT> > const& o)
{
	boost::shared_ptr< DebugValueInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugValueInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugValueInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

