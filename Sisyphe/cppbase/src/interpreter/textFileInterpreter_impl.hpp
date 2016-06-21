#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
TextFileInterpreter<EncodingT>::TextFileInterpreter()
{
	setValue( shared_ptr< _TextFile<EncodingT> > (new _TextFile<EncodingT>()) );
}

template <class EncodingT>
TextFileInterpreter<EncodingT>::TextFileInterpreter(shared_ptr< _TextFile<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
TextFileInterpreter<EncodingT>::TextFileInterpreter(shared_ptr< Base<EncodingT> > const& content)
{
	typename EncodingT::string_t nativeContent;
	if (check_string<EncodingT>(content, nativeContent))
	{
		setValue(shared_ptr< _TextFile<EncodingT> >(new _TextFile<EncodingT>(nativeContent)));
	}
}

template <class EncodingT>
TextFileInterpreter<EncodingT>::~TextFileInterpreter()
{}

template <class EncodingT>
shared_ptr< _TextFile<EncodingT> > TextFileInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void TextFileInterpreter<EncodingT>::setValue(shared_ptr< _TextFile<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::getRowid() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getRowid()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::getContent() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getContent()) );
}


template <class EncodingT>
void TextFileInterpreter<EncodingT>::setContent(shared_ptr< Base<EncodingT> > const& content)
{
	typename EncodingT::string_t nativeContent;
	if (check_string<EncodingT>(content, nativeContent))
	{
		getValue()->setContent(nativeContent);
	}
}


template <class EncodingT>
void TextFileInterpreter<EncodingT>::removeTextNotice(shared_ptr< Base<EncodingT> > const& n)
{
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		getValue()->eraseTextNotice(getValue()->getTextNoticesBeginning()+nativePosition);
	}
}


template <class EncodingT>
void TextFileInterpreter<EncodingT>::insertTextNotice(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& textNotice)
{
	int nativePosition;
	shared_ptr< _TextNotice<EncodingT> > nativeTextNotice;
	if (check_numeric(n, nativePosition) &&
		check_textNotice(textNotice, nativeTextNotice))
	{
		getValue()->insertTextNotice(getValue()->getTextNoticesBeginning()+nativePosition, nativeTextNotice);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::getTextNotice(shared_ptr< Base<EncodingT> > const& n)
{
	shared_ptr< Base<EncodingT> > res(new TextNoticeInterpreter<EncodingT>());
	int nativePosition;
	if (check_numeric(n, nativePosition))
	{
		res.reset(new TextNoticeInterpreter<EncodingT>(getValue()->getTextNoticeAt(nativePosition)));
	}
	return res;
}


template <class EncodingT>
void TextFileInterpreter<EncodingT>::clearTextNotices()
{
	getValue()->clearTextNotices();
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::hasTextNotices() const
{
	return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->isTextNoticesEmpty()));
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::textNoticesCount() const
{
	return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->getTextNoticesSize()));
}

template <class EncodingT>
typename EncodingT::string_t TextFileInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new TextFileInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t TextFileInterpreter<EncodingT>::getClassName() const
{
	return C("TextFile");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextFileInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("TextFile"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in TextFile, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_textFile(shared_ptr< Base<EncodingT> > const& val, shared_ptr< _TextFile<EncodingT> >& o)
{
	shared_ptr< TextFileInterpreter<EncodingT> > value  = dynamic_pointer_cast< TextFileInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "TextFile expected, got " << A(val->getClassName());
	}
	return value;
}

template <class EncodingT>
bool reset_textFile(shared_ptr< Base<EncodingT> >& val, shared_ptr< _TextFile<EncodingT> > const& o)
{
	shared_ptr< TextFileInterpreter<EncodingT> > value  = dynamic_pointer_cast< TextFileInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "TextFile expected, got " << A(val->getClassName());
	}
	return value;
}

NAMESPACE_END

#undef C
#undef A

