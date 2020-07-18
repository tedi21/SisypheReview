#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DebugVariableInfoInterpreter<EncodingT>::DebugVariableInfoInterpreter()
{
	m_value = boost::make_shared< _DebugVariableInfo<EncodingT> >();
}

template <class EncodingT>
DebugVariableInfoInterpreter<EncodingT>::DebugVariableInfoInterpreter(boost::shared_ptr< _DebugVariableInfo<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
DebugVariableInfoInterpreter<EncodingT>::DebugVariableInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& category,
				boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeCategory;
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(category, nativeCategory) &&
		check_string<EncodingT>(name, nativeName))
	{
		m_value = boost::make_shared< _DebugVariableInfo<EncodingT> >(nativeCategory,
				nativeName);
	}
}

template <class EncodingT>
boost::shared_ptr< _DebugVariableInfo<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::value(boost::shared_ptr< _DebugVariableInfo<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getCategory() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getCategory()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getDebugTypeInfo()
{
	return boost::shared_ptr< Base<EncodingT> >( new DebugTypeInfoInterpreter<EncodingT>(m_value->getDebugTypeInfo()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getDebugFunctionInfo()
{
	return boost::shared_ptr< Base<EncodingT> >( new DebugFunctionInfoInterpreter<EncodingT>(m_value->getDebugFunctionInfo()) );
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setCategory(boost::shared_ptr< Base<EncodingT> > const& category)
{
	typename EncodingT::string_t nativeCategory;
	if (check_string<EncodingT>(category, nativeCategory))
	{
		m_value->setCategory(nativeCategory);
	}
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setName(boost::shared_ptr< Base<EncodingT> > const& name)
{
	typename EncodingT::string_t nativeName;
	if (check_string<EncodingT>(name, nativeName))
	{
		m_value->setName(nativeName);
	}
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setDebugTypeInfo(boost::shared_ptr< Base<EncodingT> > const& debugTypeInfo)
{
	boost::shared_ptr< _DebugTypeInfo<EncodingT> > nativeDebugTypeInfo;
	if (check_debugTypeInfo(debugTypeInfo, nativeDebugTypeInfo))
	{
		m_value->setDebugTypeInfo(nativeDebugTypeInfo);
	}
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::setDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& debugFunctionInfo)
{
	boost::shared_ptr< _DebugFunctionInfo<EncodingT> > nativeDebugFunctionInfo;
	if (check_debugFunctionInfo(debugFunctionInfo, nativeDebugFunctionInfo))
	{
		m_value->setDebugFunctionInfo(nativeDebugFunctionInfo);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::hasDebugTypeInfo() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullDebugTypeInfo()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::hasDebugFunctionInfo() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullDebugFunctionInfo()) );
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::removeDebugTypeInfo()
{
	m_value->eraseDebugTypeInfo();
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::removeDebugFunctionInfo()
{
	m_value->eraseDebugFunctionInfo();
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::removeDebugValueInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		m_value->eraseDebugValueInfo(m_value->getDebugValueInfosBeginning()+nativePosition);
	}
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::insertDebugValueInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugValueInfo)
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
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::getDebugValueInfo(boost::shared_ptr< Base<EncodingT> > const& n)
{
	boost::shared_ptr< DebugValueInfoInterpreter<EncodingT> > res(new DebugValueInfoInterpreter<EncodingT>());
	size_t nativePosition;
	if (check_numeric_i(n, nativePosition))
	{
		res->value(m_value->getDebugValueInfoAt(nativePosition));
	}
	return res;
}


template <class EncodingT>
void DebugVariableInfoInterpreter<EncodingT>::clearDebugValueInfos()
{
	m_value->clearDebugValueInfos();
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::hasDebugValueInfos() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value->isDebugValueInfosEmpty()));
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::debugValueInfosCount() const
{
	return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value->getDebugValueInfosSize()));
}

template <class EncodingT>
typename EncodingT::string_t DebugVariableInfoInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugVariableInfoInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t DebugVariableInfoInterpreter<EncodingT>::getClassName() const
{
	return UCS("DebugVariableInfo");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugVariableInfoInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugVariableInfo"), method, args, ret) ||
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
		o = value->value();
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
		value->value(o);
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

