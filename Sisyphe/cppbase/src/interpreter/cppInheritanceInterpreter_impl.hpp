#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppInheritanceInterpreter<EncodingT>::CppInheritanceInterpreter()
{
	setValue( boost::shared_ptr< _CppInheritance<EncodingT> > (new _CppInheritance<EncodingT>()) );
}

template <class EncodingT>
CppInheritanceInterpreter<EncodingT>::CppInheritanceInterpreter(boost::shared_ptr< _CppInheritance<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CppInheritanceInterpreter<EncodingT>::CppInheritanceInterpreter(boost::shared_ptr< Base<EncodingT> > const& baseClassName,
				boost::shared_ptr< Base<EncodingT> > const& baseAccess)
{
	typename EncodingT::string_t nativeBaseClassName;
	typename EncodingT::string_t nativeBaseAccess;
	if (check_string<EncodingT>(baseClassName, nativeBaseClassName) &&
		check_string<EncodingT>(baseAccess, nativeBaseAccess))
	{
		setValue(boost::shared_ptr< _CppInheritance<EncodingT> >(new _CppInheritance<EncodingT>(nativeBaseClassName,
				nativeBaseAccess)));
	}
}

template <class EncodingT>
CppInheritanceInterpreter<EncodingT>::~CppInheritanceInterpreter()
{}

template <class EncodingT>
boost::shared_ptr< _CppInheritance<EncodingT> > CppInheritanceInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppInheritanceInterpreter<EncodingT>::setValue(boost::shared_ptr< _CppInheritance<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreter<EncodingT>::getBaseClassName() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getBaseClassName()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreter<EncodingT>::getBaseAccess() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getBaseAccess()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreter<EncodingT>::getDerived()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppClassInterpreter<EncodingT>(getValue()->getDerived()) );
}


template <class EncodingT>
void CppInheritanceInterpreter<EncodingT>::setDerived(boost::shared_ptr< Base<EncodingT> > const& derived)
{
	boost::shared_ptr< _CppClass<EncodingT> > nativeDerived;
	if (check_cppClass(derived, nativeDerived))
	{
		getValue()->setDerived(nativeDerived);
	}
}


template <class EncodingT>
void CppInheritanceInterpreter<EncodingT>::setBaseClassName(boost::shared_ptr< Base<EncodingT> > const& baseClassName)
{
	typename EncodingT::string_t nativeBaseClassName;
	if (check_string<EncodingT>(baseClassName, nativeBaseClassName))
	{
		getValue()->setBaseClassName(nativeBaseClassName);
	}
}


template <class EncodingT>
void CppInheritanceInterpreter<EncodingT>::setBaseAccess(boost::shared_ptr< Base<EncodingT> > const& baseAccess)
{
	typename EncodingT::string_t nativeBaseAccess;
	if (check_string<EncodingT>(baseAccess, nativeBaseAccess))
	{
		getValue()->setBaseAccess(nativeBaseAccess);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreter<EncodingT>::hasDerived() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullDerived()) );
}


template <class EncodingT>
void CppInheritanceInterpreter<EncodingT>::removeDerived()
{
	getValue()->eraseDerived();
}

template <class EncodingT>
typename EncodingT::string_t CppInheritanceInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppInheritanceInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CppInheritanceInterpreter<EncodingT>::getClassName() const
{
	return C("CppInheritance");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppInheritanceInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppInheritance"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppInheritance, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppInheritance(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppInheritance<EncodingT> >& o)
{
	boost::shared_ptr< CppInheritanceInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppInheritanceInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppInheritance expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cppInheritance(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppInheritance<EncodingT> > const& o)
{
	boost::shared_ptr< CppInheritanceInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppInheritanceInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppInheritance expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

