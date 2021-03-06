/*
 * IDebugSymbolsPtrInterpreter_impl.hpp
 *
 *
 * @date 12-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)


template <class EncodingT>
IDebugSymbolsPtrInterpreter<EncodingT>::IDebugSymbolsPtrInterpreter()
{
}

template <class EncodingT>
void IDebugSymbolsPtrInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
void IDebugSymbolsPtrInterpreter<EncodingT>::initValue(const IDebugSymbolsPtr& object)
{
	m_object = object;
}

template <class EncodingT>
IDebugSymbolsPtr& IDebugSymbolsPtrInterpreter<EncodingT>::refValue()
{
	return m_object;
}

template <class EncodingT>
const IDebugSymbolsPtr& IDebugSymbolsPtrInterpreter<EncodingT>::refValue() const
{
	return m_object;
}

template <class EncodingT>
IDebugSymbolsPtrInterpreter<EncodingT>::IDebugSymbolsPtrInterpreter(const IDebugSymbolsPtr& object)
{
	initValue(object);
}

template <class EncodingT>
const IDebugSymbolsPtr& IDebugSymbolsPtrInterpreter<EncodingT>::value() const
{
	return refValue();
}

template <class EncodingT>
void IDebugSymbolsPtrInterpreter<EncodingT>::value(IDebugSymbolsPtr const& object)
{
	if (&object != &value()) {
		tidyValue();
		initValue(object);
	}
}

template <class EncodingT>
typename EncodingT::string_t IDebugSymbolsPtrInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new IDebugSymbolsPtrInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t IDebugSymbolsPtrInterpreter<EncodingT>::getClassName() const
{
	return UCS("IDebugSymbolsPtr");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("IDebugSymbolsPtr"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in IDebugSymbolsPtr, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Turns on some of the engine's global symbol options. 
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::addSymbolOptions(const boost::shared_ptr< Base<EncodingT> >& options)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugSymbolsPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeOptions;
		if (check_numeric_i(options, nativeOptions))
		{
			res->LLvalue(valuePtr->AddSymbolOptions(nativeOptions));
		}
	}
	return res;
}

// Appends directories to the executable image path.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::appendImagePath(const boost::shared_ptr< Base<EncodingT> >& addition)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugSymbolsPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		typename ansi::string_t nativeAddition;
		if (check_string<ansi>(addition, nativeAddition))
		{
			res->LLvalue(valuePtr->AppendImagePath(nativeAddition.c_str()));
		}
	}
	return res;
}

// Appends directories to the source path.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::appendSourcePath(const boost::shared_ptr< Base<EncodingT> >& addition)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugSymbolsPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		typename ansi::string_t nativeAddition;
		if (check_string<ansi>(addition, nativeAddition))
		{
			res->LLvalue(valuePtr->AppendSourcePath(nativeAddition.c_str()));
		}
	}
	return res;
}

// Appends directories to the symbol path.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::appendSymbolPath(const boost::shared_ptr< Base<EncodingT> >& addition)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugSymbolsPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		typename ansi::string_t nativeAddition;
		if (check_string<ansi>(addition, nativeAddition))
		{
			res->LLvalue(valuePtr->AppendSymbolPath(nativeAddition.c_str()));
		}
	}
	return res;
}

// Returns the base address of module which contains the specified symbol.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::getSymbolModule(const boost::shared_ptr< Base<EncodingT> >& symbol, boost::shared_ptr< Base<EncodingT> >& base)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugSymbolsPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		typename ansi::string_t nativeSymbol;
		unsigned long long nativeBase;
		if (check_string<ansi>(symbol, nativeSymbol) && 
			check_numeric_i(base, nativeBase))
		{
			res->LLvalue(valuePtr->GetSymbolModule(nativeSymbol.c_str(), &nativeBase));
			reset_numeric_i(base, nativeBase);
		}
	}
	return res;
}

// Returns the engine's global symbol options.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::getSymbolOptions(boost::shared_ptr< Base<EncodingT> >& options)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugSymbolsPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeOptions;
		if (check_numeric_i(options, nativeOptions))
		{
			res->LLvalue(valuePtr->GetSymbolOptions(&nativeOptions));
			reset_numeric_i(options, nativeOptions);
		}
	}
	return res;
}

// Returns the symbol path.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::getSymbolPath(boost::shared_ptr< Base<EncodingT> >& buffer)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
  IDebugSymbolsPtr valuePtr = value();
  if (valuePtr != NULL)
  {
    char nativeBuffer[2048];
    ZeroMemory(nativeBuffer, 2048);
    res.reset(new Numeric<EncodingT>(valuePtr->GetSymbolPath(nativeBuffer, 2048, NULL)));
    reset_string<ansi>(buffer, nativeBuffer);
  }
  return res;
}

// Returns the source filename and the line number within the source file of an instruction in the target.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::getLineByOffset(const boost::shared_ptr< Base<EncodingT> >& offset, boost::shared_ptr< Base<EncodingT> >& line, boost::shared_ptr< Base<EncodingT> >& fileBuffer, boost::shared_ptr< Base<EncodingT> >& displacement)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
  IDebugSymbolsPtr valuePtr = value();
  if (valuePtr != NULL)
  {
    unsigned long long nativeOffset;
    unsigned long nativeLine;
    char nativeFileBuffer[2048];
    ZeroMemory(nativeFileBuffer, 2048);
    unsigned long long nativeDisplacement;
    if (check_numeric_i(offset, nativeOffset) && 
        check_numeric_i(line, nativeLine) &&
        check_numeric_i(displacement, nativeDisplacement))
    {
      res.reset(new Numeric<EncodingT>(valuePtr->GetLineByOffset(nativeOffset, &nativeLine, nativeFileBuffer, 2048, NULL, &nativeDisplacement)));
      reset_numeric_i(line, nativeLine);
      reset_string<ansi>(fileBuffer, nativeFileBuffer);
      reset_numeric_i(displacement, nativeDisplacement);
    }
  }
  return res;
}

// Searches through the target's modules for one whose memory allocation includes the specified location.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::getModuleByOffset(const boost::shared_ptr< Base<EncodingT> >& offset, const boost::shared_ptr< Base<EncodingT> >& startIndex, boost::shared_ptr< Base<EncodingT> >& index, boost::shared_ptr< Base<EncodingT> >& base)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugSymbolsPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long long nativeOffset;
		unsigned long nativeStartIndex;
		unsigned long nativeIndex;
		unsigned long long nativeBase;
		if (check_numeric_i(offset, nativeOffset) && 
			check_numeric_i(startIndex, nativeStartIndex) && 
			check_numeric_i(index, nativeIndex) && 
			check_numeric_i(base, nativeBase))
		{
			res->LLvalue(valuePtr->GetModuleByOffset(nativeOffset, nativeStartIndex, &nativeIndex, &nativeBase));
			reset_numeric_i(index, nativeIndex);
			reset_numeric_i(base, nativeBase);
		}
	}
	return res;
}

// Returns the name of the symbol at the specified location in the target's virtual address space.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::getNameByOffset(const boost::shared_ptr< Base<EncodingT> >& offset, boost::shared_ptr< Base<EncodingT> >& nameBuffer, boost::shared_ptr< Base<EncodingT> >& displacement)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
  IDebugSymbolsPtr valuePtr = value();
  if (valuePtr != NULL)
  {
    unsigned long long nativeOffset;
    char nativeNameBuffer[2048];
    ZeroMemory(nativeNameBuffer, 2048);
    unsigned long long nativeDisplacement;
    if (check_numeric_i(offset, nativeOffset) &&
        check_numeric_i(displacement, nativeDisplacement))
    {
      res.reset(new Numeric<EncodingT>(valuePtr->GetNameByOffset(nativeOffset, nativeNameBuffer, 2048, NULL, &nativeDisplacement)));
      reset_string<ansi>(nameBuffer, nativeNameBuffer);
      reset_numeric_i(displacement, nativeDisplacement);
    }
  }
  return res;
}

// Returns the name of a symbol that is located near the specified location. 
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::getNearNameByOffset(const boost::shared_ptr< Base<EncodingT> >& offset, const boost::shared_ptr< Base<EncodingT> >& delta, boost::shared_ptr< Base<EncodingT> >& nameBuffer, boost::shared_ptr< Base<EncodingT> >& displacement)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
  IDebugSymbolsPtr valuePtr = value();
  if (valuePtr != NULL)
  {
    unsigned long long nativeOffset;
    long nativeDelta;
    char nativeNameBuffer[2048];
    ZeroMemory(nativeNameBuffer, 2048);
    unsigned long long nativeDisplacement;
    if (check_numeric_i(offset, nativeOffset) && 
        check_numeric_i(delta, nativeDelta) &&
        check_numeric_i(displacement, nativeDisplacement))
    {
      res.reset(new Numeric<EncodingT>(valuePtr->GetNearNameByOffset(nativeOffset, nativeDelta, nativeNameBuffer, 2048, NULL, &nativeDisplacement)));
      reset_string<ansi>(nameBuffer, nativeNameBuffer);
      reset_numeric_i(displacement, nativeDisplacement);
    }
  }
  return res;
}

// The GetOffsetByLine method returns the location of the instruction that corresponds to a specified line in the source code.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::getOffsetByLine(const boost::shared_ptr< Base<EncodingT> >& line, const boost::shared_ptr< Base<EncodingT> >& file, boost::shared_ptr< Base<EncodingT> >& offset)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugSymbolsPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeLine;
		typename ansi::string_t nativeFile;
		unsigned long long nativeOffset;
		if (check_numeric_i(line, nativeLine) && 
			check_string<ansi>(file, nativeFile) && 
			check_numeric_i(offset, nativeOffset))
		{
			res->LLvalue(valuePtr->GetOffsetByLine(nativeLine, nativeFile.c_str(), &nativeOffset));
			reset_numeric_i(offset, nativeOffset);
		}
	}
	return res;
}

// The GetSourceFileLineOffsets method maps each line in a source file to a location in the target's memory.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugSymbolsPtrInterpreter<EncodingT>::getSourceFileLineOffsets(const boost::shared_ptr< Base<EncodingT> >& file, boost::shared_ptr< Base<EncodingT> >& addresses)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDebugSymbolsPtr valuePtr = value();
	if (valuePtr != NULL)
	{
		typename ansi::string_t nativeFile;
    std::vector< unsigned long long > nativeAddresses;
		if (check_string<ansi>(file, nativeFile) &&
        check_array(addresses, nativeAddresses, check_numeric_i<EncodingT,unsigned long long>))
		{
      unsigned long nlines = 0;
      HRESULT hr = valuePtr->GetSourceFileLineOffsets(nativeFile.c_str(), NULL, 0, &nlines);
      if (SUCCEEDED(hr))
      {
        nativeAddresses.resize(nlines);
        hr = valuePtr->GetSourceFileLineOffsets(nativeFile.c_str(), nativeAddresses.data(), nlines, NULL);
        boost::shared_ptr< Array<EncodingT> > addressesArray  = dynamic_pointer_cast< Array<EncodingT> >(addresses);
        if (addressesArray)
        {
            for (size_t i = 0; i < nlines; ++i)
            {
              boost::shared_ptr< Base<EncodingT> > item(new Numeric<EncodingT>(nativeAddresses[i]));
              addressesArray->addValue(item);
            }
        }
      }
      res.reset(new Numeric<EncodingT>(hr));
		}
	}
	return res;
}


template <class EncodingT>
bool check_IDebugSymbolsPtr(boost::shared_ptr< Base<EncodingT> > const& val, IDebugSymbolsPtr& a)
{
	boost::shared_ptr< IDebugSymbolsPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDebugSymbolsPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->value();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDebugSymbolsPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_IDebugSymbolsPtr(boost::shared_ptr< Base<EncodingT> >& val, IDebugSymbolsPtr const& a)
{
	boost::shared_ptr< IDebugSymbolsPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDebugSymbolsPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(a);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDebugSymbolsPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef A
#undef C