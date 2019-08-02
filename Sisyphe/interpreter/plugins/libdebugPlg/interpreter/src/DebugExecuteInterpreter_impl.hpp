/*
 * DebugExecuteInterpreter_impl.hpp
 *
 *
 * @date 02-08-2019
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)


template <class EncodingT>
DebugExecuteInterpreter<EncodingT>::DebugExecuteInterpreter()
{
}

template <class EncodingT>
typename EncodingT::string_t DebugExecuteInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugExecuteInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugExecuteInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t DebugExecuteInterpreter<EncodingT>::getClassName() const
{
	return UCS("DebugExecute");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugExecuteInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugExecute"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugExecute, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugExecuteInterpreter<EncodingT>::getDEBUG_EXECUTE_DEFAULT() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_EXECUTE_DEFAULT));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugExecuteInterpreter<EncodingT>::getDEBUG_EXECUTE_ECHO() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_EXECUTE_ECHO));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugExecuteInterpreter<EncodingT>::getDEBUG_EXECUTE_NOT_LOGGED() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_EXECUTE_NOT_LOGGED));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugExecuteInterpreter<EncodingT>::getDEBUG_EXECUTE_NO_REPEAT() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_EXECUTE_NO_REPEAT));
}


NAMESPACE_END

#undef A
#undef C