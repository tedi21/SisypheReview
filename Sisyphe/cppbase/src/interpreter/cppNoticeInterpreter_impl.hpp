#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
CppNoticeInterpreter<EncodingT>::CppNoticeInterpreter()
{
	m_value = boost::make_shared< _CppNotice<EncodingT> >();
}

template <class EncodingT>
CppNoticeInterpreter<EncodingT>::CppNoticeInterpreter(boost::shared_ptr< _CppNotice<EncodingT> > const& value)
{
	m_value = value;
}

template <class EncodingT>
CppNoticeInterpreter<EncodingT>::CppNoticeInterpreter(boost::shared_ptr< Base<EncodingT> > const& description,
				boost::shared_ptr< Base<EncodingT> > const& category,
				boost::shared_ptr< Base<EncodingT> > const& ruleNumber,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock,
				boost::shared_ptr< Base<EncodingT> > const& isNew,
				boost::shared_ptr< Base<EncodingT> > const& commitHash,
				boost::shared_ptr< Base<EncodingT> > const& commitDate,
				boost::shared_ptr< Base<EncodingT> > const& commitAuthor,
				boost::shared_ptr< Base<EncodingT> > const& commitLine)
{
	typename EncodingT::string_t nativeDescription;
	typename EncodingT::string_t nativeCategory;
	long long nativeRuleNumber;
	long long nativeLineNumber;
	long long nativeStartBlock;
	long long nativeLengthBlock;
	long long nativeIsNew;
	typename EncodingT::string_t nativeCommitHash;
	typename EncodingT::string_t nativeCommitDate;
	typename EncodingT::string_t nativeCommitAuthor;
	long long nativeCommitLine;
	if (check_string<EncodingT>(description, nativeDescription) &&
		check_string<EncodingT>(category, nativeCategory) &&
		check_numeric_i(ruleNumber, nativeRuleNumber) &&
		check_numeric_i(lineNumber, nativeLineNumber) &&
		check_numeric_i(startBlock, nativeStartBlock) &&
		check_numeric_i(lengthBlock, nativeLengthBlock) &&
		check_numeric_i(isNew, nativeIsNew) &&
		check_string<EncodingT>(commitHash, nativeCommitHash) &&
		check_string<EncodingT>(commitDate, nativeCommitDate) &&
		check_string<EncodingT>(commitAuthor, nativeCommitAuthor) &&
		check_numeric_i(commitLine, nativeCommitLine))
	{
		m_value = boost::make_shared< _CppNotice<EncodingT> >(nativeDescription,
				nativeCategory,
				nativeRuleNumber,
				nativeLineNumber,
				nativeStartBlock,
				nativeLengthBlock,
				nativeIsNew,
				nativeCommitHash,
				nativeCommitDate,
				nativeCommitAuthor,
				nativeCommitLine);
	}
}

template <class EncodingT>
boost::shared_ptr< _CppNotice<EncodingT> > CppNoticeInterpreter<EncodingT>::value() const
{
	return m_value;
}

template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::value(boost::shared_ptr< _CppNotice<EncodingT> > const& object)
{
	m_value = object;
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::getIdentifier() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIdentifier()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::getDescription() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getDescription()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::getCategory() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getCategory()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::getRuleNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getRuleNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::getLineNumber() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLineNumber()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::getStartBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getStartBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::getLengthBlock() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getLengthBlock()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::getIsNew() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getIsNew()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::getCommitHash() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getCommitHash()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::getCommitDate() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getCommitDate()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::getCommitAuthor() const
{
	return boost::shared_ptr< Base<EncodingT> >( new String<EncodingT>(m_value->getCommitAuthor()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::getCommitLine() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Numeric<EncodingT>(m_value->getCommitLine()) );
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::getCppFile()
{
	return boost::shared_ptr< Base<EncodingT> >( new CppFileInterpreter<EncodingT>(m_value->getCppFile()) );
}


template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::setDescription(boost::shared_ptr< Base<EncodingT> > const& description)
{
	typename EncodingT::string_t nativeDescription;
	if (check_string<EncodingT>(description, nativeDescription))
	{
		m_value->setDescription(nativeDescription);
	}
}


template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::setCategory(boost::shared_ptr< Base<EncodingT> > const& category)
{
	typename EncodingT::string_t nativeCategory;
	if (check_string<EncodingT>(category, nativeCategory))
	{
		m_value->setCategory(nativeCategory);
	}
}


template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::setRuleNumber(boost::shared_ptr< Base<EncodingT> > const& ruleNumber)
{
	long long nativeRuleNumber;
	if (check_numeric_i(ruleNumber, nativeRuleNumber))
	{
		m_value->setRuleNumber(nativeRuleNumber);
	}
}


template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::setCppFile(boost::shared_ptr< Base<EncodingT> > const& cppFile)
{
	boost::shared_ptr< _CppFile<EncodingT> > nativeCppFile;
	if (check_cppFile(cppFile, nativeCppFile))
	{
		m_value->setCppFile(nativeCppFile);
	}
}


template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber)
{
	long long nativeLineNumber;
	if (check_numeric_i(lineNumber, nativeLineNumber))
	{
		m_value->setLineNumber(nativeLineNumber);
	}
}


template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock)
{
	long long nativeStartBlock;
	if (check_numeric_i(startBlock, nativeStartBlock))
	{
		m_value->setStartBlock(nativeStartBlock);
	}
}


template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock)
{
	long long nativeLengthBlock;
	if (check_numeric_i(lengthBlock, nativeLengthBlock))
	{
		m_value->setLengthBlock(nativeLengthBlock);
	}
}


template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::setIsNew(boost::shared_ptr< Base<EncodingT> > const& isNew)
{
	long long nativeIsNew;
	if (check_numeric_i(isNew, nativeIsNew))
	{
		m_value->setIsNew(nativeIsNew);
	}
}


template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::setCommitHash(boost::shared_ptr< Base<EncodingT> > const& commitHash)
{
	typename EncodingT::string_t nativeCommitHash;
	if (check_string<EncodingT>(commitHash, nativeCommitHash))
	{
		m_value->setCommitHash(nativeCommitHash);
	}
}


template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::setCommitDate(boost::shared_ptr< Base<EncodingT> > const& commitDate)
{
	typename EncodingT::string_t nativeCommitDate;
	if (check_string<EncodingT>(commitDate, nativeCommitDate))
	{
		m_value->setCommitDate(nativeCommitDate);
	}
}


template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::setCommitAuthor(boost::shared_ptr< Base<EncodingT> > const& commitAuthor)
{
	typename EncodingT::string_t nativeCommitAuthor;
	if (check_string<EncodingT>(commitAuthor, nativeCommitAuthor))
	{
		m_value->setCommitAuthor(nativeCommitAuthor);
	}
}


template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::setCommitLine(boost::shared_ptr< Base<EncodingT> > const& commitLine)
{
	long long nativeCommitLine;
	if (check_numeric_i(commitLine, nativeCommitLine))
	{
		m_value->setCommitLine(nativeCommitLine);
	}
}


template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::hasCppFile() const
{
	return boost::shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!m_value->isNullCppFile()) );
}


template <class EncodingT>
void CppNoticeInterpreter<EncodingT>::removeCppFile()
{
	m_value->eraseCppFile();
}

template <class EncodingT>
typename EncodingT::string_t CppNoticeInterpreter<EncodingT>::toString() const
{
	std::stringstream stream;
	stream << *m_value;
	return C(stream.str());
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new CppNoticeInterpreter<EncodingT>(copy_ptr(m_value)));
}

template <class EncodingT>
typename EncodingT::string_t CppNoticeInterpreter<EncodingT>::getClassName() const
{
	return UCS("CppNotice");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CppNoticeInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("CppNotice"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in CppNotice, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
bool check_cppNotice(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppNotice<EncodingT> >& o)
{
	boost::shared_ptr< CppNoticeInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppNoticeInterpreter<EncodingT> >(val);
	if (value)
	{
		o = value->value();
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppNotice expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_cppNotice(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppNotice<EncodingT> > const& o)
{
	boost::shared_ptr< CppNoticeInterpreter<EncodingT> > value  = dynamic_pointer_cast< CppNoticeInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(o);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "CppNotice expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef C
#undef A

