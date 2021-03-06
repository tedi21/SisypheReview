#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
RuleInterpreterAccess<EncodingT>::RuleInterpreterAccess()
{
	m_object = _RuleAccess<EncodingT>::getInstance();
	m_error = false;
}

template <class EncodingT>
typename EncodingT::string_t RuleInterpreterAccess<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreterAccess<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new RuleInterpreterAccess<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t RuleInterpreterAccess<EncodingT>::getClassName() const
{
	return UCS("RuleAccess");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("RuleAccess"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in RuleAccess, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _Rule<EncodingT> > >& value) const
{
	boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
	for (size_t i=0; i<value.size(); ++i)
	{
		arr->addValue(boost::shared_ptr< Base<EncodingT> >(new RuleInterpreter<EncodingT>(value[i])));
	}
	return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreterAccess<EncodingT>::getAllRules()
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		res = convert_array(m_object->getAllRules());
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreterAccess<EncodingT>::getManyRules(const boost::shared_ptr< Base<EncodingT> >& filter)
{
	boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());
	clearError();
	try
	{
		typename EncodingT::string_t nativeFilter;
		if (check_string<EncodingT>(filter, nativeFilter))
		{
			res = convert_array(m_object->getManyRules(nativeFilter));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreterAccess<EncodingT>::getOneRule(boost::shared_ptr< Base<EncodingT> > const& identifier)
{
	boost::shared_ptr< RuleInterpreter<EncodingT> > res(new RuleInterpreter<EncodingT>());
	clearError();
	try
	{
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier))
		{
			res->value(m_object->getOneRule(nativeIdentifier));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreterAccess<EncodingT>::selectOneRule(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait)
{
	boost::shared_ptr< RuleInterpreter<EncodingT> > res(new RuleInterpreter<EncodingT>());
	clearError();
	try
	{
		bool nativeNoWait;
		long long nativeIdentifier;
		if (check_numeric_i(identifier, nativeIdentifier) &&
			check_bool(nowait, nativeNoWait))
		{
			res->value(m_object->selectOneRule(nativeIdentifier,
				nativeNoWait));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void RuleInterpreterAccess<EncodingT>::cancelSelection()
{
	clearError();
	try
	{
		m_object->cancelSelection();
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreterAccess<EncodingT>::isSelectedRule(const boost::shared_ptr< Base<EncodingT> >& rule)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _Rule<EncodingT> > nativeRule;
		if (check_rule(rule, nativeRule))
		{
			res->value(m_object->isSelectedRule(nativeRule));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreterAccess<EncodingT>::isModifiedRule(const boost::shared_ptr< Base<EncodingT> >& rule)
{
	boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
	clearError();
	try
	{
		boost::shared_ptr< _Rule<EncodingT> > nativeRule;
		if (check_rule(rule, nativeRule))
		{
			res->value(m_object->isModifiedRule(nativeRule));
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
	return res;
}

template <class EncodingT>
void RuleInterpreterAccess<EncodingT>::updateRule(boost::shared_ptr< Base<EncodingT> >& rule)
{
	clearError();
	try
	{
		boost::shared_ptr< _Rule<EncodingT> > nativeRule;
		if (check_rule(rule, nativeRule))
		{
			m_object->updateRule(nativeRule);
			reset_rule(rule, nativeRule);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void RuleInterpreterAccess<EncodingT>::insertRule(boost::shared_ptr< Base<EncodingT> >& rule)
{
	clearError();
	try
	{
		boost::shared_ptr< _Rule<EncodingT> > nativeRule;
		if (check_rule(rule, nativeRule))
		{
			m_object->insertRule(nativeRule);
			reset_rule(rule, nativeRule);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void RuleInterpreterAccess<EncodingT>::deleteRule(boost::shared_ptr< Base<EncodingT> >& rule)
{
	clearError();
	try
	{
		boost::shared_ptr< _Rule<EncodingT> > nativeRule;
		if (check_rule(rule, nativeRule))
		{
			m_object->deleteRule(nativeRule);
			reset_rule(rule, nativeRule);
		}
	}
	catch (std::exception& e)
	{
		setError(e);
	}
}

template <class EncodingT>
void RuleInterpreterAccess<EncodingT>::setError(const std::exception& error)
{
	m_error = true;
	m_errorText = error.what();
}

template <class EncodingT>
void RuleInterpreterAccess<EncodingT>::clearError()
{
	m_error = false;
	m_errorText.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > RuleInterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
{
	boost::shared_ptr< String<EncodingT> > str  = dynamic_pointer_cast< String<EncodingT> >(text);
	if (str)
	{
		str->value(C(m_errorText));
	}
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(m_error));
}

NAMESPACE_END

#undef C
#undef A

