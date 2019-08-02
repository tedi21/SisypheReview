#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugErrorInfoInterpreter<EncodingT>::DebugErrorInfoInterpreter()
{
	m_value = boost::make_shared< _DebugErrorInfo<EncodingT> >();
}

template <class EncodingT>
DebugErrorInfoInterpreter<EncodingT>::DebugErrorInfoInterpreter(boost::shared_ptr< _DebugErrorInfo<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
DebugErrorInfoInterpreter<EncodingT>::DebugErrorInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& callStack)
{
	typename EncodingT::string_t nativeCallStack;
	if (check_string<EncodingT>(callStack, nativeCallStack))
	{
		m_value = boost::make_shared< _DebugErrorInfo<EncodingT> >(nativeCallStack);
	}
}

template <class EncodingT>
boost::shared_ptr< _DebugErrorInfo<EncodingT> > DebugErrorInfoInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void DebugErrorInfoInterpreter<EncodingT>::value(boost::shared_ptr< _DebugErrorInfo<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreter<EncodingT>::getCallStack() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getCallStack()) );
}


template <class EncodingT>
void DebugErrorInfoInterpreter<EncodingT>::setCallStack(boost::shared_ptr< Base<EncodingT> > const& callStack)
{
	typename EncodingT::string_t nativeCallStack;
	if (check_string<EncodingT>(callStack, nativeCallStack))
	{
		m_value->setCallStack(nativeCallStack);
	}
}

template <class EncodingT>
typename EncodingT::string_t DebugErrorInfoInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugErrorInfoInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t DebugErrorInfoInterpreter<EncodingT>::getClassName() const
{
	return UCS("DebugErrorInfo");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugErrorInfoInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugErrorInfo"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugErrorInfo, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_debugErrorInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugErrorInfo<EncodingT> >& o)
{
	boost::shared_ptr< DebugErrorInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugErrorInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugErrorInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_debugErrorInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugErrorInfo<EncodingT> > const& o)
{
	boost::shared_ptr< DebugErrorInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugErrorInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugErrorInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

