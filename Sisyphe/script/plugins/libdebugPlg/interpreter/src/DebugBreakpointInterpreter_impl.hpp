/*
 * DebugBreakpointInterpreter_impl.hpp
 *
 *
 * @date 21-06-2016
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)


template <class EncodingT>
DebugBreakpointInterpreter<EncodingT>::DebugBreakpointInterpreter()
{
}

template <class EncodingT>
void DebugBreakpointInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
DebugBreakpointInterpreter<EncodingT>::~DebugBreakpointInterpreter()
{
	tidyValue();
}

template <class EncodingT>
typename EncodingT::string_t DebugBreakpointInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugBreakpointInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new DebugBreakpointInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t DebugBreakpointInterpreter<EncodingT>::getClassName() const
{
	return C("DebugBreakpoint");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugBreakpointInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("DebugBreakpoint"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in DebugBreakpoint, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugBreakpointInterpreter<EncodingT>::getDEBUG_BREAKPOINT_CODE() const
{
	return shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_BREAKPOINT_CODE));
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugBreakpointInterpreter<EncodingT>::getDEBUG_BREAKPOINT_DATA() const
{
	return shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_BREAKPOINT_DATA));
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugBreakpointInterpreter<EncodingT>::getDEBUG_ANY_ID() const
{
	return shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_ANY_ID));
}


NAMESPACE_END

#undef A
#undef C