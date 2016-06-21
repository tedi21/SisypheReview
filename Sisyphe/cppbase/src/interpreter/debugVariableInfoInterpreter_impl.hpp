#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugVariableInfoInterpreter<EncodingT>::DebugVariableInfoInterpreter()
{
	setValue( shared_ptr< _DebugVariableInfo<EncodingT> > (new _DebugVariableInfo<EncodingT>()) );
}

template <class EncodingT>
DebugVariableInfoInterpreter<EncodingT>::DebugVariableInfoInterpreter(shared_ptr< _DebugVariableInfo<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
DebugVariableInfoInterpreter<EncodingT>::DebugVariableInfoInterpreter(shared_ptr< Base<EncodingT> > const& category,
				shared_ptr< Base<EncodingT> > const& type,
				shared_ptr< Base<EncodingT> > const& name,
				shared_ptr< Base<EncodingT> > const& textValue)
{
	typename EncodingT::string_t nativeCategory;
	typename EncodingT::string_t nativeType;
	typename EncodingT::string_t nativeName;
	typename EncodingT::string_t nativeTextValue;
	if (check_string<EncodingT>(category, nativeCategory) &&
		check_string<EncodingT>(type, nativeType) &&
		check_string<EncodingT>(name, nativeName) &&
		check_string<EncodingT>(textValue, nativeTextValue))
	{
		setValue(shared_ptr< _DebugVariableInfo<EncodingT> >(new _DebugVariableInfo<EncodingT>(nativeCategory,
				nativeType,
				nativeName,
				nativeTextValue)));
	}
}

template <class EncodingT>
DebugVariableInfoInterpreter<EncodingT>::~DebugVariableInfoInterpreter()
{}

template <class EncodingT>
shared_ptr< _DebugVariableInfo<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setValue(shared_ptr< _DebugVariableInfo<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getIdentifier() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getCategory() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getCategory()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getType() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getType()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getName() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getName()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getTextValue() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getTextValue()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getDebugFunctionInfo()
{
	return shared_ptr< Base<EncodingT> >( new DebugFunctionInfoInterpreter<EncodingT>(getValue()->getDebugFunctionInfo()) );
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setCategory(shared_ptr< Base<EncodingT> > const& category)
{
	typename EncodingT::string_t nativeCategory;
	if (check_string<EncodingT>(category, nativeCategory))
	{
		getValue()->setCategory(nativeCategory);
	}
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setType(shared_ptr< Base<EncodingT> > const& type)
{
	typename EncodingT::string_t nativeType;
	if (check_string<EncodingT>(type, nativeType))
	{
		getValue()->setType(nativeType);
	}
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setName(shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		getValue()->setName(nativeName);
	}
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setTextValue(shared_ptr< Base<EncodingT> > const& textValue)
{
	typename EncodingT::string_t nativeTextValue;
	if (check_string<EncodingT>(textValue, nativeTextValue))
	{
		getValue()->setTextValue(nativeTextValue);
	}
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setDebugFunctionInfo(shared_ptr< Base<EncodingT> > const& debugFunctionInfo)
{
	shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
	if (check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo))
	{
		getValue()->setDebugFunctionInfo(nativeDebugFunctionInfo);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::hasDebugFunctionInfo() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullDebugFunctionInfo()) );
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
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new DebugVariableInfoInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t DebugVariableInfoInterpreter<EncodingT>::getClassName() const
{
	return C("DebugVariableInfo");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

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
bool check_debugVariableInfo(shared_ptr< Base<EncodingT> > const& val, shared_ptr< _DebugVariableInfo<EncodingT> >& o)
{
	shared_ptr< DebugVariableInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugVariableInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugVariableInfo expected, got " << A(val->getClassName());
	}
	return value;
}

template <class EncodingT>
bool reset_debugVariableInfo(shared_ptr< Base<EncodingT> >& val, shared_ptr< _DebugVariableInfo<EncodingT> > const& o)
{
	shared_ptr< DebugVariableInfoInterpreter<EncodingT> > value  = dynamic_pointer_cast< DebugVariableInfoInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DebugVariableInfo expected, got " << A(val->getClassName());
	}
	return value;
}

NAMESPACE_END

#undef C
#undef A

