#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
TextNoticeInterpreter<EncodingT>::TextNoticeInterpreter()
{
	setValue( shared_ptr< _TextNotice<EncodingT> > (new _TextNotice<EncodingT>()) );
}

template <class EncodingT>
TextNoticeInterpreter<EncodingT>::TextNoticeInterpreter(shared_ptr< _TextNotice<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
TextNoticeInterpreter<EncodingT>::TextNoticeInterpreter(shared_ptr< Base<EncodingT> > const& description,
				shared_ptr< Base<EncodingT> > const& category,
				shared_ptr< Base<EncodingT> > const& lineNumber,
				shared_ptr< Base<EncodingT> > const& startBlock,
				shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	typename EncodingT::string_t nativeDescription;
	typename EncodingT::string_t nativeCategory;
	int nativeLineNumber;
	int nativeStartBlock;
	int nativeLengthBlock;
	if (check_string<EncodingT>(description, nativeDescription) &&
		check_string<EncodingT>(category, nativeCategory) &&
		check_numeric(lineNumber, nativeLineNumber) &&
		check_numeric(startBlock, nativeStartBlock) &&
		check_numeric(lengthBlock, nativeLengthBlock))
	{
		setValue(shared_ptr< _TextNotice<EncodingT> >(new _TextNotice<EncodingT>(nativeDescription,
				nativeCategory,
				nativeLineNumber,
				nativeStartBlock,
				nativeLengthBlock)));
	}
}

template <class EncodingT>
TextNoticeInterpreter<EncodingT>::~TextNoticeInterpreter()
{}

template <class EncodingT>
shared_ptr< _TextNotice<EncodingT> > TextNoticeInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setValue(shared_ptr< _TextNotice<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getRowid() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getRowid()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getDescription() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getDescription()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getCategory() const
{
	return shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getCategory()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getLineNumber() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLineNumber()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getStartBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getLengthBlock() const
{
	return shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthBlock()) );
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getTextFile()
{
	return shared_ptr< Base<EncodingT> >( new TextFileInterpreter<EncodingT>(getValue()->getTextFile()) );
}


template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setDescription(shared_ptr< Base<EncodingT> > const& description)
{
	typename EncodingT::string_t nativeDescription;
	if (check_string<EncodingT>(description, nativeDescription))
	{
		getValue()->setDescription(nativeDescription);
	}
}


template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setCategory(shared_ptr< Base<EncodingT> > const& category)
{
	typename EncodingT::string_t nativeCategory;
	if (check_string<EncodingT>(category, nativeCategory))
	{
		getValue()->setCategory(nativeCategory);
	}
}


template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setLineNumber(shared_ptr< Base<EncodingT> > const& lineNumber)
{
	int nativeLineNumber;
	if (check_numeric(lineNumber, nativeLineNumber))
	{
		getValue()->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setTextFile(shared_ptr< Base<EncodingT> > const& textFile)
{
	shared_ptr< _TextFile<EncodingT> > nativeTextFile;
	if (check_textFile(textFile, nativeTextFile))
	{
		getValue()->setTextFile(nativeTextFile);
	}
}


template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setStartBlock(shared_ptr< Base<EncodingT> > const& startBlock)
{
	int nativeStartBlock;
	if (check_numeric(startBlock, nativeStartBlock))
	{
		getValue()->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setLengthBlock(shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	int nativeLengthBlock;
	if (check_numeric(lengthBlock, nativeLengthBlock))
	{
		getValue()->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::hasTextFile() const
{
	return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullTextFile()) );
}


template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::removeTextFile()
{
	getValue()->eraseTextFile();
}

template <class EncodingT>
typename EncodingT::string_t TextNoticeInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *(getValue());
	return C(stream.str());
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new TextNoticeInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t TextNoticeInterpreter<EncodingT>::getClassName() const
{
	return C("TextNotice");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("TextNotice"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in TextNotice, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_textNotice(shared_ptr< Base<EncodingT> > const& val, shared_ptr< _TextNotice<EncodingT> >& o)
{
	shared_ptr< TextNoticeInterpreter<EncodingT> > value  = dynamic_pointer_cast< TextNoticeInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "TextNotice expected, got " << A(val->getClassName());
	}
	return value;
}

template <class EncodingT>
bool reset_textNotice(shared_ptr< Base<EncodingT> >& val, shared_ptr< _TextNotice<EncodingT> > const& o)
{
	shared_ptr< TextNoticeInterpreter<EncodingT> > value  = dynamic_pointer_cast< TextNoticeInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "TextNotice expected, got " << A(val->getClassName());
	}
	return value;
}

NAMESPACE_END

#undef C
#undef A

