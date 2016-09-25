#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugVariableInfoInterpreter<EncodingT>::DebugVariableInfoInterpreter()
{
	setValue( boost::shared_ptr< _DebugVariableInfo<EncodingT> > (new _DebugVariableInfo<EncodingT>()) );
}

template <class EncodingT>
DebugVariableInfoInterpreter<EncodingT>::DebugVariableInfoInterpreter(boost::shared_ptr< _DebugVariableInfo<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
DebugVariableInfoInterpreter<EncodingT>::DebugVariableInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& category,
				boost::shared_ptr< Base<EncodingT> > const& debugType,
				boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& textValue)
{
	typename EncodingT::string_t nativeCategory;
	typename EncodingT::string_t nativeDebugType;
	typename EncodingT::string_t nativeName;
	typename EncodingT::string_t nativeTextValue;
	if (check_string<EncodingT>(category, nativeCategory) &&
		check_string<EncodingT>(debugType, nativeDebugType) &&
		check_string<EncodingT>(name, nativeName) &&
		check_string<EncodingT>(textValue, nativeTextValue))
	{
		setValue(boost::shared_ptr< _DebugVariableInfo<EncodingT> >(new _DebugVariableInfo<EncodingT>(nativeCategory,
				nativeDebugType,
				nativeName,
				nativeTextValue)));
	}
}

template <class EncodingT>
DebugVariableInfoInterpreter<EncodingT>::~DebugVariableInfoInterpreter()
{}

template <class EncodingT>
boost::shared_ptr< _DebugVariableInfo<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setValue(boost::shared_ptr< _DebugVariableInfo<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getCategory() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getCategory()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getDebugType() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getDebugType()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getTextValue() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getTextValue()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getDebugFunctionInfo()
{
	return boost::shared_ptr< Base<EncodingT> >( new DebugFunctionInfoInterpreter<EncodingT>(getValue()->getDebugFunctionInfo()) );
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setCategory(boost::shared_ptr< Base<EncodingT> > const& category)
{
	typename EncodingT::string_t nativeCategory;
	if (check_string<EncodingT>(category, nativeCategory))
	{
		getValue()->setCategory(nativeCategory);
	}
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setDebugType(boost::shared_ptr< Base<EncodingT> > const& debugType)
{
	typename EncodingT::string_t nativeDebugType;
	if (check_string<EncodingT>(debugType, nativeDebugType))
	{
		getValue()->setDebugType(nativeDebugType);
	}
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		getValue()->setName(nativeName);
	}
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setTextValue(boost::shared_ptr< Base<EncodingT> > const& textValue)
{
	typename EncodingT::string_t nativeTextValue;
	if (check_string<EncodingT>(textValue, nativeTextValue))
	{
		getValue()->setTextValue(nativeTextValue);
	}
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& debugFunctionInfo)
{
	boost::shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
	if (check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo))
	{
		getValue()->setDebugFunctionInfo(nativeDebugFunctionInfo);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::hasDebugFunctionInfo() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullDebugFunctionInfo()) );
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::removeDebugFunctionInfo()
{
	getValue()->eraseDebugFunctionInfo();
}

template <class EncodingT>
typename EncodingT::string_t DebugVariableInfoInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugVariableInfoInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t DebugVariableInfoInterpreter<EncodingT>::getClassName() const
{
	return C("DebugVariableInfo");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("DebugVariableInfo"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugVariableInfo, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_debugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugVariableInfo<EncodingT> >& o)
{
	boost::shared_ptr< DebugVariableInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugVariableInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugVariableInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_debugVariableInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugVariableInfo<EncodingT> > const& o)
{
	boost::shared_ptr< DebugVariableInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugVariableInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugVariableInfo expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

