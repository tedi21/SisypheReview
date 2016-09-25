#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
TextNoticeInterpreter<EncodingT>::TextNoticeInterpreter()
{
	setValue( boost::shared_ptr< _TextNotice<EncodingT> > (new _TextNotice<EncodingT>()) );
}

template <class EncodingT>
TextNoticeInterpreter<EncodingT>::TextNoticeInterpreter(boost::shared_ptr< _TextNotice<EncodingT> > const& value)
{
	setValue(value);
}

template <class EncodingT>
TextNoticeInterpreter<EncodingT>::TextNoticeInterpreter(boost::shared_ptr< Base<EncodingT> > const& description,
				boost::shared_ptr< Base<EncodingT> > const& category,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
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
		setValue(boost::shared_ptr< _TextNotice<EncodingT> >(new _TextNotice<EncodingT>(nativeDescription,
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
boost::shared_ptr< _TextNotice<EncodingT> > TextNoticeInterpreter<EncodingT>::getValue() const
{
	return m_value;
}

template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setValue(boost::shared_ptr< _TextNotice<EncodingT> > const& object)
{
	m_value = object;
	String<EncodingT>::setValue(toString());
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getRowid() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getRowid()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getDescription() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getDescription()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getCategory() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(getValue()->getCategory()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getStartBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getStartBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getLengthBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(getValue()->getLengthBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::getTextFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new TextFileInterpreter<EncodingT>(getValue()->getTextFile()) );
}


template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setDescription(boost::shared_ptr< Base<EncodingT> > const& description)
{
	typename EncodingT::string_t nativeDescription;
	if (check_string<EncodingT>(description, nativeDescription))
	{
		getValue()->setDescription(nativeDescription);
	}
}


template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setCategory(boost::shared_ptr< Base<EncodingT> > const& category)
{
	typename EncodingT::string_t nativeCategory;
	if (check_string<EncodingT>(category, nativeCategory))
	{
		getValue()->setCategory(nativeCategory);
	}
}


template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	int nativeLineNumber;
	if (check_numeric(lineNumber, nativeLineNumber))
	{
		getValue()->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setTextFile(boost::shared_ptr< Base<EncodingT> > const& textFile)
{
	boost::shared_ptr< _TextFile<EncodingT> > nativeTextFile;
	if (check_textFile(textFile, nativeTextFile))
	{
		getValue()->setTextFile(nativeTextFile);
	}
}


template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock)
{
	int nativeStartBlock;
	if (check_numeric(startBlock, nativeStartBlock))
	{
		getValue()->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void TextNoticeInterpreter<EncodingT>::setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	int nativeLengthBlock;
	if (check_numeric(lengthBlock, nativeLengthBlock))
	{
		getValue()->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::hasTextFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNullTextFile()) );
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
boost::shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new TextNoticeInterpreter<EncodingT>(copy_ptr(getValue())));
}

template <class EncodingT>
typename EncodingT::string_t TextNoticeInterpreter<EncodingT>::getClassName() const
{
	return C("TextNotice");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TextNoticeInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

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
bool check_textNotice(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _TextNotice<EncodingT> >& o)
{
	boost::shared_ptr< TextNoticeInterpreter<EncodingT> > value  = dynamic_pointer_cast< TextNoticeInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->getValue();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "TextNotice expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_textNotice(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _TextNotice<EncodingT> > const& o)
{
	boost::shared_ptr< TextNoticeInterpreter<EncodingT> > value  = dynamic_pointer_cast< TextNoticeInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "TextNotice expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

