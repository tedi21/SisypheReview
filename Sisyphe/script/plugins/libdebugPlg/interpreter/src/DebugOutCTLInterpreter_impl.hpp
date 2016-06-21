/*
 * DebugOutCTLInterpreter_impl.hpp
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
DebugOutCTLInterpreter<EncodingT>::DebugOutCTLInterpreter()
{
}

template <class EncodingT>
void DebugOutCTLInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
DebugOutCTLInterpreter<EncodingT>::~DebugOutCTLInterpreter()
{
	tidyValue();
}

template <class EncodingT>
typename EncodingT::string_t DebugOutCTLInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugOutCTLInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new DebugOutCTLInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t DebugOutCTLInterpreter<EncodingT>::getClassName() const
{
	return C("DebugOutCTL");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugOutCTLInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("DebugOutCTL"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in DebugOutCTL, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugOutCTLInterpreter<EncodingT>::getDEBUG_OUTCTL_THIS_CLIENT() const
{
	return shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_OUTCTL_THIS_CLIENT));
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugOutCTLInterpreter<EncodingT>::getDEBUG_OUTCTL_ALL_CLIENTS() const
{
	return shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_OUTCTL_ALL_CLIENTS));
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugOutCTLInterpreter<EncodingT>::getDEBUG_OUTCTL_ALL_OTHER_CLIENTS() const
{
	return shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_OUTCTL_ALL_OTHER_CLIENTS));
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugOutCTLInterpreter<EncodingT>::getDEBUG_OUTCTL_IGNORE() const
{
	return shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_OUTCTL_IGNORE));
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugOutCTLInterpreter<EncodingT>::getDEBUG_OUTCTL_LOG_ONLY() const
{
	return shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_OUTCTL_LOG_ONLY));
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugOutCTLInterpreter<EncodingT>::getDEBUG_OUTCTL_SEND_MASK() const
{
	return shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_OUTCTL_SEND_MASK));
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugOutCTLInterpreter<EncodingT>::getDEBUG_OUTCTL_NOT_LOGGED() const
{
	return shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_OUTCTL_NOT_LOGGED));
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugOutCTLInterpreter<EncodingT>::getDEBUG_OUTCTL_OVERRIDE_MASK() const
{
	return shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_OUTCTL_OVERRIDE_MASK));
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > DebugOutCTLInterpreter<EncodingT>::getDEBUG_OUTCTL_AMBIENT() const
{
	return shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_OUTCTL_AMBIENT));
}


NAMESPACE_END

#undef A
#undef C