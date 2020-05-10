#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
RuleInterpreter<EncodingT>::RuleInterpreter()
{
	m_value = boost::make_shared< _Rule<EncodingT> >();
}

template <class EncodingT>
RuleInterpreter<EncodingT>::RuleInterpreter(boost::shared_ptr< _Rule<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
RuleInterpreter<EncodingT>::RuleInterpreter(boost::shared_ptr< Base<EncodingT> > const& number,
				boost::shared_ptr< Base<EncodingT> > const& description,
				boost::shared_ptr< Base<EncodingT> > const& enabled)
{
	long long nativeNumber;
	typename EncodingT::string_t nativeDescription;
	long long nativeEnabled;
	if (check_numeric_i(number, nativeNumber) &&
		check_string<EncodingT>(description, nativeDescription) &&
		check_numeric_i(enabled, nativeEnabled))
	{
		m_value = boost::make_shared< _Rule<EncodingT> >(nativeNumber,
				nativeDescription,
				nativeEnabled);
	}
}

template <class EncodingT>
boost::shared_ptr< _Rule<EncodingT> > RuleInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void RuleInterpreter<EncodingT>::value(boost::shared_ptr< _Rule<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreter<EncodingT>::getNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreter<EncodingT>::getDescription() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getDescription()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreter<EncodingT>::getEnabled() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getEnabled()) );
}


template <class EncodingT>
void RuleInterpreter<EncodingT>::setNumber(boost::shared_ptr< Base<EncodingT> > const& number)
{
	long long nativeNumber;
	if (check_numeric_i(number, nativeNumber))
	{
		m_value->setNumber(nativeNumber);
	}
}


template <class EncodingT>
void RuleInterpreter<EncodingT>::setDescription(boost::shared_ptr< Base<EncodingT> > const& description)
{
	typename EncodingT::string_t nativeDescription;
	if (check_string<EncodingT>(description, nativeDescription))
	{
		m_value->setDescription(nativeDescription);
	}
}


template <class EncodingT>
void RuleInterpreter<EncodingT>::setEnabled(boost::shared_ptr< Base<EncodingT> > const& enabled)
{
	long long nativeEnabled;
	if (check_numeric_i(enabled, nativeEnabled))
	{
		m_value->setEnabled(nativeEnabled);
	}
}

template <class EncodingT>
typename EncodingT::string_t RuleInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new RuleInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t RuleInterpreter<EncodingT>::getClassName() const
{
	return UCS("Rule");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("Rule"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in Rule, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_rule(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _Rule<EncodingT> >& o)
{
	boost::shared_ptr< RuleInterpreter<EncodingT> > value  = dynamic_pointer_cast< RuleInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "Rule expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_rule(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _Rule<EncodingT> > const& o)
{
	boost::shared_ptr< RuleInterpreter<EncodingT> > value  = dynamic_pointer_cast< RuleInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "Rule expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

