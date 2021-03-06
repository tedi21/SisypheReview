/*
 * IDebugBreakpointPtrInterpreter_impl.hpp
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
IDebugBreakpointPtrInterpreter<EncodingT>::IDebugBreakpointPtrInterpreter()
{
}

template <class EncodingT>
void IDebugBreakpointPtrInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
void IDebugBreakpointPtrInterpreter<EncodingT>::initValue(const IDebugBreakpointPtr& object)
{
	m_object = object;
}

template <class EncodingT>
IDebugBreakpointPtr& IDebugBreakpointPtrInterpreter<EncodingT>::refValue()
{
	return m_object;
}

template <class EncodingT>
const IDebugBreakpointPtr& IDebugBreakpointPtrInterpreter<EncodingT>::refValue() const
{
	return m_object;
}

template <class EncodingT>
IDebugBreakpointPtrInterpreter<EncodingT>::IDebugBreakpointPtrInterpreter(const IDebugBreakpointPtr& object)
{
	initValue(object);
}

template <class EncodingT>
const IDebugBreakpointPtr& IDebugBreakpointPtrInterpreter<EncodingT>::value() const
{
	return refValue();
}

template <class EncodingT>
void IDebugBreakpointPtrInterpreter<EncodingT>::value(IDebugBreakpointPtr const& object)
{
	if (&object != &value()) {
		tidyValue();
		initValue(object);
	}
}

template <class EncodingT>
typename EncodingT::string_t IDebugBreakpointPtrInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugBreakpointPtrInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new IDebugBreakpointPtrInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t IDebugBreakpointPtrInterpreter<EncodingT>::getClassName() const
{
	return UCS("IDebugBreakpointPtr");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugBreakpointPtrInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("IDebugBreakpointPtr"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in IDebugBreakpointPtr, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Sets the location that triggers a breakpoint.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugBreakpointPtrInterpreter<EncodingT>::setOffset(const boost::shared_ptr< Base<EncodingT> >& offset)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugBreakpointPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long long nativeOffset;
		if (check_numeric_i(offset, nativeOffset))
		{
			res->LLvalue(valuePtr->SetOffset(nativeOffset));
		}
	}
	return res;
}

// The SetOffsetExpression methods set an expression string that evaluates to the location that triggers a breakpoint.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugBreakpointPtrInterpreter<EncodingT>::setOffsetExpression(const boost::shared_ptr< Base<EncodingT> >& expression)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugBreakpointPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		typename ansi::string_t nativeExpression;
		if (check_string<ansi>(expression, nativeExpression))
		{
			res->LLvalue(valuePtr->SetOffsetExpression(nativeExpression.c_str()));
		}
	}
	return res;
}

// Sets the flags for a breakpoint.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugBreakpointPtrInterpreter<EncodingT>::setFlags(const boost::shared_ptr< Base<EncodingT> >& flags)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugBreakpointPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeFlags;
		if (check_numeric_i(flags, nativeFlags))
		{
			res->LLvalue(valuePtr->SetFlags(nativeFlags));
		}
	}
	return res;
}

// The SetPassCount method sets the number of times that the target must reach the breakpoint location before the breakpoint is triggered.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugBreakpointPtrInterpreter<EncodingT>::setPassCount(const boost::shared_ptr< Base<EncodingT> >& count)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugBreakpointPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeCount;
		if (check_numeric_i(count, nativeCount))
		{
			res->LLvalue(valuePtr->SetPassCount(nativeCount));
		}
	}
	return res;
}

// The GetPassCount method returns the number of times that the target was originally required to reach the breakpoint location before the breakpoint is triggered.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugBreakpointPtrInterpreter<EncodingT>::getPassCount(boost::shared_ptr< Base<EncodingT> >& count)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugBreakpointPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeCount;
		if (check_numeric_i(count, nativeCount))
		{
			res->LLvalue(valuePtr->GetPassCount(&nativeCount));
			reset_numeric_i(count, nativeCount);
		}
	}
	return res;
}

// The GetCurrentPassCount method returns the remaining number of times that the target must reach the breakpoint location before the breakpoint is triggered.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugBreakpointPtrInterpreter<EncodingT>::getCurrentPassCount(boost::shared_ptr< Base<EncodingT> >& count)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugBreakpointPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeCount;
		if (check_numeric_i(count, nativeCount))
		{
			res->LLvalue(valuePtr->GetCurrentPassCount(&nativeCount));
			reset_numeric_i(count, nativeCount);
		}
	}
	return res;
}

// The GetId method returns a breakpoint ID, which is the engine's unique identifier for a breakpoint.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugBreakpointPtrInterpreter<EncodingT>::getId(boost::shared_ptr< Base<EncodingT> >& bpId)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugBreakpointPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeBpId;
		if (check_numeric_i(bpId, nativeBpId))
		{
			res->LLvalue(valuePtr->GetId(&nativeBpId));
			reset_numeric_i(bpId, nativeBpId);
		}
	}
	return res;
}

// The GetOffset method returns the location that triggers a breakpoint.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugBreakpointPtrInterpreter<EncodingT>::getOffset(boost::shared_ptr< Base<EncodingT> >& offset)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugBreakpointPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long long nativeOffset;
		if (check_numeric_i(offset, nativeOffset))
		{
			res->LLvalue(valuePtr->GetOffset(&nativeOffset));
			reset_numeric_i(offset, nativeOffset);
		}
	}
	return res;
}


template <class EncodingT>
bool check_IDebugBreakpointPtr(boost::shared_ptr< Base<EncodingT> > const& val, IDebugBreakpointPtr& a)
{
	boost::shared_ptr< IDebugBreakpointPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDebugBreakpointPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->value();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDebugBreakpointPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_IDebugBreakpointPtr(boost::shared_ptr< Base<EncodingT> >& val, IDebugBreakpointPtr const& a)
{
	boost::shared_ptr< IDebugBreakpointPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDebugBreakpointPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(a);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDebugBreakpointPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef A
#undef C