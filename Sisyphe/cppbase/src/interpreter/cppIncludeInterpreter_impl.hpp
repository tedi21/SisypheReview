#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppIncludeInterpreter<EncodingT>::CppIncludeInterpreter()
{
	setValue( shared_ptr< _CppInclude<EncodingT> > (new _CppInclude<EncodingT>()) );
}

template <class EncodingT>
CppIncludeInterpreter<EncodingT>::CppIncludeInterpreter(shared_ptr< _CppInclude<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
CppIncludeInterpreter<EncodingT>::CppIncludeInterpreter(shared_ptr< Base<EncodingT> > const& fileName)
{
	typename EncodingT::string_t nativeFileName;
	if (check_string<EncodingT>(fileName, nativeFileName))
	{
		setValue(shared_ptr< _CppInclude<EncodingT> >(new _CppInclude<EncodingT>(nativeFileName)));
	}
}

template <class EncodingT>
CppIncludeInterpreter<EncodingT>::~CppIncludeInterpreter()
{}

template <class EncodingT>
shared_ptr< _CppInclude<EncodingT> > CppIncludeInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void CppIncludeInterpreter<EncodingT>::setValue(shared_ptr< _CppInclude<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppIncludeInterpreter<EncodingT>::getIdentifier() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getIdentifier()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppIncludeInterpreter<EncodingT>::getFileName() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getFileName()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppIncludeInterpreter<EncodingT>::getCppFile()
{
	return shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(getValue()->getCppFile()) );
}


template <class EncodingT>
void CppIncludeInterpreter<EncodingT>::setFileName(shared_ptr< Base<EncodingT> > const& fileName)
{
	typename EncodingT::string_t nativeFileName;
	if (check_string<EncodingT>(fileName, nativeFileName))
	{
		getValue()->setFileName(nativeFileName);
	}
}


template <class EncodingT>
void CppIncludeInterpreter<EncodingT>::setCppFile(shared_ptr< Base<EncodingT> > const& cppFile)
{
	shared_ptr< _CppFile<EncodingT> > nativeCppFile;
	if (check_cppFile(cppFile, nativeCppFile))
	{
		getValue()->setCppFile(nativeCppFile);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > CppIncludeInterpreter<EncodingT>::hasCppFile() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullCppFile()) );
}


template <class EncodingT>
void CppIncludeInterpreter<EncodingT>::removeCppFile()
{
	getValue()->eraseCppFile();
}

template <class EncodingT>
typename EncodingT::string_t CppIncludeInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppIncludeInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new CppIncludeInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t CppIncludeInterpreter<EncodingT>::getClassName() const
{
	return C("CppInclude");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > CppIncludeInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("CppInclude"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppInclude, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppInclude(shared_ptr< Base<EncodingT> > const& val, shared_ptr< _CppInclude<EncodingT> >& o)
{
	shared_ptr< CppIncludeInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppIncludeInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppInclude expected, got " << A(val->getClassName());
	}
	return value;
}

template <class EncodingT>
bool reset_cppInclude(shared_ptr< Base<EncodingT> >& val, shared_ptr< _CppInclude<EncodingT> > const& o)
{
	shared_ptr< CppIncludeInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppIncludeInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppInclude expected, got " << A(val->getClassName());
	}
	return value;
}

NAMESPACE_END

#undef C
#undef A

