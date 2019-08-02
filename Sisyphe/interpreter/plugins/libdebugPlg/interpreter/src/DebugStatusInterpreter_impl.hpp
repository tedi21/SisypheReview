/*
 * DebugStatusInterpreter_impl.hpp
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
DebugStatusInterpreter<EncodingT>::DebugStatusInterpreter()
{
}

template <class EncodingT>
typename EncodingT::string_t DebugStatusInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStatusInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugStatusInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t DebugStatusInterpreter<EncodingT>::getClassName() const
{
	return UCS("DebugStatus");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStatusInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugStatus"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugStatus, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStatusInterpreter<EncodingT>::getDEBUG_STATUS_NO_CHANGE() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_STATUS_NO_CHANGE));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStatusInterpreter<EncodingT>::getDEBUG_STATUS_GO() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_STATUS_GO));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStatusInterpreter<EncodingT>::getDEBUG_STATUS_GO_HANDLED() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_STATUS_GO_HANDLED));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStatusInterpreter<EncodingT>::getDEBUG_STATUS_GO_NOT_HANDLED() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_STATUS_GO_NOT_HANDLED));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStatusInterpreter<EncodingT>::getDEBUG_STATUS_STEP_OVER() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_STATUS_STEP_OVER));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStatusInterpreter<EncodingT>::getDEBUG_STATUS_STEP_INTO() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_STATUS_STEP_INTO));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStatusInterpreter<EncodingT>::getDEBUG_STATUS_BREAK() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_STATUS_BREAK));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStatusInterpreter<EncodingT>::getDEBUG_STATUS_NO_DEBUGGEE() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_STATUS_NO_DEBUGGEE));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStatusInterpreter<EncodingT>::getDEBUG_STATUS_STEP_BRANCH() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_STATUS_STEP_BRANCH));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugStatusInterpreter<EncodingT>::getDEBUG_STATUS_IGNORE_EVENT() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_STATUS_IGNORE_EVENT));
}


NAMESPACE_END

#undef A
#undef C